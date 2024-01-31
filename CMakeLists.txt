cmake_minimum_required(VERSION 3.14)
project(JumpingBalls VERSION 1.0)

file(GLOB_RECURSE sources src/*.cpp)

add_executable(${PROJECT_NAME} ${sources})

target_include_directories(${PROJECT_NAME} PUBLIC include/)
target_link_directories(${PROJECT_NAME} PUBLIC lib/)
target_link_libraries(${PROJECT_NAME} libraylib.so libraylib.so.5.0.0 libraylib.so.500)