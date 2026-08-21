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

// LOGGER TESTS ------------------------------------------------------------------------------------------------------------------------------------|
int main() {
    klarion::Logger logger("test");
    auto sink = std::make_shared<CountingSink>();
    logger.add_sink(sink);
    logger.set_level(klarion::Level::Info);

    logger.log(klarion::Level::Debug, "should be filtered", {});
    logger.log(klarion::Level::Info, "should log", {});

    assert(sink->count == 1);
    return 0;
}
