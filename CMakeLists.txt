cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PaintCalc)

file(GLOB APP_SOURCES "src/classes/*/sources/*.cpp")
file(GLOB CLI_SOURCES "src/cli/*/sources/*.cpp")

add_executable(main src/main.cpp ${APP_SOURCES} ${CLI_SOURCES})
target_include_directories(
    main

    PUBLIC src/classes/auxillary_methods/headers
    PUBLIC src/classes/connections/headers
    PUBLIC src/classes/containers/headers
    PUBLIC src/classes/exceptions

    PUBLIC src/cli/option_containers/headers
    PUBLIC src/cli/leaf_options/headers
    PUBLIC src/cli/exceptions

    PUBLIC json/include/nlohmann
    PUBLIC json/include
)

add_executable(cli_demo src/cli/demo.cpp ${CLI_SOURCES})
target_include_directories(
    cli_demo

    PUBLIC src/cli/option_containers/headers
    PUBLIC src/cli/leaf_options/headers
    PUBLIC src/cli/exceptions
)
