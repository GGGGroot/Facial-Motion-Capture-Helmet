# Facial-Motion-Capture-Helmet    
![sample](https://github.com/GGGGroot/Facial-Motion-Capture-Helmet/blob/main/image/sample.png?raw=true)
## Project Contributors
- Yixuan Pang: project management and hardware designing
- Shenjia Ding: pair programming as driver and system environment set-up
- Wenjin Chi: LED strip designing and soldering, expression display coding
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
- [ ] conducting unit test of the main function
- [ ] combining the LED strip function into the main program
- [ ] testing the final program  
#### LED strip designing and soldering - Wenjin Chi  
- [x] Buying LED strip and camera
- [x] writing LED testing program to test LED strip
- [x] booking a laboratory and carrying out soldering work
- [x] connecting to the Raspberry Pi and testing the performance of the LED strip
- [x] writing the corrsponding expressions display in LED strip
- [x] conducting unit test of the expression display function
- [x] creating social media of this project
- [ ] upgrading social media and README file
#### Hardware designing and document writing - Yixuan Pang
- [x] creating github repository of this project and writing the README file
- [x] designing front panel of the helmet
- [x] booking a technical service to 3D print the front panel
- [x] upgrading README file and creating Gantt chart of this project to illustrate timeline
- [x] designing base plate of the helmet
- [x] booking a technical service to 3D print the base plate
- [x] writing boot-up coding
- [ ] conducting unit test of the auto boot-up function
## Unit Test

## Project guide
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

To recognise expressions, facial feature points are first normalised and used as input to the SVM classifier, which uses the OpenCV library's `StatModel::load` method to load pre-trained model files. Based on the results of the SVM predictions, the system can determine whether the face is a happy, normal or surprised expression. 

Main ideas: (training module + test module)  

Training module: 

- [x] Dlib feature points are extracted and normalized after a person makes a specific expression.  
- [x] Each picture stores 136 dimensional data stored into a specific numbered TXT for easy recall.  
- [x] Use SVM classifier to classify and train into XML. 

  

Test module:  

Read in the trained XML, classify each frame and display the results. 
 
### Light array connection and display 
In this project, WS2812B LED strip was used as the output equipment to show the corresponding facial expressions on the helmet. Light sets are available in 30 per metre and 144 per metre. The project uses 144 per metre, deployed around the eyes and mouth.
#### LED strip soldering 
After purchasing the LED strip, the first thing is to cut and solder the WS2812B. Since the eyes will be longer than the mouth during display, 3 rows of 25 were cut to show the eyes and 3 rows of 20 were cut to show the mouth. After that, the six light arrays are connected in sequence by aligning each row with the corresponding earth, power and signal ports and applying insulated wire to prevent short circuits. When connecting, it should be taken care to solder in the direction that the arrows in the light array are pointing. If the arrows are pointing in the opposite direction, then the light array will not work properly either. Another thing to keep in mind is to align the design with the position of the front panel so as not to block the holes reserved for seeing things clearly. Figure. shows the soldering process of the LED strip and figure. shows the soldered light array. 
#### LED strip display 
It is pivotal to know where the LED strip begins and the number of each LED. First, connect the Raspberry Pi to the light array via the Dupont wire, with the start of the arrow or terminal being the start of the light array. The LED arrays are counted and marked in turn as a number for each lamp. In this project, a total of three facial expressions are recognised and displayed, namely happy, calm and shocked. 

The part of the eye that expresses happiness is designed as `><` and the part of the mouse is designed as `v`. After calibration, lights in the optional light array are counted to display this expression:  . Figure. shows the happiness expression displayed in the front panel.  

The part of the eye that expresses shock is designed as `▯▯` and the part of the mouse is designed as `▯`. After calibration, lights in the optional light array are counted to display this expression. Figure. shows the shocked expression displayed in the front panel.  

The part of the eye that expresses calm is designed as `▯▯` and the part of the mouse is designed as `一`. After calibration, lights in the optional light array are counted to display this expression:  . Figure. shows the calm expression displayed in the front panel.  
### Hardware design
The hardware of the helmet contains two parts: front panel and base plate. The front panel has two layers. The first layer of the front panel needs to carry the LED strip circuit of the system. The second layer of the front panel should obscure most of the circuit details and reduce the brightness of the LEDs appropriately. The base plate is the main part. There should be designed proper places that could carry the Raspberry Pi, the front panel and battery and the whole helmet needs to be designed longer than normal mask so that it can provide sufficient distance between camera and wearer’s face.  
#### Front panel design 
The front panel contains two layers: the outer layer and the inner layer. The inner layer of the front panel needs to carry the LED strip, and in the meanwhile, it should have enough holes that could let the wearer able to see clearly what is in front of. This component is created by 3D printing service and the dimension of the inner layer is shown in Figure. The 3D dimension of this part is shown in Figure. The outer layer of the panel    
<div align=center><img src="https://github.com/GGGGroot/Facial-Motion-Capture-Helmet/blob/GGGGroot-patch-3/image/front%20panel_00.jpg" length="1024" width="640">
 
  Figure. Dimensions of the inner layer of the front panel layout   
<div align=center><img src="https://github.com/GGGGroot/Facial-Motion-Capture-Helmet/blob/GGGGroot-patch-3/image/3D%20front%20panel.png" length="1024" width="640">  
 
  Figure. Three-dimensional model of the inner layer of the front panel 

#### Base plate design 
The base plate contains most of the helmet. It should hold the front panel in the front and provide space for carrying the Raspberry Pi. Therefore, four M2.5 holes were cut in the bottom of the base plate to secure the Raspberry Pi, and a 0.79-inch diameter hole was punched in the side for the power cable. The dimension of the base plate is shown in Figure. The 3D dimension of this part is shown in Figure. 
<div align=center><img src="https://github.com/GGGGroot/Facial-Motion-Capture-Helmet/blob/GGGGroot-patch-3/image/base%20plate_00.jpg" length="1024" width="640">    

  Figure. Dimensions of the base plate layout 

<div align=center><img src="https://github.com/GGGGroot/Facial-Motion-Capture-Helmet/blob/GGGGroot-patch-3/image/3D%20base%20plate.png" length="1024" width="640">    

  Figure. Three-dimensional model of the base plate 
  
 









