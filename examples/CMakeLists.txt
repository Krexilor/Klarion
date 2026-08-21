# ------------------------------------------------------------------
# Klarion examples
# ------------------------------------------------------------------
add_executable(basic_usage basic/basic_usage.cpp)
target_link_libraries(basic_usage PRIVATE Klarion::klarion)

add_executable(toml_usage toml/toml_usage.cpp)
target_link_libraries(toml_usage PRIVATE Klarion::klarion)
