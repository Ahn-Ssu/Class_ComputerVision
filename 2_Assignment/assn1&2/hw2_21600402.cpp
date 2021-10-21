#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define L UINT8_MAX
#define constant 1.0f

int main(){
    Mat srcImg;

    // require 1, Read an image “lena.png”
    srcImg = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/exam1.png",0);         
    Mat negative_img, log_img, gamma_img;
    
    imshow("Original", srcImg);
    
    // require 2, Negative transformation (Result mat: negative_img) 
    negative_img = srcImg.clone();

    negative_img.setTo(L-1);
    subtract(negative_img, srcImg, negative_img);

    imshow("Negative", negative_img);

    // require 3, Log transformation (Result mat: log_img)
    log_img = srcImg.clone();

    log_img.convertTo(log_img, CV_32F);             // require 3-2, To use log function, pixel type of input should be floating point
    
    log_img = log_img + 1; // s = c * log(1+r)
    log(log_img, log_img);                          // require 3-1, Use log(mat a) function to perform log operation
    normalize(log_img, log_img, 0, L, NORM_MINMAX); // require 3-3, Also use normalize(img, img, 0, 255, NORM_MINMAX)
    convertScaleAbs(log_img, log_img, constant);
    log_img.convertTo(log_img, CV_8UC1);

    imshow("log", log_img);
    
    // require 4, Gamma transformation with gamma as 0.5 (Result mat gamma_img)
    gamma_img = srcImg.clone();

    gamma_img.convertTo(gamma_img, CV_32F);
    normalize(gamma_img, gamma_img, 0, 1.0f, NORM_MINMAX);
    pow(gamma_img, 0.5, gamma_img);
    normalize(gamma_img, gamma_img, 0, L, NORM_MINMAX);
    convertScaleAbs(gamma_img, gamma_img, constant);
    gamma_img.convertTo(gamma_img, CV_8UC1);

    imshow("gamma", gamma_img);
    
    waitKey(0);
}