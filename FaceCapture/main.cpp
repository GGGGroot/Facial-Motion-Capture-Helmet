#include <dlib/opencv.h>  
#include <opencv2/opencv.hpp>  
#include <dlib/image_processing/frontal_face_detector.h>  
#include <dlib/image_processing/render_face_detections.h>  
#include <dlib/image_processing.h>  
#include <dlib/gui_widgets.h>  

using namespace dlib;
using namespace std;
using namespace cv::ml;


#include <iostream>
#include <signal.h>
#include <unistd.h>
#include "ws2811.h"

#define LED_COUNT 132 // 根据实际LED数量调整
#define GPIO_PIN 18
#define DMA_CHANNEL 10

ws2811_t ledstring = {
    .freq = WS2811_TARGET_FREQ,
    .dmanum = DMA_CHANNEL,
    .channel = {
        [0] = {
            .gpionum = GPIO_PIN,
            .invert = 0,
            .count = LED_COUNT,
            .strip_type = WS2811_STRIP_GRB,
            .leds=0,
            .brightness = 100,
            .wshift=0,
            .rshift=0,
            .gshift=0,
            .bshift=0,
            .gamma=0,
        },
        [1] = {
            .gpionum = 0,
            .invert = 0,
            .count = 0,
            .strip_type = WS2811_STRIP_GRB,
            .leds=0,
            .brightness = 0,
            .wshift=0,
            .rshift=0,
            .gshift=0,
            .bshift=0,
            .gamma=0,
        },
    },
};

void lightUpMultipleLEDs(const std::vector<int>& ledIndices,uint32_t color) {
	if (ws2811_init(&ledstring) != WS2811_SUCCESS) {
		std::cerr << "ws2811_init failed" << std::endl;
	}

	for (int ledIndex : ledIndices) {
		if (ledIndex >= 0 && ledIndex < LED_COUNT) {
			ledstring.channel[0].leds[ledIndex] = color;
		}
		else {
			std::cerr << "Invalid LED index: " << ledIndex << std::endl;
		}
	}

	// 渲染LED颜色
	if (ws2811_render(&ledstring) != WS2811_SUCCESS) {
		std::cerr << "ws2811_render failed" << std::endl;
	}

	ws2811_fini(&ledstring);
}

int main()
{
	try
	{
		cv::VideoCapture cap(0);
		
		//29/03 speed up
		cap.set(cv::CAP_PROP_FOURCC,cv::VideoWriter::fourcc('H','2','6','4'));
		
		

		if (!cap.isOpened())
		{
			cerr << "Unable to connect to camera" << endl;
			return 1;
		}

		//image_window win;  

		// Load face detection and pose estimation models.  
		frontal_face_detector detector = get_frontal_face_detector();
		shape_predictor pose_model;
		deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;

		cv::Ptr<SVM> svm = StatModel::load<SVM>("/home/raspberry/FaceCapture/SVM_DATA.xml");

		cap.set(cv::CAP_PROP_FPS,30);
		//change width&length
		cap.set(cv::CAP_PROP_FRAME_WIDTH,320);
		cap.set(cv::CAP_PROP_FRAME_HEIGHT,240);

		// Grab and process frames until the main window is closed by the user.  
		while (cv::waitKey(1000) != 27)
		{
			// Grab a frame  
			cv::Mat temp;
			cap >> temp;

			cv_image<bgr_pixel> cimg(temp);
			// Detect faces   
			std::vector<rectangle> faces = detector(cimg);
			// Find the pose of each face.  
			std::vector<full_object_detection> shapes;
			for (unsigned long i = 0; i < faces.size(); ++i)
				shapes.push_back(pose_model(cimg, faces[i]));

			if (!shapes.empty()) {
				float testData[1][136];
				float params = -(faces[0].top() - faces[0].bottom()) / 300.0;
				for (int i = 0; i < 68; i++) {
					circle(temp, cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 2, cv::Scalar(255, 0, 0), -1);
					testData[0][i * 2] = (shapes[0].part(i).x() - faces[0].left()) / params;
					testData[0][i * 2+1] = (shapes[0].part(i).y() - faces[0].top()) / params;
					//  shapes[0].part(i).x();
				}
				cv::Mat result;
				
				cv::Mat query(1, 136, CV_32FC1, testData);

				if (svm->predict(query) == 250) {
					cv::putText(temp, "Happy" , cv::Point(20, 60),3, 2, cvScalar(0, 0, 255));
					cout << "Happy!" << endl;
					std::vector<int> ledIndices = { 10,11,25,26,31,32,45,46,54,55,
									65,66,78,79,91,92,101,102,114,115,128,129 }; // 要点亮的LED的索引列表
					lightUpMultipleLEDs(ledIndices, 0xFF0000);
				}
					
				if (svm->predict(query) == 170) {
					cv::putText(temp, "Common", cv::Point(20, 60), 3, 2, cvScalar(0, 0, 255));
					std::vector<int> ledIndices = { 24,25,26,27,28,29,30,31,32,65,66,78,79,89,90,103,104,114,115,128,129 }; // 要点亮的LED的索引列表
					lightUpMultipleLEDs(ledIndices, 0x00FF00);
				}
				if (svm->predict(query) == 300) {
					cv::putText(temp, "Shocked", cv::Point(20, 60), 3, 2, cvScalar(0, 0, 255));
					cout << "Shocked!" << endl;
					std::vector<int> ledIndices = { 8,9,10,11,12,13,25,26,31,32,48,49,50,51,52,53,
									64,65,66,78,79,80,88,91,102,105,113,114,115,128,129,130 }; // 要点亮的LED的索引列表
					lightUpMultipleLEDs(ledIndices, 0x0000FF);
				}

			}
			//Display it all on the screen  
			imshow("Motion Capture", temp);

		}
	}
	catch (serialization_error& e)
	{
		cout << "You need dlib's default face landmarking model file to run this example." << endl;
		cout << "You can get it from the following URL: " << endl;
		cout << "   http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
		cout << endl << e.what() << endl;
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
}
