cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.hpp")


project(cache)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
