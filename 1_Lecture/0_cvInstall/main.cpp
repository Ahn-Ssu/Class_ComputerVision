#include <opencv2/opencv.hpp> 
#include <iostream>


using namespace std;
using namespace cv;
int main()
{
    Mat image;
    image = imread("배리어프리_지도(국문).png", IMREAD_COLOR);
    if (image.empty())
    {
        cout << "Could not open or find the image" << endl;
        return -1;
    }
    namedWindow("Original", WINDOW_AUTOSIZE);
    imshow("Original", image);
    waitKey(0);
}