#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(){

    Mat img;
    img = imread("/Users/ahnssu/git/Class_ComputerVision/Lena.png");

    Mat mask;
    mask = Mat::zeros(img.size(), img.type());
    
    // Mat copy;

    // Rect rect = Rect(10, 10, 100, 100); 
    // rectangle(mask, rect, Scalar(255, 0 , 0), -1, 8 , 0);
    // img.copyTo(copy, mask);

    // imshow("copied", copy);
    // waitKey(0);

    cout << mask << endl; 

    return 0;

}