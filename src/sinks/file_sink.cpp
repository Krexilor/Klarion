// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <stdexcept>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/sinks/file_sink.hpp"
#include "klarion/detail/filesystem/path_utils.hpp"

// FILE SINK IMPLEMENTATION ------------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    FileSink::FileSink(const std::string& path, bool append) : path_(path) {
        detail::ensure_parent_directory_exists(path);

        file_.open(path, append ? std::ios::app : std::ios::trunc);
        if (!file_.is_open()) {
            throw std::runtime_error("Failed to open log file: " + path);
        }

        set_pattern("[%time] [%level] [%logger] [%file:%line] %msg");
    }

    FileSink::~FileSink() {
        try {
            flush();
            if (file_.is_open()) {
                file_.close();
            }
        }
        catch (...) {
            // Ignore errors during cleanup
        }
    }

    void FileSink::write(const LogRecord& record) {
        if (!should_log(record.level)) {
            return;
        }

        std::lock_guard<std::mutex> lock(mutex_);

        if (file_.is_open()) {
            file_ << formatter_.format(record) << "\n";

            if (immediate_flush_) {
                file_.flush();
            }
        }
    }

    void FileSink::set_pattern(const std::string& pattern) {
        std::lock_guard<std::mutex> lock(mutex_);
        formatter_.set_pattern(pattern);
        pattern_ = pattern;
    }

    void FileSink::flush() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (file_.is_open()) {
            file_.flush();
        }
    }

    void FileSink::set_immediate_flush(bool immediate) {
        immediate_flush_ = immediate;
    }
}
