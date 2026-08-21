#pragma once

// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <string>
#include <vector>
#include <memory>
#include <functional>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/core/record.hpp"
#include "klarion/detail/terminal/console_color.hpp"

// PATTERN FORMATTER DEFINITION --------------------------------------------------------------------------------------------------------------------|
namespace klarion::detail {
    class PatternFormatter {
        public:
            using FormatterFunc = std::function<std::string(const LogRecord&)>;

            PatternFormatter();
            explicit PatternFormatter(const std::string& pattern);

            void set_pattern(const std::string& pattern);
            std::string format(const LogRecord& record) const;
            std::string format(const LogRecord& record, const ConsoleColor& colorizer) const;

        private:
            void parse_pattern(const std::string& pattern);

            std::string pattern_;
            std::vector<FormatterFunc> formatters_;
    };
}
