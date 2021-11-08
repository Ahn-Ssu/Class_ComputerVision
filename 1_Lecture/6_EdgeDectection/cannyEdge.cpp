#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat imgae, canny;
    Mat image = imread("/Users/ahnssu/git/Class_ComputerVision/2_Assignment/assn1&2/src/Lena.png", 0);
    
    // performs canny edge detection
    // image: input Mat, canny: output Mat
    // 190: Thresh_low of double thresholding
    // 200: Thresh_high of double thresholding
    // 3: aperture size of the Sobel operation
    Canny(image, canny, 190, 200, 3);

    imshow("Input image", image);
    imshow("Canny Edge Detector", canny);

    waitKey(0);
    return 0;

}