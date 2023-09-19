cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PaintCalc)

file(GLOB SOURCES "src/classes/*/sources/*.cpp")

add_executable(main src/main.cpp ${SOURCES})

target_include_directories(
    main
    PUBLIC src/classes/expressions/headers
    PUBLIC src/classes/operators/headers
    PUBLIC src/classes/parser/headers
)
