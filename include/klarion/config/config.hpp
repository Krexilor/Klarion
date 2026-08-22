#pragma once

// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <map>
#include <string>
#include <vector>
#include <memory>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/core/level.hpp"
#include "klarion/detail/terminal/console_color.hpp"

// CONFIG DEFINATION -------------------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    // Config for single sink
    struct SinkConfig {
        std::string name;
        std::string type;
        std::string path;
        std::string pattern;
        Level level{Level::Info};
        bool append{true};
        detail::ColorMode color_mode{detail::ColorMode::Auto};

        std::map<Level, std::pair<detail::Color, detail::Style>> level_colors;
    };

    // Config for a logger
    struct LoggerConfig {
        std::string name;
        Level level{Level::Info};
        std::vector<std::string> sinks;
        std::string pattern;
    };

    // Main configuration class
    class Config {
        public:
            Config();
            Config& set_level(Level level);
            Config& set_pattern(const std::string& pattern);
            Config& add_console_sink();
            Config& add_console_sink(detail::ColorMode color_mode, const std::string& pattern = "");
            Config& add_file_sink(const std::string& path, bool append = true);
            Config& add_file_sink(const std::string& path, bool append, const std::string& pattern);
            Config& add_logger(LoggerConfig config);

            // Getters
            Level level() const { return default_level_; }
            const std::string& pattern() const { return default_pattern_; }
            const std::vector<SinkConfig>& sinks() const { return sink_configs_; }
            const std::vector<LoggerConfig>& loggers() const { return logger_configs_; }
            const std::vector<std::string>& default_sinks() const { return default_sinks_; }

            // Mutable access for post-parse adjustments
            std::vector<LoggerConfig>& mutable_loggers() { return logger_configs_; }

            static Config from_toml_file(const std::string& path);
            static Config from_toml_string(const std::string& toml);

        private:
            Level default_level_{Level::Info};
            std::string default_pattern_;
            std::vector<SinkConfig> sink_configs_;
            std::vector<LoggerConfig> logger_configs_;
            std::vector<std::string> default_sinks_;
    };
}
