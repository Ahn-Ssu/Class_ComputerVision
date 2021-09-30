#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat img1 = imread("/Users/ahnssu/git/Class_ComputerVision/Lena.png", 0);
    Mat img2 = imread("/Users/ahnssu/git/Class_ComputerVision/Lena.png", 0);
    Mat dst;
    Mat mask = Mat::zeros(img1.size(), img1.type());
    cout << img2.size();
    add(img1, img2, dst, mask);
    
    // float coef_ = 1.5F;
    // scaleAdd(img1, coef_, img2, dst);
    // absdiff(img1, img2, dst);
    // subtract(img1, img2, dst);


    imshow("addition result", dst);
    waitKey(0);
    return 0;

}