#include "headfile.h"


void initCamera(cv::VideoCapture cap)
{
		
		
		//29/03 speed up
		cap.set(cv::CAP_PROP_FOURCC,cv::VideoWriter::fourcc('H','2','6','4'));
		
		//29/03 output fps 
		cap.set(cv::CAP_PROP_FPS,30);
		//change width&length
		cap.set(cv::CAP_PROP_FRAME_WIDTH,320);
		cap.set(cv::CAP_PROP_FRAME_HEIGHT,240);	
	}




void recognizeMotion(cv::Mat temp,frontal_face_detector detector,shape_predictor pose_model,cv::Ptr<SVM> svm)
{
	
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
			//printf("fps: %d \n",fps);
			cout << "Happy!" << endl;
			//lightup(0x00FF00);
			std::vector<int> ledIndices = { 10,11,25,26,31,32,45,46,54,55,
									65,66,78,79,91,92,101,102,114,115,128,129 }; // 要点亮的LED的索引列表
			lightUpMultipleLEDs(ledIndices, 0xFF0000);
			}
				
		if (svm->predict(query) == 170) {
			cv::putText(temp, "Common", cv::Point(20, 60), 3, 2, cvScalar(0, 0, 255));
			//printf("fps: %d \n",fps);
			cout << "Common!" << endl;
			//lightup(0xFF0000);
			std::vector<int> ledIndices = { 24,25,26,27,28,29,30,31,32,65,66,78,79,89,90,103,104,114,115,128,129 }; // 要点亮的LED的索引列表
			lightUpMultipleLEDs(ledIndices, 0x00FF00);
		}
		if (svm->predict(query) == 300) {
			cv::putText(temp, "Shocked", cv::Point(20, 60), 3, 2, cvScalar(0, 0, 255));
			//printf("fps: %d \n",fps);
			cout << "Shocked!" << endl;
			//lightup(0x0000FF);
			std::vector<int> ledIndices = { 8,9,10,11,12,13,25,26,31,32,48,49,50,51,52,53,
							64,65,66,78,79,80,88,91,102,105,113,114,115,128,129,130 }; // 要点亮的LED的索引列表
			lightUpMultipleLEDs(ledIndices, 0x0000FF);
		}
				//	cout<<	svm->predict(query)<<endl;
			//	cout << ��� << endl;
		}
			//Display it all on the screen  
		cv::imshow("Motion Capture", temp);
}
