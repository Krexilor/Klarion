#pragma once

// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <string>
#include <utility>

// EXTERNAL LIBRARIES ------------------------------------------------------------------------------------------------------------------------------|
#include <fmt/format.h>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/klarion.hpp"

// MACROS DEFINATION -------------------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    template<typename... Args>
    inline void log(Level level, SourceLocation location, fmt::format_string<Args...> fmt, Args&&... args) {
        auto logger = default_logger();
        if (logger && is_enabled(level, logger->level())) {
            std::string message = fmt::format(fmt, std::forward<Args>(args)...);
            logger->log(level, std::move(message), location);
        }
    }

    template<typename... Args>
    inline void log_to(const std::string& logger_name, Level level, SourceLocation location, fmt::format_string<Args...> fmt, Args&&... args) {
        auto logger = get(logger_name);
        if (logger && is_enabled(level, logger->level())) {
            std::string message = fmt::format(fmt, std::forward<Args>(args)...);
            logger->log(level, std::move(message), location);
        }
    }
}

// LOGGIGN MACROS ----------------------------------------------------------------------------------------------------------------------------------|
#define LOG_TRACE(...) klarion::log(klarion::Level::Trace, KLARION_SOURCE_LOCATION(), __VA_ARGS__)
#define LOG_DEBUG(...) klarion::log(klarion::Level::Debug, KLARION_SOURCE_LOCATION(), __VA_ARGS__)
#define LOG_INFO(...) klarion::log(klarion::Level::Info, KLARION_SOURCE_LOCATION(), __VA_ARGS__)
#define LOG_WARN(...) klarion::log(klarion::Level::Warn, KLARION_SOURCE_LOCATION(), __VA_ARGS__)
#define LOG_ERROR(...) klarion::log(klarion::Level::Error, KLARION_SOURCE_LOCATION(), __VA_ARGS__)
#define LOG_CRITICAL(...) klarion::log(klarion::Level::Critical, KLARION_SOURCE_LOCATION(), __VA_ARGS__)

// LOGGER-SPECIFIC MACROS --------------------------------------------------------------------------------------------------------------------------|
#define LOG_TO_TRACE(logger_name, ...) klarion::log_to(logger_name, klarion::Level::Trace, KLARION_SOURCE_LOCATION(), __VA_ARGS__)
#define LOG_TO_DEBUG(logger_name, ...) klarion::log_to(logger_name, klarion::Level::Debug, KLARION_SOURCE_LOCATION(), __VA_ARGS__)
#define LOG_TO_INFO(logger_name, ...) klarion::log_to(logger_name, klarion::Level::Info, KLARION_SOURCE_LOCATION(), __VA_ARGS__)
#define LOG_TO_WARN(logger_name, ...) klarion::log_to(logger_name, klarion::Level::Warn, KLARION_SOURCE_LOCATION(), __VA_ARGS__)
#define LOG_TO_ERROR(logger_name, ...) klarion::log_to(logger_name, klarion::Level::Error, KLARION_SOURCE_LOCATION(), __VA_ARGS__)
#define LOG_TO_CRITICAL(logger_name, ...) klarion::log_to(logger_name, klarion::Level::Critical, KLARION_SOURCE_LOCATION(), __VA_ARGS__)
