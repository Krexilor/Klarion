#pragma once

// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <mutex>
#include <string>
#include <memory>
#include <vector>
#include <cstddef>

// PROJECT HEADING FILES ---------------------------------------------------------------------------------------------------------------------------|
#include "klarion/core/level.hpp"
#include "klarion/core/field.hpp"
#include "klarion/sinks/sink.hpp"
#include "klarion/core/record.hpp"

// LOGGER DEFINITION -------------------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    class Logger {
        public:
            explicit Logger(std::string name = "default");
            ~Logger();

            Logger(const Logger&) = delete;
            Logger& operator = (const Logger&) = delete;

            Logger(Logger&&) = delete;
            Logger& operator = (Logger&&) = delete;

            const std::string& name() const { return name_; }
            void set_level(Level level);

            Level level() const;

            void add_sink(SinkPtr sink);
            void remove_sink(SinkPtr sink);
            void clear_sinks();

            std::size_t sink_count() const;
            
            void log(Level level, std::string message, SourceLocation location, std::vector<Field> fields = {});
            void set_pattern(const std::string& pattern);

        private:
            std::string name_;
            Level level_{Level::Info};
            std::vector<SinkPtr> sinks_;
            mutable std::mutex mutex_;
    };
}
