// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/klarion.hpp"

// TOML USAGE EXAMPLE ------------------------------------------------------------------------------------------------------------------------------|
int main() {
    klarion::init("example_config.toml");
    LOG_INFO("Loaded from TOML");
    klarion::shutdown();
    return 0;
}
