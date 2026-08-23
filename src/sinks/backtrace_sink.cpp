// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/sinks/backtrace_sink.hpp"

// BACKTRACE SINK IMPLEMENTATION -------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    BacktraceSink::BacktraceSink(std::size_t capacity)
        : capacity_(capacity == 0 ? 1 : capacity) {
        buffer_.resize(capacity_);
    }

    void BacktraceSink::write(const LogRecord& record) {
        if (!should_log(record.level)) {
            return;
        }

        std::lock_guard<std::mutex> lock(mutex_);

        buffer_[next_index_] = record;
        next_index_ = (next_index_ + 1) % capacity_;

        if (next_index_ == 0) {
            full_ = true;
        }
    }

    void BacktraceSink::flush() {
        // No-op: purely in-memory, nothing to flush.
    }

    void BacktraceSink::dump_to(const SinkPtr& target) const {
        if (!target) {
            return;
        }

        std::lock_guard<std::mutex> lock(mutex_);

        std::size_t count = full_ ? capacity_ : next_index_;
        std::size_t start = full_ ? next_index_ : 0;

        for (std::size_t i = 0; i < count; ++i) {
            std::size_t index = (start + i) % capacity_;
            target->write(buffer_[index]);
        }
    }

    void BacktraceSink::clear() {
        std::lock_guard<std::mutex> lock(mutex_);
        next_index_ = 0;
        full_ = false;
    }

    std::size_t BacktraceSink::size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return full_ ? capacity_ : next_index_;
    }
}
