
include_directories(. ${PROJECT_SOURCE_DIR}/src)
add_executable(EncoderTests EncoderTests.cpp)
target_link_libraries(EncoderTests fi)

add_test(Encoder-DocumentOnly ${EXECUTABLE_OUTPUT_PATH}/EncoderTests 0)
add_test(Encoder-OneNode ${EXECUTABLE_OUTPUT_PATH}/EncoderTests 1	)
