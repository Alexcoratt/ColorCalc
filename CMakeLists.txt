cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PaintCalc)

file(GLOB SOURCES "src/classes/*/*/sources/*.cpp")

add_executable(main src/main.cpp ${SOURCES})

target_include_directories(
    main

    PUBLIC src/classes/math/exceptions
    PUBLIC src/classes/math/expressions/headers
    PUBLIC src/classes/math/factories/headers
    PUBLIC src/classes/math/parsers/headers

    PUBLIC src/classes/api/environment/headers

    PUBLIC src/classes/tui/commands/headers
    PUBLIC src/classes/tui/factories/headers
    PUBLIC src/classes/tui/parsers/headers
)
