// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <cctype>
#include <iostream>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/klarion.hpp"

// CUSTOM SINK EXAMPLE -----------------------------------------------------------------------------------------------------------------------------|
namespace {
    // A minimal custom sink: uppercases every message before printing it.
    class UppercaseSink : public klarion::Sink {
        public:
            void write(const klarion::LogRecord& record) override {
                if (!should_log(record.level)) {
                    return;
                }

                std::string upper = record.message;
                for (char& c : upper) {
                    c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
                }

                std::cout << "[" << klarion::to_string(record.level) << "] " << upper << "\n";
            }

            void flush() override {
                std::cout.flush();
            }
    };
}

int main() {
    klarion::init();

    auto custom = std::make_shared<UppercaseSink>();
    custom->set_level(klarion::Level::Trace);

    auto logger = klarion::get("custom");
    logger->add_sink(custom);
    logger->set_level(klarion::Level::Trace);

    LOG_TO_INFO("custom", "this will be shouted");

    klarion::shutdown();
    return 0;
}
