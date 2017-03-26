cmake_minimum_required (VERSION 3.6)
include(CheckCXXCompilerFlag)

project (hashfun C CXX)

CHECK_CXX_COMPILER_FLAG(-std=c++1z HAS_CXX17_FLAG)
if(HAS_CXX17_FLAG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
else()
    message( FATAL_ERROR "Support for C++17 is required." )
endif()


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

set(HASH_SOURCE_FILES
  hash/CityHash.cpp
  hash/MurmurHash1.cpp
  hash/MurmurHash2.cpp
  hash/MurmurHash3.cpp
  hash/SuperFastHash.cpp
  hash/xxHash.cpp
)

set(SOURCE_FILES
  ${HASH_SOURCE_FILES}
  DataSet.cpp
  HashBenchmark.cpp
  main.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(hashfun ${SOURCE_FILES})
