// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/config/config.hpp"

// CONFIG IMPLEMENTATION ---------------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    Config::Config() {
        default_pattern_ = "[%time] [%level] [%logger] %msg";
    }

    Config& Config::set_level(Level level) {
        default_level_ = level;
        return *this;
    }

    Config& Config::set_pattern(const std::string& pattern) {
        default_pattern_ = pattern;
        return *this;
    }

    Config& Config::add_console_sink() {
        return add_console_sink(detail::ColorMode::Auto, default_pattern_);
    }

    Config& Config::add_console_sink(detail::ColorMode color_mode, const std::string& pattern) {
        SinkConfig config;
        config.type = "console";
        config.color_mode = color_mode;
        config.pattern = pattern.empty() ? default_pattern_ : pattern;
        config.level = default_level_;
        sink_configs_.push_back(config);
        return *this;
    }

    Config& Config::add_file_sink(const std::string& path, bool append) {
        return add_file_sink(path, append, "[%time] [%level] [%logger] [%file:%line] %msg");
    }

    Config& Config::add_file_sink(const std::string& path, bool append, const std::string& pattern) {
        SinkConfig config;
        config.type = "file";
        config.path = path;
        config.append = append;
        config.pattern = pattern;
        config.level = default_level_;
        sink_configs_.push_back(config);
        return *this;
    }

    Config& Config::add_logger(LoggerConfig config) {
        logger_configs_.push_back(std::move(config));
        return *this;
    }
}
