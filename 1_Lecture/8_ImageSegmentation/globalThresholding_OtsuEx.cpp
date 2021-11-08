#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat image, result;
    image = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/Lena.png", 0);
    threshold(image, result, 0, 255, THRESH_BINARY | THRESH_OTSU);

    imshow("input image", image);
    imshow("result", result);
    
    waitKey(0);
    return 0;

}