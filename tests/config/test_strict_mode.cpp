// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <cassert>
#include <stdexcept>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/config/config.hpp"

// STRICT MODE TESTS -------------------------------------------------------------------------------------------------------------------------------|
int main() {
    // Non-strict: unknown key silently ignored
    klarion::Config lenient = klarion::Config::from_toml_string(R"(
        [default]
        level = "info"
        unknown_key = "oops"
    )", false);
    assert(lenient.level() == klarion::Level::Info);

    // Strict: unknown key throws
    bool threw = false;
    try {
        klarion::Config::from_toml_string(R"(
            [default]
            level = "info"
            unknown_key = "oops"
        )", true);
    }
    catch (const std::runtime_error&) {
        threw = true;
    }
    assert(threw);

    return 0;
}
