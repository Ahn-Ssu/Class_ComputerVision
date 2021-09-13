#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    /* 
    Mat(Matrix) type constructors, not all
        Mat(int rows, int cols, int type)
        Mat(Size size, int type)
        Mat(const Mat &m)
        Mat(Size size, int type, const Scalar& s)
    */

   Mat mtx1(3, 3, CV_32F);              // make a 3x3 floating-point matrix
   Mat mxt2(10, 1, CV_64FC2);           // make a 10x1 2-channel floating-point matrix
   Mat img1(1080, 1920, CV_8UC3);        // make a 3-channel(color) img of 1920 col n 1080 row 
   Mat img2(Size(1920, 1080), CV_8UC3);  // make a 3-channel img of 1920 col n 1080 row


    int w = 150, h = 100;

    Mat image(h,w, CV_8UC1, Scalar(255,0,0));
    cout << "Size: " << image.size().height << "," << image.size().width << endl;

    imshow("image", image);
    waitKey(0);

    return 0;

}