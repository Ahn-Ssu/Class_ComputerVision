#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat gray = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/contours.png", 0);
    Mat result;
    threshold(gray, result, 230, 255, THRESH_BINARY_INV);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours(result, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    putText(result, format("contour count: %d", contours.size()), Point(50, 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(128), 4);
    
    imshow("contours", result);
    waitKey(0);
    return 0;

}