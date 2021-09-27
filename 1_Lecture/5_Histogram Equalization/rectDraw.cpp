#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat image = imread("/Users/ahnssu/git/Class_ComputerVision/Lena.png", 1);
    if ( !image.data) exit(1); //Check image
    
    Rect rect = Rect(10, 10, 100, 100);
    rectangle(image, rect, Scalar(0,255,0), 4,8,0);

    imshow("Input image", image);

    waitKey(0);
    return 0;

}