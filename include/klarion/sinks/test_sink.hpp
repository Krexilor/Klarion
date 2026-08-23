#pragma once

// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <mutex>
#include <vector>
#include <string>
#include <cstddef>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/sinks/sink.hpp"

// TEST SINK DEFINITION ----------------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    class TestSink : public Sink {
        public:
            TestSink();

            void write(const LogRecord& record) override;
            void flush() override;

            std::vector<LogRecord> records() const;
            std::size_t count() const;
            void clear();
            bool contains(const std::string& substring) const;

        private:
            mutable std::mutex mutex_;
            std::vector<LogRecord> records_;
    };
}
