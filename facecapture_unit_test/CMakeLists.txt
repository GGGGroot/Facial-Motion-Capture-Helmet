cmake_minimum_required(VERSION 2.8.4)  

PROJECT(face_capture)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -DDLIB_JPEG_SUPPORT")

IF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")
ELSEIF(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
ENDIF()



#INCLUDE OPENCV
FIND_PACKAGE(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
message(STATUS "Opencv include dir found at ${OpenCV_INCLUDE_DIRS}")


#headfile
INCLUDE_DIRECTORIES(/home/raspberry/dlib-19.24) #dlib
INCLUDE_DIRECTORIES(/home/raspberry/rpi_ws281x_3) #light


LINK_DIRECTORIES(/home/raspberry/dlib-19.24/build/dlib/) #dlib
LINK_DIRECTORIES(/home/raspberry/rpi_ws281x_3/build/) #light


#.exe
aux_source_directory(src/. CPP_LIST)

ADD_EXECUTABLE(face_capture ${CPP_LIST})

#链接库
TARGET_LINK_LIBRARIES(face_capture dlib ${OpenCV_LIBS} ws2811 wiringPi pthread rt m crypt gtest)

enable_testing()

#add_subdirectory(googletest)

add_library(mycode STATIC ${CPP_LIST})

add_subdirectory(test)
