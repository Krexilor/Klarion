// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <thread>
#include <sstream>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/detail/time/timestamp.hpp"
#include "klarion/detail/formatting/pattern_formatter.hpp"

// PATTERN FORMATTER IMPLEMENTATION ----------------------------------------------------------------------------------------------------------------|
namespace klarion::detail {
    PatternFormatter::PatternFormatter() {
        set_pattern("[%time] [%level] [%logger] %msg");
    }

    PatternFormatter::PatternFormatter(const std::string& pattern) {
        set_pattern(pattern);
    }

    void PatternFormatter::set_pattern(const std::string& pattern) {
        pattern_ = pattern;
        parse_pattern(pattern);
    }

    std::string PatternFormatter::format(const LogRecord& record) const {
        std::ostringstream oss;
        for (const auto& formatter : formatters_) {
            oss << formatter(record);
        }
        return oss.str();
    }

    std::string PatternFormatter::format(const LogRecord& record, const ConsoleColor& colorizer) const {
        std::ostringstream oss;
        oss << colorizer.color_for_level(record.level);

        for (const auto& formatter : formatters_) {
            oss << formatter(record);
        }

        oss << colorizer.reset();

        return oss.str();
    }

    void PatternFormatter::parse_pattern(const std::string& pattern) {
        formatters_.clear();

        size_t pos = 0;
        while (pos < pattern.size()) {
            if (pattern[pos] == '%') {
                size_t end = pos + 1;
                while (end < pattern.size() && std::isalpha(static_cast<unsigned char>(pattern[end]))) {
                    ++end;
                }

                std::string placeholder = pattern.substr(pos + 1, end - pos - 1);

                if (placeholder == "time") {
                    formatters_.push_back([](const LogRecord& r) {
                        return format_timestamp(r.timestamp);
                    });
                }
                else if (placeholder == "level") {
                    formatters_.push_back([](const LogRecord& r) {
                        return std::string(to_string(r.level));
                    });
                }
                else if (placeholder == "logger") {
                    formatters_.push_back([](const LogRecord& r) {
                        return r.logger_name;
                    });
                }
                else if (placeholder == "msg") {
                    formatters_.push_back([](const LogRecord& r) {
                        return r.message;
                    });
                }
                else if (placeholder == "thread") {
                    formatters_.push_back([](const LogRecord& r) {
                        std::ostringstream oss;
                        oss << r.thread_id;
                        return oss.str();
                    });
                }
                else if (placeholder == "file") {
                    formatters_.push_back([](const LogRecord& r) {
                        return std::string(r.location.filename());
                    });
                }
                else if (placeholder == "line") {
                    formatters_.push_back([](const LogRecord& r) {
                        return std::to_string(r.location.line);
                    });
                }
                else if (placeholder == "func") {
                    formatters_.push_back([](const LogRecord& r) {
                        return std::string(r.location.function);
                    });
                }
                else {
                    formatters_.push_back([text = "%" + placeholder](const LogRecord&) {
                        return text;
                    });
                }

                pos = end;
            }
            else {
                char c = pattern[pos];
                formatters_.push_back([c](const LogRecord&) {
                    return std::string(1, c);
                });
                ++pos;
            }
        }
    }
}
