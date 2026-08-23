#pragma once

// LIBRARIES ---------------------------------------------------------------------------------------------------------------------------------------|
#include <string>
#include <type_traits>

// EXTERNAL LIBRARIES ------------------------------------------------------------------------------------------------------------------------------|
#include <fmt/format.h>

// FIELD DEFINITION --------------------------------------------------------------------------------------------------------------------------------|
namespace klarion {
    enum class FieldKind {
        String, Int, Float, Bool
    };

    struct Field {
        std::string key;
        std::string value;
        FieldKind kind{FieldKind::String};
    };

    template<typename T>
    inline Field kv(std::string key, const T& value) {
        using DecayedT = std::decay_t<T>;

        if constexpr (std::is_same_v<DecayedT, bool>) {
            return Field{std::move(key), value ? "true" : "false", FieldKind::Bool};
        }
        else if constexpr (std::is_floating_point_v<DecayedT>) {
            return Field{std::move(key), fmt::format("{}", value), FieldKind::Float};
        }
        else if constexpr (std::is_integral_v<DecayedT>) {
            return Field{std::move(key), fmt::format("{}", value), FieldKind::Int};
        }
        else {
            return Field{std::move(key), fmt::format("{}", value), FieldKind::String};
        }
    }

    inline Field kv(std::string key, std::string value) {
        return Field{std::move(key), std::move(value), FieldKind::String};
    }
}
