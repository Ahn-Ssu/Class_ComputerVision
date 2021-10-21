#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat gray = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/moon.png", 0);
    Mat color;

    applyColorMap(gray, color, COLORMAP_OCEAN);


    imshow("Input image", gray);
    imshow("cc image", color);

    waitKey(0);
    return 0;

}