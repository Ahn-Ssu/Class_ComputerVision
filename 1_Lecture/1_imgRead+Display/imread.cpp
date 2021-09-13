#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat gray_image, color_image;


    /*
    read img function
    Mat imread( const string& filename, int flags= 1)
        1. filename: filePath
        2. Flag 0/1: read image as gray/color channel
    */
    // 0 on the 2nd param. means read img in grayscale
    gray_image = imread("/Users/ahnssu/git/Class_ComputerVision/Lena.png", 0);

    // blank 2nd parameter means 1, which means read img in colors;
    color_image = imread("/Users/ahnssu/git/Class_ComputerVision/Lena.png");


    /*
    display img function
    void imshow(const string &winname, InputArray mat)
        1. winname: name of the window
        2. mat : image to be shown
    */
    imshow("Original", color_image);
    waitKey(0);
}