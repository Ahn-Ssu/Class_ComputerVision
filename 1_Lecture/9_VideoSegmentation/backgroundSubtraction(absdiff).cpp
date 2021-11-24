#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    VideoCapture capture("/Users/ahn_ssu/git/Class_ComputerVision/src/background.mp4");
    Mat background, image, gray, result, foregroundMask, foregroundImg;


    capture >> background;
    cvtColor(background, background, CV_BGR2GRAY);


    while(true){
        if(capture.grab() == 0 ) break;

        capture.retrieve(image);
        cvtColor(image, gray, CV_BGR2GRAY);

        absdiff(background, gray, foregroundMask);
        threshold(foregroundMask, foregroundMask, 50, 255, CV_THRESH_BINARY);
        foregroundMask.copyTo(foregroundImg);
        gray.copyTo(foregroundImg, foregroundMask);

        imshow("foregroundImg", foregroundImg);
        imshow("foregroundMask", foregroundMask);
        imshow("background", background);

        waitKey(33);
    }
    return 0;

}