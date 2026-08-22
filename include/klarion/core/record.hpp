#pragma once

// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <utility>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/core/level.hpp"
#include "klarion/core/field.hpp"
#include "klarion/core/source_location.hpp"

// RECORD DEFINITION -------------------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    struct LogRecord {
        Level level{Level::Info};
        std::string message;
        std::string logger_name;
        SourceLocation location;
        std::chrono::system_clock::time_point timestamp;
        std::thread::id thread_id;
        std::vector<Field> fields;

        LogRecord() : timestamp(std::chrono::system_clock::now()), thread_id(std::this_thread::get_id()) {}

        LogRecord(
            Level level_,
            std::string message_,
            std::string logger_name_,
            SourceLocation location_,
            std::vector<Field> fields_ = {}
        ) :
        level(level_),
        message(std::move(message_)),
        logger_name(std::move(logger_name_)),
        location(location_),
        timestamp(std::chrono::system_clock::now()),
        thread_id(std::this_thread::get_id()),
        fields(std::move(fields_)) {}
    };
}
