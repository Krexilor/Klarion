# ------------------------------------------------------------------
# Klarion tests
# ------------------------------------------------------------------
add_executable(test_level core/test_level.cpp)
target_link_libraries(test_level PRIVATE Klarion::klarion)

add_executable(test_logger core/test_logger.cpp)
target_link_libraries(test_logger PRIVATE Klarion::klarion)

add_executable(test_runtime_level core/test_runtime_level.cpp)
target_link_libraries(test_runtime_level PRIVATE Klarion::klarion)

add_executable(test_structured_fields core/test_structured_fields.cpp)
target_link_libraries(test_structured_fields PRIVATE Klarion::klarion)

add_executable(test_config config/test_config.cpp)
target_link_libraries(test_config PRIVATE Klarion::klarion)

add_executable(test_env_overrides config/test_env_overrides.cpp)
target_link_libraries(test_env_overrides PRIVATE Klarion::klarion)

add_test(NAME test_level COMMAND test_level)
add_test(NAME test_logger COMMAND test_logger)
add_test(NAME test_runtime_level COMMAND test_runtime_level)
add_test(NAME test_structured_fields COMMAND test_structured_fields)
add_test(NAME test_config COMMAND test_config)
add_test(NAME test_env_overrides COMMAND test_env_overrides)
