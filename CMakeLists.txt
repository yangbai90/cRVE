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
set(src include/Welcome.h src/main.cpp)
set(src ${src} include/CRVE.h)
set(src ${src} src/CRVE/CRVE.cpp)
set(src ${src} src/CRVE/Run.cpp)
set(src ${src} src/CRVE/GetGmshFileInfo.cpp)
set(src ${src} src/CRVE/ReadMsh2File.cpp)
set(src ${src} src/CRVE/ReadMsh4File.cpp)
set(src ${src} src/CRVE/LableBC.cpp)
set(src ${src} src/CRVE/JudgeFuns.cpp)
set(src ${src} src/CRVE/SaveMesh.cpp)
set(src ${src} src/CRVE/PrintInfo.cpp)
################################################
### For String Utils                         ###
################################################
set(src ${src} include/StringUtils.h)
set(src ${src} src/StringUtils.cpp)



add_executable(crve ${src})

