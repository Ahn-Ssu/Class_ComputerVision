#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(){

    Mat img, img_gray;
    int value, B, G, R, channels;

    img = imread("/Users/ahnssu/git/Class_ComputerVision/Lena.png");
    img_gray = imread("/Users/ahnssu/git/Class_ComputerVision/Lena.png", 0);

    //  using at operator
    value = img_gray.at<uchar>(50, 100);
    cout << "value: " << value << endl;

    B = img.at<Vec3b>(50, 100)[0];
    G = img.at<Vec3b>(50, 100)[1];
    R = img.at<Vec3b>(50, 100)[2];

    cout << "value B: " << B << endl;
    cout << "value G: " << G << endl;
    cout << "value R: " << R << endl;

    // waitKey(0);

    return 0;

}