#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat image = Mat::zeros(400, 600, CV_8UC3);
    int w = image.cols;
    int h = image.rows;

    putText(image, format("width: %d, height: %d 무야호", w ,h), Point(50,80), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4, CV_AA);
     



    imshow("Input image", image);

    waitKey(0);
    return 0;

}