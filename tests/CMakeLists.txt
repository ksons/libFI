
include_directories(. ${PROJECT_SOURCE_DIR}/src)
add_executable(EncoderTests EncoderTests.cpp)
target_link_libraries(EncoderTests fi)

add_test(Encoder-DocumentOnly ${EXECUTABLE_OUTPUT_PATH}/EncoderTests 0)
add_test(Encoder-OneElement ${EXECUTABLE_OUTPUT_PATH}/EncoderTests 1)
add_test(Encoder-TwoElements ${EXECUTABLE_OUTPUT_PATH}/EncoderTests 2)
add_test(Encoder-NestedElements ${EXECUTABLE_OUTPUT_PATH}/EncoderTests 3)
