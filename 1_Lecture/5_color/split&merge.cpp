#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat image, image_YUV, dst;
    Mat yuv_channels[3];

    image = imread("/Users/ahnssu/git/Class_ComputerVision/2_Assignment/assn1&2/src/Lena.png");

    cvtColor(image, image_YUV, CV_BGR2YUV);
    split(image_YUV, yuv_channels);

    merge(yuv_channels,3,dst);
    // cvtColor(dst, dst, CV_YUV2BGR);

    imshow("Input image", image);
    imshow("Y image", yuv_channels[0]);
    imshow("U image", yuv_channels[1]);
    imshow("V image", yuv_channels[2]);
    imshow("YUV image", dst);

    waitKey(0);
    return 0;

}