// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <cassert>
#include <cstdlib>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/config/config.hpp"

// ENVIRONMENT OVERRIDE TESTS ----------------------------------------------------------------------------------------------------------------------|
namespace {
    void set_env(const char* name, const char* value) {
        #if defined(_WIN32)
            _putenv_s(name, value);
        #else
            setenv(name, value, 1);
        #endif
    }

    void unset_env(const char* name) {
        #if defined(_WIN32)
            _putenv_s(name, "");
        #else
            unsetenv(name);
        #endif
    }
}

int main() {
    set_env("KLARION_LEVEL", "debug");

    klarion::Config config;
    assert(config.level() == klarion::Level::Debug);

    unset_env("KLARION_LEVEL");

    set_env("KLARION_LEVEL_NETWORK", "trace");

    klarion::Config toml_config = klarion::Config::from_toml_string(R"(
        [default]
        level = "info"

        [loggers.network]
        level = "warn"
    )");

    bool found = false;
    for (const auto& logger : toml_config.loggers()) {
        if (logger.name == "network") {
            found = true;
            assert(logger.level == klarion::Level::Trace);
        }
    }
    assert(found);

    unset_env("KLARION_LEVEL_NETWORK");
    return 0;
}
