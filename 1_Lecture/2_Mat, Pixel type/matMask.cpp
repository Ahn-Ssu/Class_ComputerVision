#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(){

    Mat img;
    img = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/moon.png");

    Mat mask;
    mask = Mat::zeros(img.size(), img.type());
    
    Mat copy;
    // resize(img, img, Size(256, 256));
    Rect rect = Rect(26, 76, 170, 100); 
    rectangle(mask, rect, Scalar(255, 0 , 0), -1, 8 , 0);
    img.copyTo(copy, mask);

    imshow("copied", copy);
    // imshow("origin",img);
    waitKey(0);

    cout << img.size() << endl; 

    return 0;

}