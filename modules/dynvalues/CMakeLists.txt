cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(DynValues)

file(GLOB SOURCES "src/*/sources/*.cpp")

add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})
target_include_directories(
	${PROJECT_NAME}_lib

	PUBLIC src/values/headers
	PUBLIC src/auxillary_classes/headers
	PUBLIC src/exceptions
)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}_lib)
