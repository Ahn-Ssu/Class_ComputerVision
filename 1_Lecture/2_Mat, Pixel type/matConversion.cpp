#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(){

    Mat img;
    Mat after_convertTo, after_convertScaleAbs;
    img = imread("/Users/ahnssu/git/Class_ComputerVision/Lena.png");

    imshow("original", img);

    img.convertTo(after_convertTo, CV_16SC1);
    imshow("after convertTo", after_convertTo);

    convertScaleAbs(img, after_convertScaleAbs, 2, 3);
    imshow("after convertScaleAbs", after_convertScaleAbs);

    img.setTo(Scalar(0));
    imshow("after setTo", img);

    waitKey(0);


    return 0;

}