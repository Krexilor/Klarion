// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/klarion.hpp"

// BASIC USAGE EXAMPLE -----------------------------------------------------------------------------------------------------------------------------|
int main() {
    klarion::init();

    LOG_TRACE("This won't show (below default level)");
    LOG_INFO("Application started");
    LOG_WARN("Something looks off: {}", 42);
    LOG_ERROR("Failed with code {}", -1);
    LOG_CRITICAL("Support for multiple args: {} {}", "still", "simple");

    klarion::shutdown();
    return 0;
}
