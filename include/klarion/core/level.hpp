#pragma once

// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <cctype>
#include <string>
#include <string_view>

// LEVEL DEFINITION --------------------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    enum class Level {
        Trace = 0,
        Debug = 1,
        Info = 2,
        Warn = 3,
        Error = 4,
        Critical = 5
    };

    // Convert level to string representation
    constexpr std::string_view to_string(Level level) noexcept {
        switch (level) {
            case Level::Trace: return "trace";
            case Level::Debug: return "debug";
            case Level::Info: return "info";
            case Level::Warn: return "warn";
            case Level::Error: return "error";
            case Level::Critical: return "critical";
            default: return "unknown";
        }
    }

    // Convert string to level (case-insensitive)
    inline Level level_from_string(std::string_view str) {
        std::string lower;
        lower.reserve(str.size());
        for (char c : str) {
            lower.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(c))));
        }

        if (lower == "trace") return Level::Trace;
        if (lower == "debug") return Level::Debug;
        if (lower == "info") return Level::Info;
        if (lower == "warn") return Level::Warn;
        if (lower == "error") return Level::Error;
        if (lower == "critical") return Level::Critical;

        return Level::Info;
    }

    // Check if a level is enabled given a threshold
    constexpr bool is_enabled(Level level, Level threshold) noexcept {
        return static_cast<int>(level) >= static_cast<int>(threshold);
    }
}
