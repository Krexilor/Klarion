// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <memory>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/klarion.hpp"
#include "klarion/core/macros.hpp"
#include "klarion/sinks/console_sink.hpp"

// BASIC USAGE EXAMPLE -----------------------------------------------------------------------------------------------------------------------------|
int main() {
    klarion::init();

    LOG_TRACE("This won't show (below default level)");
    LOG_INFO("Application started");
    LOG_WARN("Something looks off: {}", 42);
    LOG_ERROR("Failed with code {}", -1);

    auto net = klarion::get("network");
    auto net_sink = std::make_shared<klarion::ConsoleSink>();
    net_sink->set_level(klarion::Level::Debug);
    net->add_sink(net_sink);
    net->set_level(klarion::Level::Debug);
    LOG_TO_DEBUG("network", "Connecting to {}:{}", "127.0.0.1", 8080);

    klarion::Klarion::init(
        klarion::Config{}
            .set_level(klarion::Level::Debug)
            .add_console_sink()
            .add_file_sink("logs/app.log")
    );
    LOG_DEBUG("Now writing to console and file");

    klarion::shutdown();
    return 0;
}
