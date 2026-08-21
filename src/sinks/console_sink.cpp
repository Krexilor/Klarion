// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <iostream>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/sinks/console_sink.hpp"

// CONSOLE SINK IMPLEMENTATION ---------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    ConsoleSink::ConsoleSink() : colorizer_(detail::ColorMode::Auto) {
        set_pattern("[%time] [%level] [%logger] %msg");
    }

    ConsoleSink::ConsoleSink(detail::ColorMode color_mode) : colorizer_(color_mode) {
        set_pattern("[%time] [%level] [%logger] %msg");
    }

    void ConsoleSink::write(const LogRecord& record) {
        if (!should_log(record.level)) {
            return;
        }

        std::lock_guard<std::mutex> lock(mutex_);

        if (record.level >= Level::Warn) {
            std::cerr << formatter_.format(record, colorizer_) << "\n";
        }
        else {
            std::cout << formatter_.format(record, colorizer_) << "\n";
        }
    }

    void ConsoleSink::flush() {
        std::lock_guard<std::mutex> lock(mutex_);
        std::cout.flush();
        std::cerr.flush();
    }

    void ConsoleSink::set_pattern(const std::string& pattern) {
        std::lock_guard<std::mutex> lock(mutex_);
        formatter_.set_pattern(pattern);
        pattern_ = pattern;
    }

    void ConsoleSink::set_color_mode(detail::ColorMode mode) {
        std::lock_guard<std::mutex> lock(mutex_);
        colorizer_.set_mode(mode);
    }

    void ConsoleSink::set_level_color(Level level, detail::Color color, detail::Style style) {
        std::lock_guard<std::mutex> lock(mutex_);
        colorizer_.set_level_color(level, color, style);
    }
}
