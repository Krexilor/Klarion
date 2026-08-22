#pragma once

// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <string>

// EXTERNAL LIBRARIES ------------------------------------------------------------------------------------------------------------------------------|
#include <fmt/format.h>

// FIELD DEFINITION --------------------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    struct Field {
        std::string key;
        std::string value;
    };

    template<typename T>
    inline Field kv(std::string key, const T& value) {
        return Field{std::move(key), fmt::format("{}", value)};
    }

    inline Field kv(std::string key, std::string value) {
        return Field{std::move(key), std::move(value)};
    }
}
