// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/klarion.hpp"

// JSON SINK EXAMPLE -------------------------------------------------------------------------------------------------------------------------------|
int main() {
    klarion::init();

    auto json_sink = std::make_shared<klarion::JsonSink>("logs/app.jsonl");
    json_sink->set_level(klarion::Level::Info);

    auto logger = klarion::get("api");
    logger->add_sink(json_sink);
    logger->set_level(klarion::Level::Info);

    LOG_TO_INFO_KV("api", "Request handled",
        klarion::kv("status", 200),
        klarion::kv("duration_ms", 12.5),
        klarion::kv("cached", false)
    );

    klarion::shutdown();
    return 0;
}
