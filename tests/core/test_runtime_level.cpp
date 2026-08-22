// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <memory>
#include <cassert>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/sinks/sink.hpp"
#include "klarion/core/logger.hpp"

// TEST SINK ---------------------------------------------------------------------------------------------------------------------------------------|
namespace {
    class CountingSink : public klarion::Sink {
        public:
            int count = 0;
            void write(const klarion::LogRecord&) override { ++count; }
            void flush() override {}
    };
}

// RUNTIME LEVEL TESTS -----------------------------------------------------------------------------------------------------------------------------|
int main() {
    klarion::Logger logger("test");
    auto sink = std::make_shared<CountingSink>();
    sink->set_level(klarion::Level::Trace);
    logger.add_sink(sink);
    logger.set_level(klarion::Level::Info);

    logger.log(klarion::Level::Debug, "filtered", {});
    assert(sink->count == 0);

    logger.set_level(klarion::Level::Debug);
    logger.log(klarion::Level::Debug, "now allowed", {});
    assert(sink->count == 1);

    logger.set_level(klarion::Level::Critical);
    logger.log(klarion::Level::Error, "filtered again", {});
    assert(sink->count == 1);

    return 0;
}
