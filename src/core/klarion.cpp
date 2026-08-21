// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/klarion.hpp"
#include "klarion/sinks/file_sink.hpp"
#include "klarion/sinks/console_sink.hpp"

// KLARION IMPLEMENTATION --------------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    std::map<std::string, std::shared_ptr<Logger>> Klarion::loggers_;
    std::mutex Klarion::mutex_;
    bool Klarion::initialized_{false};

    void Klarion::init() {
        Config config;
        config.add_console_sink();
        init(config);
    }

    void Klarion::init(const std::string& config_path) {
        Config config = Config::from_toml_file(config_path);
        init(config);
    }

    void Klarion::init(const Config& config) {
        std::lock_guard<std::mutex> lock(mutex_);

        if (initialized_) {
            shutdown_impl();
        }

        apply_config(config);
        initialized_ = true;
    }

    void Klarion::shutdown() {
        std::lock_guard<std::mutex> lock(mutex_);
        shutdown_impl();
    }

    void Klarion::shutdown_impl() {
        for (auto& [name, logger] : loggers_) {
            logger->clear_sinks();
        }
        loggers_.clear();
        initialized_ = false;
    }

    std::shared_ptr<Logger> Klarion::default_logger() {
        return get("default");
    }

    std::shared_ptr<Logger> Klarion::get(const std::string& name) {
        std::lock_guard<std::mutex> lock(mutex_);

        auto it = loggers_.find(name);
        if (it != loggers_.end()) {
            return it->second;
        }

        auto logger = std::make_shared<Logger>(name);
        loggers_[name] = logger;
        return logger;
    }

    std::shared_ptr<Logger> Klarion::create(const std::string& name) {
        std::lock_guard<std::mutex> lock(mutex_);

        auto logger = std::make_shared<Logger>(name);
        loggers_[name] = logger;
        return logger;
    }

    void Klarion::set_level(Level level) {
        auto logger = default_logger();
        if (logger) {
            logger->set_level(level);
        }
    }

    bool Klarion::is_initialized() {
        return initialized_;
    }

    void Klarion::apply_config(const Config& config) {
        std::map<std::string, SinkPtr> sink_map;

        for (size_t i = 0; i < config.sinks().size(); ++i) {
            const auto& sink_config = config.sinks()[i];
            std::string key = sink_config.name.empty()
                ? ("sink_" + std::to_string(i))
                : sink_config.name;

            try {
                sink_map[key] = create_sink(sink_config);
            }
            catch (const std::exception&) {
                // skip invalid sink, continue with others
            }
        }

        auto def_logger = std::make_shared<Logger>("default");
        def_logger->set_level(config.level());

        if (!config.default_sinks().empty()) {
            for (const auto& name : config.default_sinks()) {
                auto it = sink_map.find(name);
                if (it != sink_map.end()) def_logger->add_sink(it->second);
            }
        } else {
            for (const auto& [name, sink] : sink_map) {
                def_logger->add_sink(sink);
            }   
        }

        loggers_["default"] = def_logger;

        for (const auto& logger_config : config.loggers()) {
            auto logger = std::make_shared<Logger>(logger_config.name);
            logger->set_level(logger_config.level);
            if (!logger_config.pattern.empty()) logger->set_pattern(logger_config.pattern);

            for (const auto& sink_name : logger_config.sinks) {
                auto it = sink_map.find(sink_name);
                if (it != sink_map.end()) logger->add_sink(it->second);
            }
            loggers_[logger_config.name] = logger;
        }
    }

    SinkPtr Klarion::create_sink(const SinkConfig& config) {
        if (config.type == "console") {
            auto sink = std::make_shared<ConsoleSink>(config.color_mode);
            sink->set_level(config.level);
            sink->set_pattern(config.pattern);

            for (const auto& [level, color_style] : config.level_colors) {
                static_cast<ConsoleSink*>(sink.get())->set_level_color(level, color_style.first, color_style.second);
            }

            return sink;
        }
        else if (config.type == "file") {
            auto sink = std::make_shared<FileSink>(config.path, config.append);
            sink->set_level(config.level);
            sink->set_pattern(config.pattern);
            return sink;
        }

        throw std::runtime_error("Unknown sink type: " + config.type);
    }
}
