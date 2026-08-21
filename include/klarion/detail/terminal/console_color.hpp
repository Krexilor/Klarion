#pragma once

// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <string>
#include <string_view>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/core/level.hpp"

// CONSOLE COLOR DEFINITION ------------------------------------------------------------------------------------------------------------------------|
namespace klarion::detail {
    enum class ColorMode {
        Auto, Always, Never
    };

    enum class Color {
        Default,
        Black,
        Red,
        Green,
        Yellow,
        Blue,
        Magenta,
        Cyan,
        White,
        BrightBlack,
        BrightRed,
        BrightGreen,
        BrightYellow,
        BrightBlue,
        BrightMagenta,
        BrightCyan,
        BrightWhite
    };

    enum class Style {
        Reset, Bold, Dim, Normal
    };

    // Convert color to ANSI code string
    std::string to_ansi_code(Color color);
    std::string to_ansi_code(Style style);

    // Get default color for a log level
    Color default_level_color(Level level);

    // Check if terminal supports colors
    bool supports_color();

    // Color formatter for console output
    class ConsoleColor {
        public:
            ConsoleColor(ColorMode mode = ColorMode::Auto);

            void set_mode(ColorMode mode);
            ColorMode mode() const { return mode_; }

            void set_level_color(Level level, Color color, Style style = Style::Normal);
            void reset_level_colors();

            std::string color_for_level(Level level) const;
            std::string reset() const;

        private:
        bool colors_active() const;
            ColorMode mode_;
            struct LevelColor {
                Color color{Color::Default};
                Style style{Style::Normal};
            };
            LevelColor level_colors_[6];
    };
}
