// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <cassert>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/sinks/test_sink.hpp"

// TEST SINK SELF-TESTS ----------------------------------------------------------------------------------------------------------------------------|
int main() {
    klarion::TestSink sink;

    klarion::LogRecord record(klarion::Level::Info, "hello world", "test", {});
    sink.write(record);

    assert(sink.count() == 1);
    assert(sink.contains("hello"));
    assert(!sink.contains("goodbye"));

    sink.clear();
    assert(sink.count() == 0);

    return 0;
}
