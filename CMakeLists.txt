cmake_minimum_required(VERSION 3.10)

project(Compression)

add_executable(Compression src/main.cpp src/LZ77.h src/archievatorLZ77.cpp src/archievatorLZW.cpp src/LZW.h src/archievatorRLE.cpp)

add_executable(test_func src/test_func.cpp src/doctest.h src/LZ77.h src/archievatorLZ77.cpp src/archievatorLZW.cpp src/LZW.h src/archievatorRLE.cpp)
target_sources(test_func PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/doctest.h)

enable_testing()
add_test(NAME test_func COMMAND test_func --force-colors -d)

