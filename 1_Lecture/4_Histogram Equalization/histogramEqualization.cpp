#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat image;
    Mat hist_equalized_image;

    image = imread("/Users/ahnssu/git/Class_ComputerVision/Lena.png", 0);
    if ( !image.data) exit(1); //Check image
    
    equalizeHist(image, hist_equalized_image);

    imshow("Input image", image);
    imshow("Hist equalized image", hist_equalized_image);



    waitKey(0);
    return 0;

}