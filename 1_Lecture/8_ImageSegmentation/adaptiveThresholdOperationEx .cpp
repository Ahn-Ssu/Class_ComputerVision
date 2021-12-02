#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){

    Mat image = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/faceCapture.png");
    cvtColor(image, image, CV_BGR2GRAY);

    Mat dst;
    adaptiveThreshold(image, dst, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 7, 10);

    imshow("dst", dst);
    imshow("image", image);
    waitKey(0);
    return 0;

}