cmake_minimum_required(VERSION 3.29)
project(test)

set(CMAKE_CXX_STANDARD 20)

add_executable(test test/test.cpp library/MPointer.h library/MPointerGC.h
        test/doublylinkedlist.h
        test/Quicksort.h
        test/Bubblesort.h
        test/Insertionsort.h)

