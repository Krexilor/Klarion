# ------------------------------------------------------------------
# Klarion library target
# ------------------------------------------------------------------
add_library(klarion STATIC
    core/logger.cpp
    core/klarion.cpp
    config/config.cpp
    sinks/file_sink.cpp
    sinks/console_sink.cpp
    config/toml_config.cpp
    detail/terminal/console_color.cpp
    detail/formatting/pattern_formatter.cpp
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
