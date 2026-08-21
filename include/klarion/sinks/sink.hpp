#pragma once

// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <string>
#include <memory>

// PROJECT HEADER FILES ----------------------------------------------------------------------------------------------------------------------------|
#include "klarion/core/level.hpp"
#include "klarion/core/record.hpp"

// SINK DEFINITION ---------------------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    class Sink {
        public:
            Sink() = default;
            virtual ~Sink() = default;

            Sink(const Sink&) = delete;
            Sink& operator = (const Sink&) = delete;

            virtual void write(const LogRecord& record) = 0;
            virtual void flush() = 0;
            void set_level(Level level) { min_level_ = level; }
            Level level() const { return min_level_; }

            bool should_log(Level level) const {
                return is_enabled(level, min_level_);
            }

            virtual void set_pattern(const std::string& pattern) {
                pattern_ = pattern;
            }

            const std::string& pattern() const {
                return pattern_;
            }
        
        protected:
            Level min_level_{Level::Info};
            std::string pattern_;
    };

    using SinkPtr = std::shared_ptr<Sink>;
}
