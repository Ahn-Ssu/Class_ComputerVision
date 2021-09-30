#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat image, image_YUV;
    image = imread("/Users/ahnssu/git/Class_ComputerVision/2_Assignment/assn1&2/src/Lena.png");


    cvtColor(image, image_YUV, CV_BGR2YUV);

    imshow("Input image", image);

    waitKey(0);
    return 0;

}