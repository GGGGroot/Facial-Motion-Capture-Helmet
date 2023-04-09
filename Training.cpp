#include <opencv2/opencv.hpp>
#include <string>
#include <fstream>
using namespace std;
using namespace cv;
using namespace cv::ml;

void read_data(float data_array[150][136], int start, string directory);
int main()
{
    float data_array[150][136];

    read_data(data_array, 0, "Calm");
    read_data(data_array, 50, "Happy");
    read_data(data_array, 100, "Disgusted");
    int face_labels[150];
    for (int i = 0; i < 50; i++) {
        face_labels[i] = 170;
        face_labels[i + 50] = 250;
        face_labels[i + 100] = 300;
    }

    //训练需要用到的数据
    //	int 标签[4] = { 1, 2, 3, 4 };
    //	float 训练数据[4][2] = { { 31, 12 },{ 65, 220 },{ 440, 350 },{ 400, 400 } };
    //转为Mat以调用
    Mat trainingMat(150, 136, CV_32FC1, data_array);
    Mat labelMat(150, 1, CV_32SC1, face_labels);
    //训练的初始化
    Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setKernel(SVM::LINEAR);
    svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
    //开始训练
    svm->train(trainingMat, ROW_SAMPLE, labelMat);
    svm->save("SVM_DATA.xml");
}

void read_data(float data_array[150][136], int start, string directory) {
    fstream read_file;

    for (int i = 0; i < 50; i++) {
        read_file.open(directory + "\\" + to_string(i + 1) + ".txt");
        for (int j = 0; j < 136; j++) {
            string input_data;
            read_file >> input_data;
            data_array[i + start][j] = atof(input_data.c_str());
        }
        read_file.close();
    }
}
