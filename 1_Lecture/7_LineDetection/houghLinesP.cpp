#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat imgae, edge, result;
    float rho, theta, a, b, x0, y0;
    Point p1, p2;
    vector <Vec4i> lines;

    image = imread("/Users/ahnssu/git/Class_ComputerVision/2_Assignment/assn1&2/src/Lena.png");
    result = image.clone();

    cvtColor(image, image, CV_BGR2GRAY);
    Canny(image, edge, 50, 200, 3);

    // applying Hough Transform to find lines in the image
    // edge: input Mat, lines: output vector of lines
    // 1 : (rho) distance resolution of the accumulator in pixels
    // CV_PI/180: (theta) angle resolution of the accumulator in radians
    // 50: (threshold) accumulator threshold parameter
    
    // 10: (minLineLength) minimum line length.
    // 300: (maxLineGap) maximum allowed gap between points on the same line to link them
    HoughLinesP(edge, lines, 1, CV_PI / 180, 50, 10, 300);

    for (int i = 0; i < lines.size(); i++){
        Vec4i l = lines[i];
        line(result, 
            Point(l[0], l[1]), 
            Point(l[2], l[3]), 
            Scalar(0,0,255), 3, 8);
    }

    imshow("Input image", image);
    imshow("edge", edge);
    imshow("Hough Transform P", result);

    waitKey(0);
    return 0;

}