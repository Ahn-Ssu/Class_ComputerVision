#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){

    Mat image = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/Lena.png");
    cvtColor(image, image, CV_BGR2GRAY);
    imshow("image", image);

    /* 
    void inRange(cv::InputArray src, cv::InputArray lowerb, cv::InputArray upperb, cv::OutputArray dst)
        - src: first input array
        - lowerb: inclusive lower boundary array or a scalar 
        - upperb: inclusive upper boundary array or a saclar
        - dst: output array of the same size as src and CV_8U type
    */
    inRange(image, Scalar(0, 133, 77), Scalar(255, 173, 127), image);

    imshow("inRanged", image);
    waitKey(0);
    return 0;

}