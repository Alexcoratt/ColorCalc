cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ColorCalc CXX)

add_subdirectory(modules/simplecli)
add_subdirectory(modules/dynvalues)

set(JSONCPP_WITH_TESTS OFF)
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(modules/jsoncpp)
get_target_property(JSON_INC_PATH jsoncpp_static INTERFACE_INCLUDE_DIRECTORIES)
include_directories(${JSON_INC_PATH})

file(GLOB CONNECTIONS "src/connections/sources/*.cpp")
file(GLOB MANAGERS "src/managers/sources/*.cpp")
file(GLOB CONFIG_MANAGERS "src/config_managers/sources/*.cpp")

add_library(${PROJECT_NAME}_lib STATIC
    ${CONNECTIONS}
    ${MANAGERS}
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
    PRIVATE jsoncpp_static
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

if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-Wl,-Bstatic -lpthread -Wl,-Bdynamic")
endif()
