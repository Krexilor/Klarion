// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <cctype>
#include <cstdlib>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/config/env_overrides.hpp"

// ENVIRONMENT OVERRIDES IMPLEMENTATION ------------------------------------------------------------------------------------------------------------|
namespace klarion::detail {
    namespace {
        std::string env_key_for_logger(const std::string& logger_name) {
            std::string key = "KLARION_LEVEL_";
            key.reserve(key.size() + logger_name.size());

            for (char c : logger_name) {
                key.push_back(std::isalnum(static_cast<unsigned char>(c))
                    ? static_cast<char>(std::toupper(static_cast<unsigned char>(c)))
                    : '_');
            }

            return key;
        }
    }

    void apply_environment_overrides(Config& config) {
        if (const char* level_env = std::getenv("KLARION_LEVEL")) {
            config.set_level(level_from_string(level_env));
        }

        for (auto& logger_config : config.mutable_loggers()) {
            std::string key = env_key_for_logger(logger_config.name);

            if (const char* level_env = std::getenv(key.c_str())) {
                logger_config.level = level_from_string(level_env);
            }
        }
    }
}
