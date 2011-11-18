
include_directories(. ${PROJECT_SOURCE_DIR}/src)
add_executable(EncoderTests EncoderTests.cpp)
target_link_libraries(EncoderTests fi)

add_test(Encoder-DocumentOnly ${EXECUTABLE_OUTPUT_PATH}/EncoderTests 0)
add_test(Encoder-OneElement ${EXECUTABLE_OUTPUT_PATH}/EncoderTests 1)
add_test(Encoder-TwoElements ${EXECUTABLE_OUTPUT_PATH}/EncoderTests 2)
add_test(Encoder-NestedElements ${EXECUTABLE_OUTPUT_PATH}/EncoderTests 3)

add_executable(DecoderTests DecoderTests.cpp)
target_link_libraries(DecoderTests fi)

add_test(NAME Decoder-ElementsOnly COMMAND DecoderTests 0 ${PROJECT_SOURCE_DIR}/data/01_Elements_only_java.finf)
add_test(NAME Decoder-ElementsAttributes COMMAND DecoderTests 1 ${PROJECT_SOURCE_DIR}/data/02_Elements_Attributes_java.finf)