#include <dlib/opencv.h>
#include <opencv2/opencv.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <string>

using namespace dlib;
using namespace std;
void write_to_txt(string name, string content, bool overwrite);
int main()
{
    try
    {
        cv::VideoCapture cap(0);

        //image_window win;

        // Load face detection and pose estimation models.
        frontal_face_detector detector = get_frontal_face_detector();
        shape_predictor pose_model;
        deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;
        std::vector<rectangle> faces2;
        // Grab and process frames until the main window is closed by the user.
        int filename = 0;

        if (!cap.isOpened())
        {
            cerr << "Unable to connect to camera" << endl;
            return 1;
        }

        int frame_count = cap.get(7);

        while (cv::waitKey(30) != 27)
        {
            cv::Mat temp;
            cap >> temp;
            cv_image<bgr_pixel> cimg(temp);
            std::vector<rectangle> faces = detector(cimg);
            if (!faces.empty()) faces2 = faces;
            std::vector<full_object_detection> shapes;

            if (faces.empty()) {
            }
            else {
                for (unsigned long i = 0; i < faces.size(); ++i)
                    shapes.push_back(pose_model(cimg, faces[i]));
            }
            if (!shapes.empty()) {
                cv::line(temp, cvPoint(faces[0].left(), faces[0].top()), cvPoint(faces[0].right(), faces[0].top()), cv::Scalar(255, 0, 0));
                cv::line(temp, cvPoint(faces[0].left(), faces[0].top()), cvPoint(faces[0].left(), faces[0].bottom()), cv::Scalar(255, 0, 0));

                filename++;
                float coef = -(faces[0].top() - faces[0].bottom()) / 300.0;
                cout << coef << endl;
                for (int i = 0; i < 68; i++) {
                    circle(temp, cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 3, cv::Scalar(0, 0, 255), -1);
                    putText(temp, to_string(i), cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 0, 0), 1, 4);
                    //--------------这部分是用来采集训练数据的
                    write_to_txt((to_string(filename) + ".txt"), to_string((shapes[0].part(i).x() - faces[0].left()) / coef), 0);
                    write_to_txt((to_string(filename) + ".txt"), to_string((shapes[0].part(i).y() - faces[0].top()) / coef), 0);
                }
            }

            imshow("Dlib Landmarks", temp);
        }
        cv::destroyAllWindows();
    }
    catch (serialization_error& e)
    {
        cout << "You need dlib's default face landmarking model file to run this example." << endl;
        cout << "You can get it from the following URL: " << endl;
        cout << "   http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
        cout << endl << e.what() << endl;
    }
}
void write_to_txt(string name, string content, bool overwrite) {
        ofstream write(name, overwrite ? ios::trunc : ios::app);

        if (write.is_open()) {
            write << content << endl;
            write.close();
        }

