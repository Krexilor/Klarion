# ------------------------------------------------------------------
# Klarion examples
# ------------------------------------------------------------------
add_executable(basic_usage basic/basic_usage.cpp)
target_link_libraries(basic_usage PRIVATE Klarion::klarion)

add_executable(named_logger_usage named_loggers/named_logger_usage.cpp)
target_link_libraries(named_logger_usage PRIVATE Klarion::klarion)

add_executable(toml_usage toml/toml_usage.cpp)
target_link_libraries(toml_usage PRIVATE Klarion::klarion)

add_executable(runtime_control runtime/runtime_control.cpp)
target_link_libraries(runtime_control PRIVATE Klarion::klarion)

add_executable(structured_usage structured/structured_usage.cpp)
target_link_libraries(structured_usage PRIVATE Klarion::klarion)
