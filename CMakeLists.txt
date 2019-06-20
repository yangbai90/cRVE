cmake_minimum_required(VERSION 3.8)
project(cRVE)

set(CMAKE_CXX_STANDARD 14)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Test")

###############################################
### For release                             ###
###############################################
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -O3 -march=native")


###############################################
### For debug                               ###
###############################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -O2 -Wall -Wextra -Werror")




################################################
### For basic framework                      ###
################################################
set(SRC src/main.cpp)
set(SRC ${SRC} include/Help.h)
set(SRC ${SRC} include/GmshIO.h src/GmshIO.cpp src/GmshIOGetInfo.cpp)
set(SRC ${SRC} src/ReadMesh.cpp src/LableCubic.cpp src/JudgeFuns.cpp)


add_executable(crve ${SRC})

