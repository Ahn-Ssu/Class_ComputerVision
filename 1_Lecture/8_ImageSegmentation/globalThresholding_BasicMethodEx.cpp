#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){

    Mat image, thresh;
    int thresh_T, low_cnt, high_cnt, low_sum, high_sum; 
    int i, j, th;

    thresh_T = 200;
    th = 10; // 초기의 T 값 수렴 판단 범위 값 
    low_cnt = high_cnt = low_sum = high_sum = 0 ; 

    image = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/Lena.png", 0);
    cout << "threshold value:" << thresh_T << endl;

    while(1){

        for ( j = 0 ; j< image.rows ; j++){
            for ( i = 0 ;  i <image.cols; i++){

                if(image.at<uchar>(j, i) < thresh_T) {
                    low_sum += image.at<uchar> (j, i);
                    low_cnt ++;
                }
                else{
                    high_sum += image.at<uchar>(j, i);
                    high_cnt++;
                }
            }
        }

        if ( abs(thresh_T - (low_sum / low_cnt + high_sum / high_cnt) /2.0f) < th) break;
        else {
            thresh_T = (low_sum / low_cnt + high_sum / high_cnt) / 2.0f;
            cout << "threshold value: " << thresh_T << endl;
            low_cnt = high_cnt = low_sum = high_sum = 0;
        }
    }

    threshold(image, thresh, thresh_T, 255, THRESH_BINARY);

    imshow("input image", image);
    imshow("thresholding", thresh);
    waitKey(0);
    return 0;

}