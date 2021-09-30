#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

void white_balacing(Mat img){
    Mat bgr_channels[3];
    split(img, bgr_channels);


    double avg;
    int sum, temp, i, j, c;


    for(c=0;c<img.channels(); c++){
        sum = 0 ;
        avg = 0.0f;
        for(i=0; i<img.rows; i++){
            for( j = 0 ; j < img.cols ; j++){
                sum += bgr_channels[c].at<uchar>(i,j);
            }
        }

        avg = sum / (img.rows * img.cols);
        for(i=0; i<img.rows; i++){
            for( j = 0 ; j < img.cols ; j++){
                temp = (128/avg) * bgr_channels[c].at<uchar>(i,j);

                if(temp>255) bgr_channels[c].at<uchar>(i,j) = 255;
                else bgr_channels[c].at<uchar>(i,j) = temp;
            }
        }

    }

    merge(bgr_channels,3,img);
}

int main(){
    Mat balancing = imread("/Users/ahnssu/git/Class_ComputerVision/2_Assignment/assn1&2/src/Lena.png", 1);
    Mat result;

    result = balancing.clone();
    white_balacing(result);



    imshow("Input image", balancing);
    imshow("result image", result);

    waitKey(0);
    return 0;

}