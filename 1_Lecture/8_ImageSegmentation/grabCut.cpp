#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat result, bgModel, fgModel, image, foreground;
    image = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/faceCapture.png");
    resize(image, image, Size(1200, 800));

    // inner rectangle which includes foreground 
    Rect Rect(480, 370, 180, 300);
    // Rect rect = Rect(10, 10, 100, 100);
    rectangle(image, Rect, Scalar(0,255,0), 4,8,0);
    
    grabCut(image, result, Rect, bgModel, fgModel, 20, GC_INIT_WITH_RECT);
    compare(result, GC_PR_FGD, result, CMP_EQ);
    foreground = Mat(image.size(), CV_8UC3, Scalar(0, 0, 0));

    image.copyTo(foreground, result);

    imshow("original", image);
    imshow("result", result);
    imshow("Foreground", foreground);
    
    waitKey(0);
    return 0;

}