// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <cstdio>
#include <stdexcept>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/sinks/rotating_file_sink.hpp"
#include "klarion/detail/filesystem/path_utils.hpp"

// ROTATING FILE SINK IMPLEMENTATION ---------------------------------------------------------------------------------------------------------------|
namespace klarion {
    RotatingFileSink::RotatingFileSink(const std::string& path, std::size_t max_size_bytes, int max_files)
        : path_(path), max_size_bytes_(max_size_bytes), max_files_(max_files) {
        if (max_files_ < 1) {
            max_files_ = 1;
        }

        detail::ensure_parent_directory_exists(path_);

        file_.open(path_, std::ios::app);
        if (!file_.is_open()) {
            throw std::runtime_error("Failed to open log file: " + path_);
        }

        current_size_ = static_cast<std::size_t>(file_.tellp());
        set_pattern("[%time] [%level] [%logger] [%file:%line] %msg");
    }

    RotatingFileSink::~RotatingFileSink() {
        try {
            flush();
            if (file_.is_open()) {
                file_.close();
            }
        }
        catch (...) {
            // Ignore errors during cleanup.
        }
    }

    std::string RotatingFileSink::rotated_path(const std::string& path, int index) {
        size_t slash = path.find_last_of("/\\");
        std::string dir = (slash == std::string::npos) ? "" : path.substr(0, slash + 1);
        std::string filename = (slash == std::string::npos) ? path : path.substr(slash + 1);

        size_t dot = filename.find_last_of('.');
        std::string stem = (dot == std::string::npos) ? filename : filename.substr(0, dot);
        std::string ext = (dot == std::string::npos) ? "" : filename.substr(dot);

        return dir + stem + "." + std::to_string(index) + ext;
    }

    void RotatingFileSink::rotate() {
        if (file_.is_open()) {
            file_.close();
        }

        std::string oldest = rotated_path(path_, max_files_);
        std::remove(oldest.c_str());

        for (int i = max_files_ - 1; i >= 1; --i) {
            std::string src = rotated_path(path_, i);
            std::string dst = rotated_path(path_, i + 1);
            std::remove(dst.c_str());
            std::rename(src.c_str(), dst.c_str());
        }

        std::string first_rotated = rotated_path(path_, 1);
        std::remove(first_rotated.c_str());
        std::rename(path_.c_str(), first_rotated.c_str());

        file_.open(path_, std::ios::trunc);
        current_size_ = 0;
    }

    void RotatingFileSink::write(const LogRecord& record) {
        if (!should_log(record.level)) {
            return;
        }

        std::lock_guard<std::mutex> lock(mutex_);

        if (!file_.is_open()) {
            return;
        }

        if (current_size_ >= max_size_bytes_) {
            rotate();
        }

        std::string formatted = formatter_.format(record) + "\n";
        file_ << formatted;
        current_size_ += formatted.size();

        if (immediate_flush_) {
            file_.flush();
        }
    }

    void RotatingFileSink::set_pattern(const std::string& pattern) {
        std::lock_guard<std::mutex> lock(mutex_);
        formatter_.set_pattern(pattern);
        pattern_ = pattern;
    }

    void RotatingFileSink::flush() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (file_.is_open()) {
            file_.flush();
        }
    }

    void RotatingFileSink::set_immediate_flush(bool immediate) {
        immediate_flush_ = immediate;
    }
}
