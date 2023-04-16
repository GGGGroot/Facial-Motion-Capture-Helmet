# Facial-Motion-Capture-Helmet    
![sample](https://github.com/GGGGroot/Facial-Motion-Capture-Helmet/blob/main/image/sample.png?raw=true)

>[Click me to visit the Twitter channel](https://twitter.com/Team_29_)    
>[Click me to visit the Instagram channel](https://instagram.com/facial_motion_capture_helmet?igshid=YmMyMTA2M2Y=)

## Project Contributors
- Yixuan Pang: project management, hardware designing and boot-up coding
- Shenjia Ding: pair programming as driver and system environment set-up
- Wenjin Chi: LED strip designing, soldering, and expression display coding
- Zihao Wang: pair programming as navigator and constructing training set
## Project Description
  The facial-motion-capture helmet is a real-time facial expression feedback system by using the camera to capture the wearer’s facial emotion based on the Linux embedded system - Raspberry Pi, and then the corresponding expressions are fed back into the light array for display. This expression recognition system uses the OpenCV and dlib libraries in C++ for video signal acquisition and real-time feedback of facial expressions and can currently recognise basic emotion like happy, sad and calm. The expressions displayed in real time are cute and can be used as a device for Vtuber and for treating people with autism and facial dysmorphia.
### Background   
  Some autism has difficulty holding a conversation or understanding facial expressions when talking with others.     
  Facial dysmorphia is a mental health condition where a person spends a lot of time worrying about flaws in their appearance.  
  Vtubers need a headset to help them with their creative work.
### Technologies   
  Facial recognition    
  LED strip design     
### Difficulties    
  Finite distance & light            
  Motion Recognition     
### Business prospects         
  Vtuber       
  VR Device          
  Cyberpunk art installation
## Project Planning
#### Main programming - Shenjia Ding and Zihao Wang
- [x] searching information about how to realise real-time face recognation
- [x] building the environment of openCV and dlib library
- [x] writing facial recognition functions of the program
- [x] constructing training set and performing training
- [x] conducting Unit test of the facial recognition function
- [x] writing main function
- [x] combining the LED strip function into the main program
- [x] testing the final program  
#### LED strip designing and soldering - Wenjin Chi  
- [x] Buying LED strip and camera
- [x] writing LED testing program to test LED strip
- [x] booking a laboratory and carrying out soldering work
- [x] connecting to the Raspberry Pi and testing the performance of the LED strip
- [x] writing the corrsponding expressions display in LED strip
- [x] conducting unit test of the expression display function
- [x] creating social media of this project
- [x] upgrading social media and README file
#### Hardware designing and document writing - Yixuan Pang
- [x] creating github repository of this project and writing the README file
- [x] designing front panel of the helmet
- [x] booking a technical service to 3D print the front panel
- [x] upgrading README file and creating Gantt chart of this project to illustrate timeline
- [x] designing base plate of the helmet
- [x] booking a technical service to 3D print the base plate
- [x] writing boot-up coding
## Project guide
### Hardware guidance

#### Raspberry Pi
In this project, our team is using the Raspberry Pi 4 Model B with 4GB Ram. It is an embedded system and has good performance.    
<img src="https://github.com/GGGGroot/Facial-Motion-Capture-Helmet/blob/GGGGroot-patch-5/image/Raspberry%20Pi.png" length="1024" width="640"> 

#### Pi camera
The Raspberry Pi Camera Module v2 is a customised expansion board for the Raspberry Pi with a high quality 8MP Sony IMX219 sensor and a fixed focus lens. It can reach 3280 x 2464 pixel stills and also supports 1080p30, 720p60 and 640x480p60/90 camera capabilities. The expansion board understands the Raspberry Pi through a small slot on the surface of the board and uses a dedicated CSI interface, specially designed for cameras. In this project, we use 1080p30 camera capability.    
<img src="https://github.com/GGGGroot/Facial-Motion-Capture-Helmet/blob/GGGGroot-patch-5/image/Pi%20Camera.jpg">    

#### WS2812B LED strip
WS2812B is an intelligent control LED light source that the control circuit and RGB chip are integrated in. It is programmable and cuttable. The voltage support is DC5V, which is the same of Raspberry Pi.   
<img src="https://github.com/GGGGroot/Facial-Motion-Capture-Helmet/blob/GGGGroot-patch-5/image/WS2812B%20LED%20Strip.jpg" length="1024" width="640">

### Environment construction 
To install OpenCV library, first thing is to download the modules of [OpenCV library](https://docs.opencv.org/). The development files end in `-dev` and for opencv they are of the format `libopencv-moduleYouWant-dev`, or `libopencv-dev`, which includes all openCV modules.

Using `apt` install:
```
sudo apt install libopencv-dev  # installs all opencv modules
sudo apt install libopencv-core-dev  # example: only installs the core module
```
To install dlib library, the first thing is to download the dlib library modules from the [dlib library](http://dlib.net/) website, extract it and then run the following statement：  
```
cd dlib-19.24  # Go to the dlib root   
mkdir build  # Create a new build folder to store the cmake compiled files 
cd build  # Go to the newly created build folder  
cmake ..  # cmake compiles the entire folder 
```
To install GPIO library, the first thing is to download the [wiringpi library](https://project-downloads.drogon.net/), and then run the following:
```
sudo dpkg -i wiringpi-latest.deb
```
### Facial expression capture and recognition 
The program uses the OpenCV library for image processing and display, and the Dlib library for face detection and expression recognition.  

First, the camera is turned on using the OpenCV library and the frame image is acquired from the camera, followed by the face detection of the face in the frame image using the face detector in the Dlib library. The default face detector is obtained by calling the get_frontal_face_detector function. A pre-trained model, called `shape_predictor_68_face_landmarks`, is provided in the Dlib library for detecting facial landmarks. This model can recognise 68 different landmarks on the human face, including key areas such as eyebrows, eyes, nose and mouth, and can be used to recognise expressions.  

To recognise expressions, facial feature points are first normalised and used as input to the SVM classifier, which uses the OpenCV library's `StatModel::load` method to load pre-trained model files. Based on the results of the SVM predictions, the system can determine whether the face is a happy, common or shocked expression. Figure.1 shows the happiness expression determined through the system. Figure.2 shows the common expression determined through the system. Figure.3 shows the shocked expression determined through the system.

<div align=center><img src="https://github.com/GGGGroot/Facial-Motion-Capture-Helmet/blob/main/image/Expression%20Recognition%20-%20Happy.png" length="1024" width="640">  

<p align="center">Figure.1 the happiness expression determined through the system</p>  

<div align=center><img src="https://github.com/GGGGroot/Facial-Motion-Capture-Helmet/blob/main/image/Expression%20Recognition%20-%20Common.png" length="1024" width="640">  

<p align="center">Figure.2 the common expression determined through the system</p>  

<div align=center><img src="https://github.com/GGGGroot/Facial-Motion-Capture-Helmet/blob/main/image/Expression%20Recognition%20-%20Shocked.png" length="1024" width="640">  

<p align="center">Figure.3 the shocked expression determined through the system</p>     

<div align=left>

Main ideas: (training module + test module)  

Training module: 

- [x] Dlib feature points are extracted and normalized after a person makes a specific expression.  
- [x] Each picture stores 136 dimensional data stored into a specific numbered TXT for easy recall.  
- [x] Use SVM classifier to classify and train into XML. 

Test module:  

Read in the trained XML, classify each frame and display the results. 

The programme can be viewed through [there](https://github.com/GGGGroot/Facial-Motion-Capture-Helmet/tree/main/Expression%20recognition%20training%20module).

### Software building in Raspberry Pi

First you need to ensure that CMake is installed on your system. If it is not already installed, follow these steps:
```
sudo apt-get update Update the package list
sudo apt-get install cmake Install CMake
```
Next, you will build and compile your project using CMake. First, create a new CMakeLists.txt file in the project folder, with the following contents:
```
cmake_minimum_required(VERSION 2.8.4) # Minimum version required is 2.8.4

PROJECT(face_capture) # Set the project name

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

# Include header files
INCLUDE_DIRECTORIES(/home/raspberry/dlib-19.24) # dlib root directory
INCLUDE_DIRECTORIES(/home/raspberry/rpi_ws281x_3) # light-headfile

LINK_DIRECTORIES(/home/raspberry/dlib-19.24/build/dlib/) # dlib build directory after compilation
LINK_DIRECTORIES(/home/raspberry/rpi_ws281x_3/build/)

# Create an executable file similar to .exe
ADD_EXECUTABLE(face_capture main.cpp)
# Link libraries
TARGET_LINK_LIBRARIES(face_capture dlib ${OpenCV_LIBS} ws2811 wiringPi pthread rt m crypt)
```
Then compile using cmake, as follows:
```
cd facecapture_test #Go to the project directory
mkdir build #Create a new build directory
cd build #Go into the build directory
cmake .. #Run CMake to generate the build system
make -j8 #Compile the project
sudo . /face_capture #Execute the program
```
Note: Ensure that the shape_predictor_68_face_landmarks.dat and SVM_DATA files are in the build folder.

### Light array connection and display 
In this project, WS2812B LED strip was used as the output equipment to show the corresponding facial expressions on the helmet. Light sets are available in 30 per metre and 144 per metre. The project uses 144 per metre, deployed around the eyes and mouth.
#### LED strip soldering 
After purchasing the LED strip, the first thing is to cut and solder the WS2812B. Since the eyes will be longer than the mouth during display, 3 rows of 25 were cut to show the eyes and 3 rows of 20 were cut to show the mouth. After that, the six light arrays are connected in sequence by aligning each row with the corresponding earth, power and signal ports and applying insulated wire to prevent short circuits. When connecting, it should be taken care to solder in the direction that the arrows in the light array are pointing. If the arrows are pointing in the opposite direction, then the light array will not work properly either. Another thing to keep in mind is to align the design with the position of the front panel so as not to block the holes reserved for seeing things clearly.    
#### LED strip display 
It is pivotal to know where the LED strip begins and the number of each LED. First, connect the Raspberry Pi to the light array via the Dupont wire, with the start of the arrow or terminal being the start of the light array. The LED arrays are counted and marked in turn as a number for each lamp. In this project, a total of three facial expressions are recognised and displayed, namely happy, common and shocked. 

The part of the eye that expresses happiness is designed as `><` and the part of the mouse is designed as `v`. After calibration, lights in the optional light array are counted to display this expression. Figure.4 shows the happiness expression displayed in the front panel.  
<div align=center><img src="https://github.com/GGGGroot/Facial-Motion-Capture-Helmet/blob/GGGGroot-patch-3/image/happy.jpg" length="1024" width="640">   

Figure.4 the happiness expression 
<div align=left>

The part of the eye that expresses shock is designed as `▯▯` and the part of the mouse is designed as `▯`. After calibration, lights in the optional light array are counted to display this expression. Figure.5 shows the shocked expression displayed in the front panel.  
<div align=center><img src="https://github.com/GGGGroot/Facial-Motion-Capture-Helmet/blob/GGGGroot-patch-3/image/shock.jpg" length="1024" width="640">

Figure.5 the shocked expression 
<div align=left>

The part of the eye that expresses calm is designed as `▯▯` and the part of the mouse is designed as `一`. After calibration, lights in the optional light array are counted to display this expression. Figure.6 shows the common expression displayed in the front panel.  
<div align=center><img src="https://github.com/GGGGroot/Facial-Motion-Capture-Helmet/blob/GGGGroot-patch-3/image/calm.jpg" length="1024" width="640">

Figure.6 the common expression 
<div align=left>

### Hardware design
The hardware of the helmet contains two parts: front panel and base plate. The front panel has two layers. The first layer of the front panel needs to carry the LED strip circuit of the system. The second layer of the front panel should obscure most of the circuit details and reduce the brightness of the LEDs appropriately. The base plate is the main part. There should be designed proper places that could carry the Raspberry Pi, the front panel and battery and the whole helmet needs to be designed longer than normal mask so that it can provide sufficient distance between camera and wearer’s face.  
#### Front panel design 
The front panel contains two layers: the outer layer and the inner layer. The inner layer of the front panel needs to carry the LED strip, and in the meanwhile, it should have enough holes that could let the wearer able to see clearly what is in front of. This component is created by 3D printing service and the dimension of the inner layer is shown in Figure. The 3D dimension of this part is shown in Figure.7. The outer layer of the panel can use frosted panels and it ensures that the wearer can see clearly in front while reducing brightness.   
<div align=center><img src="https://github.com/GGGGroot/Facial-Motion-Capture-Helmet/blob/GGGGroot-patch-3/image/front%20panel_00.jpg" length="1024" width="640">
 
Figure.7 Dimensions of the inner layer of the front panel layout   
<div align=center><img src="https://github.com/GGGGroot/Facial-Motion-Capture-Helmet/blob/GGGGroot-patch-3/image/3D%20front%20panel.png" length="1024" width="640">  
 
Figure.8 Three-dimensional model of the inner layer of the front panel 
<div align=left>    

#### Base plate design 
The base plate contains most of the helmet. It should hold the front panel in the front and provide space for carrying the Raspberry Pi. Therefore, four M2.5 holes were cut in the bottom of the base plate to secure the Raspberry Pi, and a 0.79-inch diameter hole was punched in the side for the power cable. The dimension of the base plate is shown in Figure.9. The 3D dimension of this part is shown in Figure.10. 
<div align=center><img src="https://github.com/GGGGroot/Facial-Motion-Capture-Helmet/blob/GGGGroot-patch-3/image/base%20plate_00.jpg" length="1024" width="640">    

Figure.9 Dimensions of the base plate layout 

<div align=center><img src="https://github.com/GGGGroot/Facial-Motion-Capture-Helmet/blob/GGGGroot-patch-3/image/3D%20base%20plate.png" length="1024" width="640">    

Figure.10 Three-dimensional model of the base plate 
<div align=left> 

### Auto start-up programme
To self-start a script and run a particular C++ file in the Raspberry Pi, the first thing is to create a script file and save it in a suitable location. In this project, we store it to `/home/raspberry/startup.sh. Any text editor can be used to create this file.     
After that, add the following to the script file:
```
#!/bin/bash
cd /home/raspberry/facecapture_test
./face_capture
```
The third step is to grant permission to execute the script file. Enter the following command in the terminal:
```
chmod +x /home/pi/startup.sh
```
The script file can now be added to the Raspberry Pi's boot entry. The project edit the `/etc/rc.local` file, which can be opened with any text editor. Add the following to the end of the document:
```
sudo -u raspberry /home/raspberry/startup.sh &
```
Now reboot the system and the script can automatically start to run.



