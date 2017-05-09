cmake_minimum_required (VERSION 3.2)
project (hashfun CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -pedantic-errors")

if (CMAKE_COMPILER_IS_GNUCXX)
  set(CODE_CXX_FLAGS "${CODE_CXX_FLAGS} -flto")
endif()
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti")
set(CODE_CXX_FLAGS "${CODE_CXX_FLAGS} -O3")

if (NOT (MSVS OR MSYS OR MINGW))
  set(Boost_USE_STATIC_LIBS   ON)
endif()
find_package(Boost COMPONENTS program_options )
if( NOT Boost_FOUND)
  message( FATAL_ERROR "Boost not found" )
endif()
include_directories(${Boost_INCLUDE_DIRS})

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
  CommandlineParser.cpp
  CvsPrinter.cpp
  DataSet.cpp
  HashBenchmark.cpp
  main.cpp
)

###############################################
# https://crascit.com/2015/07/25/cmake-gtest/ #
###############################################
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in
               googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
 
# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
 
# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)
###############################################

add_executable(hashfun ${SOURCE_FILES})
set_target_properties(hashfun PROPERTIES COMPILE_FLAGS ${CODE_CXX_FLAGS})
target_link_libraries(hashfun ${Boost_LIBRARIES})

enable_testing()
add_executable(runUnitTests unittest/DataSet_unittest.cpp DataSet.cpp)
target_link_libraries(runUnitTests gtest_main)
add_test(NAME that-test-I-made COMMAND runUnitTests)


