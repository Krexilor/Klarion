#pragma once

// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <map>
#include <mutex>
#include <string>
#include <memory>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/core/level.hpp"
#include "klarion/core/logger.hpp"
#include "klarion/config/config.hpp"
#include "klarion/core/source_location.hpp"

// KLARION DEFINITION ------------------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    class Klarion {
        public:
            static void init();
            static void init(const std::string& config_path, bool strict = false);
            static void init(const Config& config);
            static void shutdown();

            static void reload(const Config& config);
            static void reload(const std::string& config_path, bool strict = false);

            static std::shared_ptr<Logger> default_logger();
            static std::shared_ptr<Logger> get(const std::string& name);
            static std::shared_ptr<Logger> create(const std::string& name);

            static void set_level(Level level);
            static void set_level(const std::string& logger_name, Level level);

            static bool is_initialized();

        private:
            static void apply_config(const Config& config);
            static void reinit_locked(const Config& config);
            static SinkPtr create_sink(const SinkConfig& config);
            static void shutdown_impl();
            static std::map<std::string, std::shared_ptr<Logger>> loggers_;
            static std::mutex mutex_;
            static bool initialized_;
    };

    inline void init() { Klarion::init(); }
    inline void init(const std::string& config_path, bool strict = false) { Klarion::init(config_path, strict); }
    inline void init(const Config& config) { Klarion::init(config); }
    inline void shutdown() { Klarion::shutdown(); }

    inline void reload(const Config& config) { Klarion::reload(config); }
    inline void reload(const std::string& config_path, bool strict = false) { Klarion::reload(config_path, strict); }

    inline std::shared_ptr<Logger> default_logger() {
        return Klarion::default_logger();
    }

    inline std::shared_ptr<Logger> get(const std::string& name) {
        return Klarion::get(name);
    }

    inline void set_level(Level level) { Klarion::set_level(level); }
    inline void set_level(const std::string& logger_name, Level level) { Klarion::set_level(logger_name, level); }
}
