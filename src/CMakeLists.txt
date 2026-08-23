# ------------------------------------------------------------------
# Klarion library target
# ------------------------------------------------------------------
add_library(klarion STATIC
    core/klarion.cpp
    core/logger.cpp
    config/config.cpp
    config/toml_config.cpp
    config/env_overrides.cpp

    detail/filesystem/path_utils.cpp
    detail/terminal/console_color.cpp
    detail/formatting/pattern_formatter.cpp

    sinks/file_sink.cpp
    sinks/test_sink.cpp
    sinks/json_sink.cpp
    sinks/console_sink.cpp
    sinks/backtrace_sink.cpp
    sinks/rotating_file_sink.cpp
)
add_library(Klarion::klarion ALIAS klarion)

# Public headers live in <repo>/include
target_include_directories(klarion PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Consumers automatically get C++17
target_compile_features(klarion PUBLIC cxx_std_17)

# Dependencies
target_link_libraries(klarion PUBLIC
    fmt::fmt
    tomlplusplus::tomlplusplus
)
