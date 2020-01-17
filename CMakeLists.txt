cmake_minimum_required(VERSION 3.8)
project(cRVE)

set(CMAKE_CXX_STANDARD 14)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")


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


################################################
### For basic framework                      ###
################################################
set(SRC ${SRC} include/CRVE.h include/Types.h)
set(SRC ${SRC} src/CRVE/CRVE.cpp src/CRVE/Init.cpp)
set(SRC ${SRC} src/CRVE/GetMshVersionFromMshFile.cpp)
set(SRC ${SRC} src/CRVE/Run.cpp)
set(SRC ${SRC} src/CRVE/ReadMeshFromMsh.cpp)
set(SRC ${SRC} src/CRVE/ReadMeshFromMsh4.cpp)
set(SRC ${SRC} src/CRVE/ReadMeshFromGmsh2.cpp)

set(SRC ${SRC} include/GmshIO.h src/GmshIO.cpp src/GmshIOGetInfo.cpp)
set(SRC ${SRC} src/ReadMesh.cpp src/Init.cpp src/LableCubic.cpp src/JudgeFuns.cpp)
set(SRC ${SRC} src/PrepareInfoBeforeSave.cpp)


add_executable(crve ${SRC})

