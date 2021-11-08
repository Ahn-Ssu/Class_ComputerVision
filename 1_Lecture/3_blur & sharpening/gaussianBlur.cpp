#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat image, avgImg, gaussianImg;
    image = imread("/Users/ahnssu/git/Class_ComputerVision/2_Assignment/assn3/src/Lena.png");

    // Blurs an image using the normalized box filter
    // image: input image, avgImg: output image, Size(5, 5): blurring kernel size
    blur(image, avgImg, Size(5, 5));

    // Blurs an image using a Gaussian filter
    // image: input image, GaussianImg: output image, Size(5, 5): Gaussian kernel Size
    // 1.5: Gaussian kernel standard deviation in X direction
    GaussianBlur(image, gaussianImg, Size(5,5), 1.5);

    imshow("image", image);
    imshow("avg", avgImg);
    imshow("gaussian",gaussianImg);
    waitKey(0);

    return 0;

}