#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int main(){
    Mat image,hist_equalized_image;

    image = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/exam1.png", 0);
    if ( !image.data) exit(1); //Check image

    Vec3b
    
    // Perform histogram equalization on the input image
    equalizeHist(image, hist_equalized_image);

    imshow("before", image);
    imshow("after histoEq", hist_equalized_image);


    uchar * pixel;
    for (int j = 0 ; j < image.rows ; j ++){
        pixel = image.ptr<uchar>(j);
        
        for (int i = 0; i < image.cols;i++){
            if(pixel[i] > 250) ;
            else pixel[i] = 1; 
        }
    }

    imshow("after intensity change", image);

    waitKey(0);
    return 0;

}
