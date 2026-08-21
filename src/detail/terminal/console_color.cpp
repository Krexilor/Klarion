// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <cstdio>
#include <cstdlib>
#include <iostream>

// PLATFORM-SPECIFIC HEADERS -----------------------------------------------------------------------------------------------------------------------|
#if defined(_WIN32)
    #include <io.h>
#else
    #include <unistd.h>
#endif

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/detail/terminal/console_color.hpp"

// CONSOLE COLOR IMPLEMENTATION --------------------------------------------------------------------------------------------------------------------|
namespace klarion::detail {
    std::string to_ansi_code(Color color) {
        switch (color) {
            case Color::Default: return "\033[39m";
            case Color::Black: return "\033[30m";
            case Color::Red: return "\033[31m";
            case Color::Green: return "\033[32m";
            case Color::Yellow: return "\033[33m";
            case Color::Blue: return "\033[34m";
            case Color::Magenta: return "\033[35m";
            case Color::Cyan: return "\033[36m";
            case Color::White: return "\033[37m";
            case Color::BrightBlack: return "\033[90m";
            case Color::BrightRed: return "\033[91m";
            case Color::BrightGreen: return "\033[92m";
            case Color::BrightYellow: return "\033[93m";
            case Color::BrightBlue: return "\033[94m";
            case Color::BrightMagenta: return "\033[95m";
            case Color::BrightCyan: return "\033[96m";
            case Color::BrightWhite: return "\033[97m";
            default: return "\033[39m";
        }
    }

    std::string to_ansi_code(Style style) {
        switch (style) {
            case Style::Reset: return "\033[0m";
            case Style::Bold: return "\033[1m";
            case Style::Dim: return "\033[2m";
            case Style::Normal: return "\033[22m";
            default: return "\033[0m";
        }
    }

    Color default_level_color(Level level) {
        switch (level) {
            case Level::Trace: return Color::BrightBlack;
            case Level::Debug: return Color::Cyan;
            case Level::Info: return Color::Green;
            case Level::Warn: return Color::Yellow;
            case Level::Error: return Color::Red;
            case Level::Critical: return Color::BrightRed;
            default: return Color::Default;
        }
    }

    bool supports_color() {
        #ifdef _WIN32
            return _isatty(_fileno(stdout));
        #else
            const char* term = std::getenv("TERM");
            return term && std::string(term) != "dumb" && isatty(fileno(stdout));
        #endif
    }

    ConsoleColor::ConsoleColor(ColorMode mode) : mode_(mode) {
        reset_level_colors();
    }

    void ConsoleColor::set_mode(ColorMode mode) {
        mode_ = mode;
    }

    void ConsoleColor::set_level_color(Level level, Color color, Style style) {
        auto index = static_cast<size_t>(level);
        if (index < 6) {
            level_colors_[index] = {color, style};
        }
    }

    void ConsoleColor::reset_level_colors() {
        for (int i = 0; i < 6; ++i) {
            level_colors_[i] = {
                default_level_color(static_cast<Level>(i)),
                Style::Normal
            };
        }
    }

    std::string ConsoleColor::color_for_level(Level level) const {
        if (mode_ == ColorMode::Never) {
            return {};
        }

        if (mode_ == ColorMode::Auto && !supports_color()) {
            return {};
        }

        auto index = static_cast<size_t>(level);
        if (index >= 6) {
            return {};
        }

        const auto& lc = level_colors_[index];
        return to_ansi_code(lc.style) + to_ansi_code(lc.color);
    }

    std::string ConsoleColor::reset() const {
        if (mode_ == ColorMode::Never) {
            return {};
        }

        if (mode_ == ColorMode::Auto && !supports_color()) {
            return {};
        }

        return to_ansi_code(Style::Reset);
    }
}
