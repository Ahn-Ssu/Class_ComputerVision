#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat image = imread("/Users/ahnssu/git/Class_ComputerVision/Lena.png", 1);
    if ( !image.data) exit(1); //Check image
    

    circle(image, Point(25,25), 0, Scalar(0, 255, 10), 3, CV_AA, 0);
    imshow("Input image", image);

    waitKey(0);
    return 0;

}