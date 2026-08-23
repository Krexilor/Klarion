// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <cassert>
#include <fstream>
#include <sstream>
#include <filesystem>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/core/field.hpp"
#include "klarion/sinks/json_sink.hpp"

namespace fs = std::filesystem;

// JSON SINK TESTS ---------------------------------------------------------------------------------------------------------------------------------|
int main() {
    const std::string path = (fs::temp_directory_path() / "klarion_test_output.jsonl").string();

    std::error_code ec;
    fs::remove(path, ec);

    {
        klarion::JsonSink sink(path, false);
        sink.set_level(klarion::Level::Trace);

        klarion::LogRecord record(
            klarion::Level::Info,
            "User login",
            "auth",
            {},
            { klarion::kv("user_id", 42), klarion::kv("active", true) }
        );

        sink.write(record);
        sink.flush();
    }

    std::ifstream file(path, std::ios::in);
    assert(file.is_open());

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    assert(content.find("\"message\":\"User login\"") != std::string::npos);
    assert(content.find("\"user_id\":42") != std::string::npos);
    assert(content.find("\"active\":true") != std::string::npos);

    fs::remove(path, ec);
    return 0;
}
