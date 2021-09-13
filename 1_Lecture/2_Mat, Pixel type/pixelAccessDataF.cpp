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

    // Data function
    uchar* data = (uchar*)img.data;
    //  using at operator
    cout << "pointer: " << *data << endl;


    B = data[(50*img.cols + 100) * channels + 0];
    G = data[(50*img.cols + 100) * channels + 1];
    R = data[(50*img.cols + 100) * channels + 2];

    cout << "img.cols :" << img.cols << " ,img.rows :" << img.rows << endl;


    cout << "at (100, 50)" << endl;
    cout << "value B: " << B << endl;
    cout << "value G: " << G << endl;
    cout << "value R: " << R << endl;

    // waitKey(0);

    return 0;

}