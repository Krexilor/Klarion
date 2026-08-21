// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <cassert>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/core/level.hpp"

// LEVEL TESTS -------------------------------------------------------------------------------------------------------------------------------------|
int main() {
    assert(klarion::level_from_string("debug") == klarion::Level::Debug);
    assert(klarion::level_from_string("DEBUG") == klarion::Level::Debug);
    assert(klarion::level_from_string("garbage") == klarion::Level::Info);
    assert(klarion::is_enabled(klarion::Level::Error, klarion::Level::Warn));
    assert(!klarion::is_enabled(klarion::Level::Trace, klarion::Level::Warn));
    return 0;
}
