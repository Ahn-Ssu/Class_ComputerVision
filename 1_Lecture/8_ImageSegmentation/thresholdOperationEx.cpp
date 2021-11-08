#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){

    Mat image = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/Lena.png");
    cvtColor(image, image, CV_BGR2GRAY);

    Mat dst;
    /* 
    double threshold(Mat src, Mat dst, double thresh, double maxval, int type)
        - apply fixed level thresh to each array element
        - Typically used to get binary image from grayscale input image
        - maxval: dst(l) = maxval if scr(l) > thresh, otherwise -> 0, when type is THRESH_BINARY 
            - type : THRESH_BINARY, THRESH_NIARY_INV, THRESH_TRUNC, THRESH_TOZERO, THRESH_TOZERO_INV
    */
    threshold(image, dst, 100, 255, THRESH_BINARY);

    imshow("dst", dst);
    imshow("image", image);
    waitKey(0);
    return 0;

}