#pragma once

// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <string_view>

// SOURCE LOCATION DEFINITION ----------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    struct SourceLocation {
        std::string_view file{"unknown"};
        int line{0};
        std::string_view function{"unknown"};

        constexpr SourceLocation() = default;

        constexpr SourceLocation(
            std::string_view file_,
            int line_,
            std::string_view function_
        ) : 
        file(file_), line(line_), function(function_) {}

        constexpr std::string_view filename() const noexcept {
            std::string_view::size_type pos = file.find_last_of("/\\");
            if (pos != std::string_view::npos) {
                return file.substr(pos + 1);
            }
            return file;
        }
    };
}

// Macro to capture current source location
#define KLARION_SOURCE_LOCATION() \
    ::klarion::SourceLocation(__FILE__, __LINE__, __func__)
