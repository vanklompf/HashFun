cmake_minimum_required (VERSION 3.2)
project (hashfun CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -pedantic-errors")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti")
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

#set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS program_options )
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  add_executable(hashfun ${SOURCE_FILES})
  target_link_libraries(hashfun ${Boost_LIBRARIES})
endif()



