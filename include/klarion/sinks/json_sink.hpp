#pragma once

// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <mutex>
#include <string>
#include <fstream>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/sinks/sink.hpp"
#include "klarion/core/field.hpp"

// JSON SINK DEFINITION ----------------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    class JsonSink : public Sink {
        public:
            explicit JsonSink(const std::string& path, bool append = true);
            ~JsonSink();

            void write(const LogRecord& record) override;
            void flush() override;
            void set_pattern(const std::string& pattern) override;

        private:
            std::ofstream file_;
            std::string path_;
            std::mutex mutex_;
    };
}
