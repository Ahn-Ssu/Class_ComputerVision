#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(){

    Mat image, laplacian, abs_laplacian, sharpen;
    image = imread("/Users/ahnssu/git/Class_ComputerVision/2_Assignment/assn3/src/moon.png");

    GaussianBlur(image, image, Size(3, 3), 0, 0, BORDER_DEFAULT);

    // calculates the Laplacian of an image
    // image: src, laplacian: dst, CV_16S: desire depth of dst
    // 1 : aperture size used to compute second-derivative (optional)
    // 1 : optional scale factor for the computed Laplacian values
    // 0 : optional delta value that is added to the result
    Laplacian(image, laplacian, CV_16S, 1, 1, 0);
    convertScaleAbs(laplacian, abs_laplacian);
    sharpen = abs_laplacian + image;


    imshow("image", image);
    imshow("Laplacian (CV_16S)", laplacian);
    imshow("abs_laplacian", abs_laplacian);
    imshow("sharpen", sharpen);
    
    cout << laplacian << endl; // for monitor
    waitKey(0);

    return 0;

}