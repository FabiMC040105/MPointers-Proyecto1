cmake_minimum_required(VERSION 3.29)
project(test)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(../library ../../library/cmake-build-debug)

add_executable(test test.cpp)

target_link_libraries(test PRIVATE "${CMAKE_CURRENT_LIST_DIR}/../library/cmake-build-debug/CMakeFiles/MPointers_Proyecto1.dir/MPointer.cpp.o")
target_include_directories(test PRIVATE ../library)