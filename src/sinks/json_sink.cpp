// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <cstdio>
#include <sstream>
#include <stdexcept>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/sinks/json_sink.hpp"
#include "klarion/detail/time/timestamp.hpp"
#include "klarion/detail/filesystem/path_utils.hpp"

// JSON SINK IMPLEMENTATION ------------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    namespace {
        std::string escape_json(const std::string& input) {
            std::ostringstream oss;

            for (unsigned char c : input) {
                switch (c) {
                    case '"':  oss << "\\\""; break;
                    case '\\': oss << "\\\\"; break;
                    case '\n': oss << "\\n"; break;
                    case '\r': oss << "\\r"; break;
                    case '\t': oss << "\\t"; break;
                    default:
                        if (c < 0x20) {
                            char buf[7];
                            std::snprintf(buf, sizeof(buf), "\\u%04x", c);
                            oss << buf;
                        }
                        else {
                            oss << static_cast<char>(c);
                        }
                }
            }

            return oss.str();
        }
    }

    JsonSink::JsonSink(const std::string& path, bool append) : path_(path) {
        detail::ensure_parent_directory_exists(path_);

        file_.open(path_, append ? std::ios::app : std::ios::trunc);
        if (!file_.is_open()) {
            throw std::runtime_error("Failed to open JSON log file: " + path_);
        }
    }

    JsonSink::~JsonSink() {
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

    void JsonSink::write(const LogRecord& record) {
        if (!should_log(record.level)) {
            return;
        }

        std::lock_guard<std::mutex> lock(mutex_);

        if (!file_.is_open()) {
            return;
        }

        std::ostringstream oss;
        oss << "{";
        oss << "\"time\":\"" << detail::format_timestamp(record.timestamp) << "\",";
        oss << "\"level\":\"" << to_string(record.level) << "\",";
        oss << "\"logger\":\"" << escape_json(record.logger_name) << "\",";
        oss << "\"message\":\"" << escape_json(record.message) << "\"";

        if (!record.fields.empty()) {
            oss << ",\"fields\":{";

            for (size_t i = 0; i < record.fields.size(); ++i) {
                if (i > 0) oss << ",";

                const auto& field = record.fields[i];
                oss << "\"" << escape_json(field.key) << "\":";

                switch (field.kind) {
                    case FieldKind::Int:
                    case FieldKind::Float:
                        oss << field.value;
                        break;
                    case FieldKind::Bool:
                        oss << (field.value == "true" ? "true" : "false");
                        break;
                    case FieldKind::String:
                    default:
                        oss << "\"" << escape_json(field.value) << "\"";
                        break;
                }
            }

            oss << "}";
        }

        oss << "}\n";

        file_ << oss.str();
        file_.flush();
    }

    void JsonSink::flush() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (file_.is_open()) {
            file_.flush();
        }
    }

    void JsonSink::set_pattern(const std::string&) {
        // JSON output has a fixed structure; text patterns do not apply.
    }
}
