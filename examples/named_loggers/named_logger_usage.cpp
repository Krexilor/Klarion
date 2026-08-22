// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <memory>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/klarion.hpp"

// NAMED LOGGER EXAMPLE ----------------------------------------------------------------------------------------------------------------------------|
int main() {
    klarion::init();

    LOG_INFO("Default logger says hello");

    // A named logger has its own independent level and sinks.
    // Note: a sink's own level acts as a hard cap regardless of the logger's level, so the sink must also be lowered explicitly.
    auto net = klarion::get("network");
    auto net_sink = std::make_shared<klarion::ConsoleSink>();
    net_sink->set_level(klarion::Level::Debug);
    net->add_sink(net_sink);
    net->set_level(klarion::Level::Debug);

    LOG_TO_DEBUG("network", "Connecting to {}:{}", "127.0.0.1", 8080);
    LOG_TO_INFO("network", "Connected successfully");

    klarion::shutdown();
    return 0;
}
