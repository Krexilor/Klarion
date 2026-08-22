#pragma once

// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <string>
#include <vector>
#include <utility>

// EXTERNAL LIBRARIES ------------------------------------------------------------------------------------------------------------------------------|
#include <fmt/format.h>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/klarion.hpp"
#include "klarion/core/field.hpp"

// MACROS DEFINATION -------------------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    // Log a message with fmt-style formatting
    template<typename... Args>
    inline void log(Level level, SourceLocation location, fmt::format_string<Args...> fmt, Args&&... args) {
        auto logger = default_logger();
        if (logger && is_enabled(level, logger->level())) {
            std::string message = fmt::format(fmt, std::forward<Args>(args)...);
            logger->log(level, std::move(message), location);
        }
    }

    // Log a message to a specific logger
    template<typename... Args>
    inline void log_to(const std::string& logger_name, Level level, SourceLocation location, fmt::format_string<Args...> fmt, Args&&... args) {
        auto logger = get(logger_name);
        if (logger && is_enabled(level, logger->level())) {
            std::string message = fmt::format(fmt, std::forward<Args>(args)...);
            logger->log(level, std::move(message), location);
        }
    }

    // Log a plain message with structured key-value fields
    template<typename... Fields>
    inline void log_kv(Level level, SourceLocation location, std::string message, Fields&&... fields) {
        auto logger = default_logger();
        if (logger && is_enabled(level, logger->level())) {
            logger->log(level, std::move(message), location, std::vector<Field>{std::forward<Fields>(fields)...});
        }
    }

    // Log a plain message with structured key-value fields to a specific logger
    template<typename... Fields>
    inline void log_to_kv(const std::string& logger_name, Level level, SourceLocation location, std::string message, Fields&&... fields) {
        auto logger = get(logger_name);
        if (logger && is_enabled(level, logger->level())) {
            logger->log(level, std::move(message), location, std::vector<Field>{std::forward<Fields>(fields)...});
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

// STRUCTURED LOGGING MACROS -----------------------------------------------------------------------------------------------------------------------|
#define LOG_TRACE_KV(msg, ...) klarion::log_kv(klarion::Level::Trace, KLARION_SOURCE_LOCATION(), msg, __VA_ARGS__)
#define LOG_DEBUG_KV(msg, ...) klarion::log_kv(klarion::Level::Debug, KLARION_SOURCE_LOCATION(), msg, __VA_ARGS__)
#define LOG_INFO_KV(msg, ...) klarion::log_kv(klarion::Level::Info, KLARION_SOURCE_LOCATION(), msg, __VA_ARGS__)
#define LOG_WARN_KV(msg, ...) klarion::log_kv(klarion::Level::Warn, KLARION_SOURCE_LOCATION(), msg, __VA_ARGS__)
#define LOG_ERROR_KV(msg, ...) klarion::log_kv(klarion::Level::Error, KLARION_SOURCE_LOCATION(), msg, __VA_ARGS__)
#define LOG_CRITICAL_KV(msg, ...) klarion::log_kv(klarion::Level::Critical, KLARION_SOURCE_LOCATION(), msg, __VA_ARGS__)

// STRUCTURED LOGGER-SPECIFIC MACROS ---------------------------------------------------------------------------------------------------------------|
#define LOG_TO_TRACE_KV(logger_name, msg, ...) klarion::log_to_kv(logger_name, klarion::Level::Trace, KLARION_SOURCE_LOCATION(), msg, __VA_ARGS__)
#define LOG_TO_DEBUG_KV(logger_name, msg, ...) klarion::log_to_kv(logger_name, klarion::Level::Debug, KLARION_SOURCE_LOCATION(), msg, __VA_ARGS__)
#define LOG_TO_INFO_KV(logger_name, msg, ...) klarion::log_to_kv(logger_name, klarion::Level::Info, KLARION_SOURCE_LOCATION(), msg, __VA_ARGS__)
#define LOG_TO_WARN_KV(logger_name, msg, ...) klarion::log_to_kv(logger_name, klarion::Level::Warn, KLARION_SOURCE_LOCATION(), msg, __VA_ARGS__)
#define LOG_TO_ERROR_KV(logger_name, msg, ...) klarion::log_to_kv(logger_name, klarion::Level::Error, KLARION_SOURCE_LOCATION(), msg, __VA_ARGS__)
#define LOG_TO_CRITICAL_KV(logger_name, msg, ...) klarion::log_to_kv(logger_name, klarion::Level::Critical, KLARION_SOURCE_LOCATION(), msg, __VA_ARGS__)
