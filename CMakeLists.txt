# 设置 CMake 最低版本
cmake_minimum_required(VERSION 3.12)

# 定义项目
project(jsonparser VERSION 1.0 LANGUAGES CXX)

# 启用 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置输出目录到项目根目录下的 bin 文件夹
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# 添加库 (INTERFACE 用于只提供头文件的库)
add_library(jsonparser_lib INTERFACE)
target_include_directories(jsonparser_lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 添加 benchmark 可执行文件并链接 jsoncpp
add_executable(jsonparser_benchmark benchmark/benchmark.cc)
target_include_directories(jsonparser_benchmark PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/benchmark)
target_link_libraries(jsonparser_benchmark jsonparser_lib jsoncpp)
# 构建后复制 test_data.json
add_custom_command(TARGET jsonparser_benchmark POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/test_data.json
            $<TARGET_FILE_DIR:jsonparser_benchmark>
)

# 添加测试程序
add_executable(jsonparser_tests tests/unit_test.cc)
target_include_directories(jsonparser_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
target_link_libraries(jsonparser_tests jsonparser_lib)

# 设置编译类型的默认优化标志
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

# 自定义选项控制优化
option(ENABLE_OPTIMIZATION "Enable compiler optimization (-O2)" OFF)
if (ENABLE_OPTIMIZATION)
    message(STATUS "Compiler optimization enabled: -O2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
else()
    message(STATUS "Compiler optimization disabled")
endif()

# 输出每个构建的详细日志
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")