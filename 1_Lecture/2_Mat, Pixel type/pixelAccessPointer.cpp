#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(){

    Mat img, img_gray;

    img = imread("/Users/ahnssu/git/Class_ComputerVision/Lena.png");
    img_gray = imread("/Users/ahnssu/git/Class_ComputerVision/Lena.png", 0);

    int value, B, G, R, channels;
    channels = img.channels();

    uchar* p;
    p = img.ptr<uchar>(50);
    //  using at operator
    cout << "pointer: " << *p << endl;

    int row = 100;
    B = p[row * channels + 0];
    G = p[row * channels + 1];
    R = p[row * channels + 2];

    cout << "at (" << row <<  ","<<"50)" << endl;
    cout << "value B: " << B << endl;
    cout << "value G: " << G << endl;
    cout << "value R: " << R << endl;

    // waitKey(0);

    return 0;

}