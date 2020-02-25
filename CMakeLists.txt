cmake_minimum_required(VERSION 2.8)

project(hm2obj LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

#------------------------------------------#
#---  Define project sources & headers  ---#
#------------------------------------------#

# project_sources variable contains all the .cpp/.inl files
FILE(GLOB_RECURSE project_sources ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.inl)
# project_headers variable contains all the .h/.hpp files
FILE(GLOB_RECURSE project_headers ${CMAKE_SOURCE_DIR}/src/*.h ${CMAKE_SOURCE_DIR}/src/*.hpp)

include_directories(${CMAKE_SOURCE_DIR}/src)
add_executable(hm2obj
               ${project_sources}
               ${project_headers})
