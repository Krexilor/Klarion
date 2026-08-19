# ------------------------------------------------------------------
# Klarion library target
# ------------------------------------------------------------------
add_library(klarion INTERFACE)
add_library(Klarion::klarion ALIAS klarion)

# Public headers live in <repo>/include
target_include_directories(klarion INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Consumers automatically get C++17
target_compile_features(klarion INTERFACE cxx_std_17)

# Dependencies
target_link_libraries(klarion INTERFACE
    fmt::fmt
    tomlplusplus::tomlplusplus
)
