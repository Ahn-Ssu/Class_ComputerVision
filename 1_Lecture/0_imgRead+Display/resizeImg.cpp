#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat img = imread("/Users/ahnssu/git/Class_ComputerVision/Lena.png");
    Mat resize_img;

    /*
    img size function
    resize(Mat src, Mat dst, Size(cols, rows))
        1. src: input img
        2. dst: output img
        3. Size(cols, rows): Size of image to convert
    */
    resize(img, resize_img, Size(50, 50));

    imshow("original Img", img);
    imshow("resize img", resize_img);
    waitKey(0);
    return 0;
}