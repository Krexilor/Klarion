// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <string>
#include <cassert>
#include <filesystem>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/sinks/rotating_file_sink.hpp"

namespace fs = std::filesystem;

// ROTATING FILE SINK TESTS ------------------------------------------------------------------------------------------------------------------------|
int main() {
    const std::string path = "test_rotating.log";

    fs::remove(path);
    fs::remove("test_rotating.1.log");
    fs::remove("test_rotating.2.log");

    {
        klarion::RotatingFileSink sink(path, /*max_size_bytes=*/50, /*max_files=*/2);
        sink.set_level(klarion::Level::Trace);

        for (int i = 0; i < 10; ++i) {
            klarion::LogRecord record(klarion::Level::Info, "Message number " + std::to_string(i), "test", {});
            sink.write(record);
        }

        sink.flush();
    }

    assert(fs::exists(path));
    assert(fs::exists("test_rotating.1.log"));

    fs::remove(path);
    fs::remove("test_rotating.1.log");
    fs::remove("test_rotating.2.log");

    return 0;
}
