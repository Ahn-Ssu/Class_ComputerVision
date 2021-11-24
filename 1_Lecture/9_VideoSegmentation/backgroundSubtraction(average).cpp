#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    VideoCapture capture("/Users/ahn_ssu/git/Class_ComputerVision/src/background.mp4");
    Mat image, sum, avg;
    int cnt = 2;

    capture >> avg;

    while(true){

        if(!capture.read(image)) break;

        add(image / cnt, avg*(cnt - 1)/cnt, avg);

        imshow("avg", avg);
        cnt++;
        waitKey(33);
    }
    return 0;

}