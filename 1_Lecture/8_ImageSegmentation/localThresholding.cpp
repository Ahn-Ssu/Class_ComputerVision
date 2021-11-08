#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat image, binary, adaptive_binary; 
    image = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/opencv.jpg",0);

    threshold(image, binary, 150, 255, THRESH_BINARY);
    adaptiveThreshold(image, adaptive_binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 85, 15);

    imshow("input image", image);
    imshow("binary", binary);
    imshow("adaptive binary", adaptive_binary);
    
    waitKey(0);
    return 0;

}