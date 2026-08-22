// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/klarion.hpp"
#include "klarion/core/macros.hpp"

// RUNTIME CONTROL EXAMPLE -------------------------------------------------------------------------------------------------------------------------|
int main() {
    klarion::Config config;
    config.set_level(klarion::Level::Debug);
    config.add_console_sink();
    config.set_level(klarion::Level::Info);

    klarion::init(config);

    LOG_INFO("Starting up at info level");
    LOG_DEBUG("This won't show yet");

    klarion::set_level(klarion::Level::Debug);
    LOG_DEBUG("Now visible after runtime level change");

    klarion::reload(
        klarion::Config{}
            .set_level(klarion::Level::Warn)
            .add_console_sink()
    );

    LOG_INFO("This is now suppressed after reload");
    LOG_WARN("This still shows after reload");

    klarion::shutdown();
    return 0;
}
