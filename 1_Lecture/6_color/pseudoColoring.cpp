#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat gray = imread("/Users/ahnssu/git/Class_ComputerVision/2_Assignment/assn1&2/src/Lena.png", 0);
    Mat color;

    applyColorMap(gray, color, COLORMAP_JET);


    imshow("Input image", gray);
    imshow("cc image", color);

    waitKey(0);
    return 0;

}