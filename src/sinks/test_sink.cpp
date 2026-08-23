// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/sinks/test_sink.hpp"

// TEST SINK IMPLEMENTATION ------------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    TestSink::TestSink() {
        set_level(Level::Trace);
    }

    void TestSink::write(const LogRecord& record) {
        if (!should_log(record.level)) {
            return;
        }

        std::lock_guard<std::mutex> lock(mutex_);
        records_.push_back(record);
    }

    void TestSink::flush() {
        // No-op: purely in-memory, nothing to flush.
    }

    std::vector<LogRecord> TestSink::records() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return records_;
    }

    std::size_t TestSink::count() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return records_.size();
    }

    void TestSink::clear() {
        std::lock_guard<std::mutex> lock(mutex_);
        records_.clear();
    }

    bool TestSink::contains(const std::string& substring) const {
        std::lock_guard<std::mutex> lock(mutex_);

        for (const auto& record : records_) {
            if (record.message.find(substring) != std::string::npos) {
                return true;
            }
        }

        return false;
    }
}
