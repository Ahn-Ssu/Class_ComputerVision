#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat img1 = imread("/Users/ahnssu/git/Class_ComputerVision/Lena.png");
    Mat img2 = imread("/Users/ahnssu/git/Class_ComputerVision/Lena.png");
    Mat dst;

    add(img1, img2, dst);
    
    float coef_ = 1.5F;
    scaleAdd(img1, coef_, img2, dst);
    absdiff(img1, img2, dst);
    subtract(img1, img2, dst);


    imshow("addition result", dst);
    waitKey(0);
    return 0;

}