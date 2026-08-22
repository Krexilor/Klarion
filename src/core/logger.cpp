// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <algorithm>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/core/logger.hpp"

// LOGGER IMPLEMENTATION ---------------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    Logger::Logger(std::string name) : name_(std::move(name)) {}

    Logger::~Logger() {
        std::lock_guard<std::mutex> lock(mutex_);
        for (auto& sink : sinks_) {
            sink->flush();
        }
    }

    void Logger::set_level(Level level) {
        std::lock_guard<std::mutex> lock(mutex_);
        level_ = level;
    }

    Level Logger::level() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return level_;
    }

    void Logger::add_sink(SinkPtr sink) {
        if (!sink) {
            return;
        }

        std::lock_guard<std::mutex> lock(mutex_);

        if (std::find(sinks_.begin(), sinks_.end(), sink) == sinks_.end()) {
            sinks_.push_back(std::move(sink));
        }
    }

    void Logger::remove_sink(SinkPtr sink) {
        std::lock_guard<std::mutex> lock(mutex_);
        sinks_.erase(std::remove(sinks_.begin(), sinks_.end(), sink), sinks_.end());
    }

    void Logger::clear_sinks() {
        std::lock_guard<std::mutex> lock(mutex_);
        sinks_.clear();
    }

    size_t Logger::sink_count() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return sinks_.size();
    }

    void Logger::log(Level level, std::string message, SourceLocation location, std::vector<Field> fields) {
        std::lock_guard<std::mutex> lock(mutex_);

        if (!is_enabled(level, level_)) {
            return;
        }

        LogRecord record(level, std::move(message), name_, location, std::move(fields));

        for (auto& sink : sinks_) {
            if (sink->should_log(level)) {
                sink->write(record);
            }
        }
    }

    void Logger::set_pattern(const std::string& pattern) {
        std::lock_guard<std::mutex> lock(mutex_);
        for (auto& sink : sinks_) {
            sink->set_pattern(pattern);
        }
    }
}
