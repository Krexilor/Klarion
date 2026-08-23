// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/klarion.hpp"

// BACKTRACE SINK EXAMPLE --------------------------------------------------------------------------------------------------------------------------|
int main() {
    klarion::init();

    auto backtrace = std::make_shared<klarion::BacktraceSink>(20);
    backtrace->set_level(klarion::Level::Trace);

    auto logger = klarion::get("worker");
    logger->add_sink(backtrace);
    logger->set_level(klarion::Level::Trace);

    for (int i = 0; i < 100; ++i) {
        LOG_TO_DEBUG("worker", "Processing step {}", i);
    }

    // Something went wrong — dump the last messages leading up to it.
    auto console_sink = std::make_shared<klarion::ConsoleSink>();
    console_sink->set_level(klarion::Level::Trace);
    backtrace->dump_to(console_sink);

    klarion::shutdown();
    return 0;
}
