#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){

    Mat image = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/faceCapture.png");
    Mat inRanged_mask ;
    Mat inRanged_img;
    /* 
    void inRange(cv::InputArray src, cv::InputArray lowerb, cv::InputArray upperb, cv::OutputArray dst)
        - src: first input array
        - lowerb: inclusive lower boundary array or a scalar 
        - upperb: inclusive upper boundary array or a saclar
        - dst: output array of the same size as src and CV_8U type
    */
    cvtColor(image, image, CV_BGR2YCrCb);
    inRange(image, Scalar(20, 133, 77), Scalar(220, 173, 127), inRanged_mask);

    cvtColor(inRanged_mask, inRanged_mask, CV_GRAY2BGR);
    cvtColor(inRanged_mask, inRanged_mask, CV_BGR2YCrCb); // 이렇게 얘를 먼저 고쳐야 이렇게 됨
    image.copyTo(inRanged_img, inRanged_mask);
    cvtColor(image, image, CV_YCrCb2BGR);
    cvtColor(inRanged_img, inRanged_img, CV_YCrCb2BGR);
    
    imshow("image", image);
    imshow("inRanged", inRanged_mask);
    imshow("inRanged img", inRanged_img);
    // cout << inRanged_img << endl;
    waitKey(0);
    return 0;

}