cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SimpleCLI)

file(GLOB SOURCES "src/*/sources/*.cpp")

add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})
target_include_directories(
    ${PROJECT_NAME}_lib

    PUBLIC src/option_containers/headers
    PUBLIC src/leaf_options/headers
    PUBLIC src/exceptions
)

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}_lib)

