// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <memory>
#include <cassert>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/sinks/test_sink.hpp"
#include "klarion/sinks/backtrace_sink.hpp"

// BACKTRACE SINK TESTS ----------------------------------------------------------------------------------------------------------------------------|
int main() {
    klarion::BacktraceSink backtrace(3);
    backtrace.set_level(klarion::Level::Trace);

    for (int i = 0; i < 5; ++i) {
        klarion::LogRecord record(klarion::Level::Info, "msg" + std::to_string(i), "test", {});
        backtrace.write(record);
    }

    assert(backtrace.size() == 3);

    auto capture = std::make_shared<klarion::TestSink>();
    backtrace.dump_to(capture);

    auto records = capture->records();
    assert(records.size() == 3);
    assert(records[0].message == "msg2");
    assert(records[1].message == "msg3");
    assert(records[2].message == "msg4");

    return 0;
}
