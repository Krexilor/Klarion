// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/klarion.hpp"

// ROTATING FILE SINK EXAMPLE ----------------------------------------------------------------------------------------------------------------------|
int main() {
    klarion::init();

    auto rotating = std::make_shared<klarion::RotatingFileSink>("logs/rotating.log", /*max_size_bytes=*/1024, /*max_files=*/3);
    rotating->set_level(klarion::Level::Info);

    auto logger = klarion::get("rotator");
    logger->add_sink(rotating);
    logger->set_level(klarion::Level::Info);

    for (int i = 0; i < 50; ++i) {
        LOG_TO_INFO("rotator", "Writing log entry number {}", i);
    }

    klarion::shutdown();
    return 0;
}
