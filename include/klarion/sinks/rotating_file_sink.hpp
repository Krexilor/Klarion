#pragma once

// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <mutex>
#include <string>
#include <fstream>
#include <cstddef>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/sinks/sink.hpp"
#include "klarion/detail/formatting/pattern_formatter.hpp"

// ROTATING FILE SINK DEFINITION -------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    class RotatingFileSink : public Sink {
        public:
            RotatingFileSink(const std::string& path, std::size_t max_size_bytes, int max_files);
            ~RotatingFileSink();

            void write(const LogRecord& record) override;
            void flush() override;
            void set_pattern(const std::string& pattern) override;
            void set_immediate_flush(bool immediate);

        private:
            void rotate();
            static std::string rotated_path(const std::string& path, int index);

            std::ofstream file_;
            std::string path_;
            std::size_t max_size_bytes_;
            int max_files_;
            std::size_t current_size_{0};
            detail::PatternFormatter formatter_;
            std::mutex mutex_;
            bool immediate_flush_{false};
    };
}
