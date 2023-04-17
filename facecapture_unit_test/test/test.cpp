#include <gtest/gtest.h>
#include "..\src\headfile.h"

namespace{
	/*
	 	TEST(LightTest,InitLight)
	{
		EXPECT_TRUE(ledstring);
		}
	*/
	TEST(LightTest, MultiLeds)
	{
		EXPECT_TRUE(lightUpMultipleLEDs({1,2},0xFF0000));
		}


	
	TEST(CameraTest, InitCamera)
	{
		cv::VideoCapture cap(0);
		EXPECT_TRUE(initCamera(cap));
		}
	
	TEST(CameraTest, MotionTest)
	{
		frontal_face_detector detector_test = get_frontal_face_detector();
		shape_predictor pose_model_test;
		deserialize("/home/raspberry/facecapture_test/build/shape_predictor_68_face_landmarks.dat") >> pose_model_test;
		cv::Ptr<SVM> svm_test = StatModel::load<SVM>("/home/raspberry/FaceCapture/SVM_DATA.xml");
		cv::VideoCapture cap(0);
		cv::Mat temp_test;
		cap >> temp_test;
		
		EXPECT_TRUE(recognizeMotion(temp_test, detector_test, pose_model_test, svm_test));
	}

}
