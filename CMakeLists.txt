cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PaintCalc)

file(GLOB SOURCES "src/*/sources/*.cpp")

add_subdirectory(modules/cli)
add_subdirectory(modules/dynvalues)

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(modules/json)

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})
target_include_directories(${PROJECT_NAME}
    PUBLIC src/auxillary_methods/headers
    PUBLIC src/connections/headers
    PUBLIC src/containers/headers
    PUBLIC src/values/headers
    PUBLIC src/exceptions
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE nlohmann_json::nlohmann_json
    PUBLIC SimpleCLI_lib
    PUBLIC DynValues_lib
)

target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
