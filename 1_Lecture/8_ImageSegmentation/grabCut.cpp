#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat result, bgModel, fgModel, image, foreground;
    image = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/dog.png");

    // inner rectangle which includes foreground 
    Rect rectangle(65, 0, 170, 230);
    grabCut(image, result, rectangle, bgModel, fgModel, 10, GC_INIT_WITH_RECT);
    compare(result, GC_PR_FGD, result, CMP_EQ);
    foreground = Mat(image.size(), CV_8UC3, Scalar(255, 255, 255));

    image.copyTo(foreground, result);

    imshow("original", image);
    imshow("result", result);
    imshow("Foreground", foreground);
    
    waitKey(0);
    return 0;

}