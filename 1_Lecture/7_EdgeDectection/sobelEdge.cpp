#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat imgae, blur, grad_x, grad_y, abs_grad,x_, abs_grad_y, result;
    Mat image = imread("/Users/ahnssu/git/Class_ComputerVision/2_Assignment/assn1&2/src/Lena.png", 0);
    GaussianBlur(image, blur, Size(5,5), 5, 5, BORDER_DEFAULT);

    // performs Sobel operation which is a discrete differentiation
    // blur: input Mat, grad_x: output MAt, CV_16S: depth of the output Mat
    // 1 : order of derivative in x direction, 0 : order of derivative in y direction
    // 3 : size of the extended Sobel kernel; it must be 1,3,5, or 7.
    Sobel(blur, grad_x, CV_16S, 1, 0, 3);
    convertScaleAbs(grad_x, abs_grad_x);

    Sobel(blur, grad_y, CV_16S, 0, 1, 3);
    convertScaleAbs(grad_y, abs_grad_y);

    // abs_grad_x : input g_x Mat
    // 0.5 : weight for abs_grad_x
    // abs_grad_y : input g_y Mat
    // 0.5 : weight for abs_grad_y
    // 0 : offset added to weighted sum
    // result : output Mat
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, result);


    imshow("X", abs_grad_x);
    imshow("Y", abs_grad_y);
    imshow("Input image", image);
    imshow("Sobel Edge Detector", result);

    waitKey(0);
    return 0;

}