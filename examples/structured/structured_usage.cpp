// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <memory>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/klarion.hpp"
#include "klarion/core/macros.hpp"
#include "klarion/sinks/console_sink.hpp"

// STRUCTURED LOGGING EXAMPLE ----------------------------------------------------------------------------------------------------------------------|
int main() {
    klarion::init();

    LOG_INFO_KV("User login",
        klarion::kv("user_id", 42),
        klarion::kv("ip", "127.0.0.1")
    );

    auto net = klarion::get("network");
    auto net_sink = std::make_shared<klarion::ConsoleSink>();
    net_sink->set_level(klarion::Level::Debug);
    net->add_sink(net_sink);
    net->set_level(klarion::Level::Debug);

    LOG_TO_DEBUG_KV("network", "Connection established",
        klarion::kv("host", "example.com"),
        klarion::kv("port", 443)
    );

    klarion::shutdown();
    return 0;
}
