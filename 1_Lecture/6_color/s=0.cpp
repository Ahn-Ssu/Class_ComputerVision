#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat image = imread("/Users/ahnssu/git/Class_ComputerVision/2_Assignment/assn1&2/src/Lena.png");
    Mat HSV, intensity_change, mask_out, change_color;
    vector<Mat> s1(3);
    vector<Mat> s2(3);
    vector<Mat> s3(3);

    int rows = image.rows;
    int cols = image.cols;
    uchar* h;
    uchar* s;
    uchar* v;

    cvtColor(image, HSV, CV_BGR2HSV);
    split(HSV, s1);
    split(HSV, s2);
    split(HSV, s3);

    
    for (int j = 0 ; j < rows ; j ++){
        h = s1[0].ptr<uchar>(j);
        s = s1[1].ptr<uchar>(j);
        for (int i = 0; i < cols;i++){
            h[i] = 128; 
            s[i] = 0;
        }
    }
    for (int j = 0 ; j < rows ; j ++){
        h = s2[0].ptr<uchar>(j);
        s = s2[1].ptr<uchar>(j);
        for (int i = 0; i < cols;i++){
            h[i] = 0; 
            s[i] = 0;
        }
    }
    for (int j = 0 ; j < rows ; j ++){
        h = s3[0].ptr<uchar>(j);
        s = s3[1].ptr<uchar>(j);
        for (int i = 0; i < cols;i++){
            h[i] = 255; 
            s[i] = 0;
        }
    }

    

    merge(s1, intensity_change);
    merge(s2, mask_out);
    merge(s3, change_color);
    cvtColor(intensity_change, intensity_change, CV_HSV2BGR);
    cvtColor(mask_out, mask_out, CV_HSV2BGR);
    cvtColor(change_color, change_color, CV_HSV2BGR);

    imshow("Input image", image);
    imshow("s1 (h=128, s=0) image", mask_out);
    imshow("s2 (h=0, s=0) image", intensity_change);
    imshow("s3 (h=255, s=0) image", change_color);

    waitKey(0);
    return 0;

}