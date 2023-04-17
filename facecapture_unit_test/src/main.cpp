

#include "headfile.h"


int main()
{
	try
	{
		cv::VideoCapture cap(0);
		initCamera(cap);
		if (!cap.isOpened())
		{
			cerr << "Unable to connect to camera" << endl;
			//return 
			return 1;
		}
		
		frontal_face_detector detector = get_frontal_face_detector();
		shape_predictor pose_model;
		deserialize("/home/raspberry/facecapture_test/build/shape_predictor_68_face_landmarks.dat") >> pose_model;
		cv::Ptr<SVM> svm = StatModel::load<SVM>("/home/raspberry/FaceCapture/SVM_DATA.xml");
		
		
		
		while (cv::waitKey(100) != 27)
		{
			// Grab a frame  
			cv::Mat temp;
			cap >> temp;
			
			recognizeMotion(temp,detector,pose_model,svm);
			

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
