
PROJECT(hashcode2014)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#####################################################
# macros
#####################################################
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
        LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

#####################################################
# Add boost package. 
#####################################################

#If the Boost library is not installed in the default directory (/usr/lib) uncomment the lines below and give the path to the boost include files and libraries
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "~/Projects/CPP/boost_1_55_0/include")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "~/Projects/CPP/boost_1_55_0/lib")

SET(Boost_USE_STATIC_LIBS ON) 
SET(Boost_USE_MULTITHREADED ON)  
SET(Boost_USE_STATIC_RUNTIME OFF) 
FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
ENDIF()

######################################################
# Add gtest package. 
#####################################################

#If the gtest library is not installed in the default directory (/usr/lib) uncomment the lines below and give the path to the gtest include files and libraries
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "~/Projects/CPP/gtest-1.7.0/include")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "~/Projects/CPP/gtest-1.7.0/lib/.libs")

FIND_PACKAGE(GTest)
IF(GTEST_FOUND)
    INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})
ENDIF()


######################################################
# Compiler options
######################################################
set (CMAKE_CXX_FLAGS "-Wall -std=c++11")

######################################################
# Include subdirectories 
#####################################################
ADD_SUBDIRECTORY(lib)
ADD_SUBDIRECTORY(lib_test)
ADD_SUBDIRECTORY(examples)

