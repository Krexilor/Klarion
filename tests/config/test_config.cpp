// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <cassert>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/config/config.hpp"

// CONFIG TESTS ------------------------------------------------------------------------------------------------------------------------------------|
int main() {
    klarion::Config config = klarion::Config::from_toml_string(R"(
        [default]
        level = "debug"
        sinks = ["console"]

        [sinks.console]
        type = "console"
        pattern = "%msg"
    )");

    assert(config.level() == klarion::Level::Debug);
    assert(config.sinks().size() == 1);
    assert(config.sinks()[0].name == "console");
    assert(config.sinks()[0].type == "console");
    assert(config.default_sinks().size() == 1);
    assert(config.default_sinks()[0] == "console");
    return 0;
}
