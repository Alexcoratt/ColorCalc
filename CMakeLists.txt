cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ColorCalc CXX)

add_subdirectory(modules/simplecli)
add_subdirectory(modules/dynvalues)

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(modules/json)

file(GLOB CONNECTIONS "src/connections/sources/*.cpp")
file(GLOB MANAGERS "src/managers/sources/*.cpp")
file(GLOB VALUES "src/values/sources/*.cpp")
file(GLOB CONFIG_MANAGERS "src/config_managers/sources/*.cpp")

add_library(${PROJECT_NAME}_lib STATIC
    ${CONNECTIONS}
    ${MANAGERS}
    ${VALUES}
    ${CONFIG_MANAGERS}
)

target_include_directories(${PROJECT_NAME}_lib
    PUBLIC src/connections/headers
    PUBLIC src/managers/headers
    PUBLIC src/values/headers
    PUBLIC src/auxillary/headers
    PUBLIC src/config_managers/headers
    PUBLIC src/exceptions
)

target_link_libraries(${PROJECT_NAME}_lib
    PRIVATE nlohmann_json::nlohmann_json
    PUBLIC DynValues_lib
)

file(GLOB CLI_SOURCES "src/cli_methods/sources/*.cpp")
add_executable(${PROJECT_NAME} src/main.cpp ${CLI_SOURCES})
target_include_directories(${PROJECT_NAME}
    PRIVATE src/cli_methods/headers
)
target_link_libraries(${PROJECT_NAME}
    PRIVATE SimpleCLI_lib
    PRIVATE ${PROJECT_NAME}_lib
)

target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
