#ifndef __MY_CODE_H_
#define __MY_CODE_H_

#include <dlib/opencv.h>  
#include <opencv2/opencv.hpp>  
#include <dlib/image_processing/frontal_face_detector.h>  
#include <dlib/image_processing/render_face_detections.h>  
#include <dlib/image_processing.h>  
#include <dlib/gui_widgets.h> 

#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <ws2811.h>

#define LED_COUNT 132 // 根据实际LED数量调整
#define GPIO_PIN 18
#define DMA_CHANNEL 10


using namespace dlib;
using namespace std;
using namespace cv::ml;



bool lightUpMultipleLEDs(const std::vector<int>& ledIndices,uint32_t color);
bool initCamera(cv::VideoCapture cap);
bool recognizeMotion(cv::Mat temp,frontal_face_detector detector,shape_predictor pose_model,cv::Ptr<SVM> svm);

#endif
