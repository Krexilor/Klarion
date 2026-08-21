#pragma once

// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <mutex>
#include <string>
#include <fstream>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/sinks/sink.hpp"
#include "klarion/detail/formatting/pattern_formatter.hpp"

// FILE SINK DEFINITION ----------------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    class FileSink : public Sink {
        public:
            FileSink(const std::string& path, bool append = true);
            ~FileSink();

            void write(const LogRecord& record) override;
            void flush() override;

            void set_pattern(const std::string& pattern) override;
            void set_immediate_flush(bool immediate);
        
        private:
            std::ofstream file_;
            std::string path_;
            detail::PatternFormatter formatter_;
            std::mutex mutex_;
            bool immediate_flush_{false};
    };
}
