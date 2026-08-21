#pragma once

// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <ctime>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

// TIMESTAMP DEFINITION ----------------------------------------------------------------------------------------------------------------------------|
namespace klarion::detail {
    inline std::string format_timestamp(std::chrono::system_clock::time_point tp) {
        const std::time_t time_t_val = std::chrono::system_clock::to_time_t(tp);
        const long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count() % 1000;

        std::tm tm_buf;

        #if defined(_WIN32) || defined(_MSC_VER)
            localtime_s(&tm_buf, &time_t_val);
        #else
            localtime_r(&time_t_val, &tm_buf);
        #endif

        std::ostringstream oss;
        oss << std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S");
        oss << '.' << std::setfill('0') << std::setw(3) << ms;

        return oss.str();
    }
}
