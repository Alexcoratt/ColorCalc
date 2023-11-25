cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ColorCalc CXX)

add_subdirectory(modules/SimpleCLI)
add_subdirectory(modules/DynValues)

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(modules/json)

#file(GLOB CONNECTION_SOURCES "src/connections/sources/*.cpp")
#file(GLOB CONNECTION_HEADERS "src/connections/headers/*.hpp")
file(GLOB CONNECTIONS "src/connections/*/*.?pp")

#file(GLOB MANAGER_SOURCES "src/managers/sources/*.cpp")
#file(GLOB MANAGER_HEADERS "src/managers/headers/*.hpp")
file(GLOB MANAGERS "src/managers/*/*.?pp")

#file(GLOB VALUE_SOURCES "src/values/sources/*.cpp")
#file(GLOB VALUE_HEADERS "src/values/headers/*.hpp")
file(GLOB VALUES "src/values/*/*.?pp")

#file(GLOB CONFIG_MANAGER_SOURCES "src/config_managers/sources/*.cpp")
#file(GLOB CONFIG_MANAGER_HEADERS "src/config_managers/headers/*.hpp")
file(GLOB CONFIG_MANAGERS "src/config_managers/*/*.?pp")

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
    PUBLIC src/cli_methods/headers
)
target_link_libraries(${PROJECT_NAME}
    PRIVATE SimpleCLI_lib
    PRIVATE ${PROJECT_NAME}_lib
)

target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
