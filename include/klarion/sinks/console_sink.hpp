#pragma once

// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <mutex>
#include <iostream>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/sinks/sink.hpp"
#include "klarion/detail/terminal/console_color.hpp"
#include "klarion/detail/formatting/pattern_formatter.hpp"

// CONSOLE SINK DEFINITION -------------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    class ConsoleSink : public Sink {
        public:
            ConsoleSink();
            explicit ConsoleSink(detail::ColorMode color_mode);

            void write(const LogRecord& record) override;
            void flush() override;
            void set_pattern(const std::string& pattern) override;
            void set_color_mode(detail::ColorMode mode);
            void set_level_color(
                Level level,
                detail::Color color,
                detail::Style style = detail::Style::Normal
            );

        private:
            detail::ConsoleColor colorizer_;
            detail::PatternFormatter formatter_;
            std::mutex mutex_;
    };
}

