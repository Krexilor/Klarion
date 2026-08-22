// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <memory>
#include <cassert>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/core/field.hpp"
#include "klarion/sinks/sink.hpp"
#include "klarion/core/logger.hpp"

// TEST SINK ---------------------------------------------------------------------------------------------------------------------------------------|
namespace {
    class CapturingSink : public klarion::Sink {
        public:
            klarion::LogRecord last_record;
            void write(const klarion::LogRecord& record) override { last_record = record; }
            void flush() override {}
    };
}

// STRUCTURED FIELD TESTS --------------------------------------------------------------------------------------------------------------------------|
int main() {
    klarion::Logger logger("test");
    auto sink = std::make_shared<CapturingSink>();
    logger.add_sink(sink);
    logger.set_level(klarion::Level::Info);

    logger.log(
        klarion::Level::Info,
        "User login",
        {},
        { klarion::kv("user_id", 42), klarion::kv("ip", "127.0.0.1") }
    );

    assert(sink->last_record.fields.size() == 2);
    assert(sink->last_record.fields[0].key == "user_id");
    assert(sink->last_record.fields[0].value == "42");
    assert(sink->last_record.fields[1].key == "ip");
    assert(sink->last_record.fields[1].value == "127.0.0.1");

    return 0;
}
