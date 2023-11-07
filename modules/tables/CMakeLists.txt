cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Tables)

file(GLOB SOURCES "src/*/sources/*.cpp")

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})
target_include_directories(
	${PROJECT_NAME}

	PUBLIC src/tables/headers
	PUBLIC src/values/headers
	PUBLIC src/exceptions
)
