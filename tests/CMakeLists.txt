# ------------------------------------------------------------------
# Klarion tests
# ------------------------------------------------------------------
add_executable(test_level core/test_level.cpp)
target_link_libraries(test_level PRIVATE Klarion::klarion)

add_executable(test_logger core/test_logger.cpp)
target_link_libraries(test_logger PRIVATE Klarion::klarion)

add_executable(test_config config/test_config.cpp)
target_link_libraries(test_config PRIVATE Klarion::klarion)
