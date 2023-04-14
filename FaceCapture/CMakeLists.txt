cmake_minimum_required(VERSION 2.8.4)  #版本最小为2.8.4

PROJECT(face_capture)   #设置工程名

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -DDLIB_JPEG_SUPPORT")

IF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")
ELSEIF(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
ENDIF()


# #INCLUDE OPENCV
# include_directories(/usr/include/opencv4)
# include_directories(/usr/include/opencv4/opencv2)
# include_directories(/usr/include/)

# link_libraries(opencv_core)
# link_libraries(opencv_highgui)
# link_libraries(opencv_imgproc)

#INCLUDE OPENCV
FIND_PACKAGE(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
message(STATUS "Opencv include dir found at ${OpenCV_INCLUDE_DIRS}")


#包含头文件
INCLUDE_DIRECTORIES(/home/raspberry/dlib-19.24) #dlib根目录地址
INCLUDE_DIRECTORIES(/home/raspberry/rpi_ws281x_3) #light-headfile


LINK_DIRECTORIES(/home/raspberry/dlib-19.24/build/dlib/) #dlib编译后bulid下dlib地址
LINK_DIRECTORIES(/home/raspberry/rpi_ws281x_3/build/)


#FInd wx281x
#find_library()
#RPI_LIBS=/home/raspberry/rpi_ws281x_3/build

#生产类似于.exe的可执行文件
ADD_EXECUTABLE(face_capture main.cpp)
#链接库
TARGET_LINK_LIBRARIES(face_capture dlib ${OpenCV_LIBS} ws2811 wiringPi pthread rt m crypt)
#TARGET_LINK_LIBRARIES(dlib_detector libjpeg.so)
