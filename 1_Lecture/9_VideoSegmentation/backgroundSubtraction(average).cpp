#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    VideoCapture capture("/Users/ahn_ssu/git/Class_ComputerVision/src/Faces.mp4");
    Mat image, sum, avg;
    int cnt = 2;

    capture >> avg;

    while(true){

        if(!capture.read(image)) break;

        add(image / cnt, avg*(cnt - 1)/cnt, avg);

        // imshow("avg", avg);
        cnt++;
    }

            // GaussianBlur(avg, avg, Size(9, 9), 3.5, 3.5);
            // medianBlur(avg, avg, 9);
            blur(avg, avg, Size(9,9));
        VideoCapture capture1("/Users/ahn_ssu/git/Class_ComputerVision/src/Faces.mp4");
        Mat background, frame, gray, result, foregroundMask, foregroundImg;


        // capture >> background;
        cvtColor(avg, avg, CV_BGR2GRAY);


        while(true){
            if(capture1.grab() == 0 ) break;

            capture1.retrieve(frame);
            cvtColor(frame, gray, CV_BGR2GRAY);

            absdiff(avg, gray, foregroundMask);
            
            // GaussianBlur(foregroundMask, foregroundMask, Size(9, 9), 3.5, 3.5);
            threshold(foregroundMask, foregroundMask, 25, 255, CV_THRESH_BINARY);
            // adaptiveThreshold(foregroundMask, foregroundMask, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 7, 40);
            morphologyEx(foregroundMask,foregroundMask, MORPH_CLOSE, 10);
            foregroundMask.copyTo(foregroundImg);
            // cout << "Channels :" << foregroundMask.channels() << endl;
            gray.copyTo(foregroundImg, foregroundMask);

            imshow("foregroundImg", foregroundImg);
            imshow("foregroundMask", foregroundMask);
            // imshow("background", avg);

            waitKey(33);
        }
        // 이거 잘 디벨롭 시켜서 forgroung Img에서 마스크 따로 줘가지고 쟤네만 따버리는거 해보기
    return 0;

}