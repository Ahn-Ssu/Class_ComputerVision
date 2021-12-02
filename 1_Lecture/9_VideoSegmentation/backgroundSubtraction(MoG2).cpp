#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2();
    Mat backgroundImg, image,  foregroundMask, foregroundImg;
    VideoCapture cap("/Users/ahn_ssu/git/Class_ComputerVision/src/Faces.mp4");

    float learning_rate = 0.5f ;
    int cnt = 1 ;
    while(true){
        cap >> image;
        if(image.empty()) break;

        resize(image, image, Size(640, 480));


        if (foregroundMask.empty()) 
            foregroundMask.create(image.size(), image.type());

        // image: Next video frame. Floating point frame will be used without scaling and should be in range [0, 255]
        // foregroundMask: The output foreground mask as an 8-bit binary image.
        cnt ++;
        bg_model -> apply(image, foregroundMask);
        GaussianBlur(foregroundMask, foregroundMask, Size(13, 13), 3.5, 3.5);
        threshold(foregroundMask, foregroundMask, 50, 255, THRESH_BINARY);
        foregroundImg = Scalar::all(0);
        image.copyTo(foregroundImg, foregroundMask);

        imshow("foreground image", foregroundImg);
        waitKey(33);
    }
    return 0;

}