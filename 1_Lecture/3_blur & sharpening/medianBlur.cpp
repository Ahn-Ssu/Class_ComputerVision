#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat image = imread("/Users/ahnssu/git/Class_ComputerVision/2_Assignment/assn3/src/saltnpepper.png",0);
    Mat mf1, mf2; 


    medianBlur(image, mf1, 3);
    medianBlur(image, mf2, 9);

    imshow("image", image);
    imshow("mf1(3x3)", mf1);
    imshow("mf2(9x9)",mf2);
    waitKey(0);

    return 0;

}