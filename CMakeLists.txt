cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PaintCalc)

add_subdirectory(modules/SimpleCLI)
add_subdirectory(modules/DynValues)

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(modules/json)

file(GLOB CONNECTION_SOURCES "src/connections/sources/*.cpp")
file(GLOB MANAGER_SOURCES "src/managers/sources/*.cpp")
file(GLOB VALUE_SOURCES "src/values/sources/*.cpp")
file(GLOB CONNECTION_STRATEGIES_SOURCES "src/table_connection_strategies/sources/*.cpp")

add_library(${PROJECT_NAME}_lib STATIC
    ${CONNECTION_SOURCES}
    ${MANAGER_SOURCES}
    ${VALUE_SOURCES}
    ${CONNECTION_STRATEGIES_SOURCES}
)
target_include_directories(${PROJECT_NAME}_lib
    PUBLIC src/connections/headers
    PUBLIC src/managers/headers
    PUBLIC src/values/headers
    PUBLIC src/auxillary/headers
    PUBLIC src/table_connection_strategies/headers
    PUBLIC src/exceptions
)
target_link_libraries(${PROJECT_NAME}_lib
    PUBLIC nlohmann_json::nlohmann_json
    PUBLIC DynValues_lib
)

file(GLOB CLI_SOURCES "src/cli_methods/sources/*.cpp")
add_executable(${PROJECT_NAME} src/main.cpp ${CLI_SOURCES})
target_include_directories(${PROJECT_NAME}
    PUBLIC src/cli_methods/headers
)
target_link_libraries(${PROJECT_NAME}
    PUBLIC SimpleCLI_lib
    PUBLIC ${PROJECT_NAME}_lib
)

target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
