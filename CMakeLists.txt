cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PaintCalc)

file(GLOB SOURCES "src/*/sources/*.cpp" "src/cli/*/sources/*.cpp")

add_executable(main src/main.cpp ${SOURCES})

target_include_directories(
    main

    PUBLIC src/classes/headers

    PUBLIC src/cli/option_containers/headers
    PUBLIC src/cli/leaf_options/headers
    PUBLIC src/cli/exceptions

    PUBLIC json/include/nlohmann
    PUBLIC json/include
)
