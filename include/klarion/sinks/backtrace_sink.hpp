#pragma once

// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <mutex>
#include <vector>
#include <cstddef>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/sinks/sink.hpp"

// BACKTRACE SINK DEFINITION -----------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    class BacktraceSink : public Sink {
        public:
            explicit BacktraceSink(std::size_t capacity);

            void write(const LogRecord& record) override;
            void flush() override;

            void dump_to(const SinkPtr& target) const;

            void clear();
            std::size_t size() const;

        private:
            std::size_t capacity_;
            std::size_t next_index_{0};
            bool full_{false};
            std::vector<LogRecord> buffer_;
            mutable std::mutex mutex_;
    };
}
