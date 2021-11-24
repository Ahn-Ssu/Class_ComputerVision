#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture capture("/Users/ahn_ssu/git/Class_ComputerVision/src/background.mp4");
    Mat background, image, gray, foregroundMask, foregroundImg;
    Mat sum; 
    int cnt=2;
    
    capture >> background;
    while(true){ // if
        if(!capture.read(image)) break;

        add(image/cnt, background*(cnt-1)/cnt, background);
        cnt++;

        if (cnt == 12) break; // for only first 10 frames
    }
    cvtColor(background, background, CV_BGR2GRAY);

    while (true)
    {
        if (capture.grab() == 0)
            break;

        capture.retrieve(image);
        cvtColor(image, gray, CV_BGR2GRAY);

        absdiff(background, gray, foregroundMask);
        GaussianBlur(foregroundMask, foregroundMask, Size(11, 11), 3.5, 3.5);
        threshold(foregroundMask, foregroundMask, 20, 255, CV_THRESH_BINARY);
        foregroundMask.copyTo(foregroundImg);
        gray.copyTo(foregroundImg, foregroundMask);


        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        int obj_count = 0 ;

        findContours(foregroundMask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

        vector<Rect> boundRect(contours.size());
        for (int i = 0; i < contours.size(); i++)
            boundRect[i] = boundingRect(Mat(contours[i])); //draw rectangles on the contours
    
        for (int i = 0; i < contours.size(); i++)
            if ( boundRect[i].area() > 400){
                rectangle(gray, boundRect[i].tl(), boundRect[i].br(), Scalar(255, 255, 255), 2, 8, 0);
                obj_count ++;
            }
        putText(gray, 
                format("the number of moving object: %d", obj_count),
                Point(50,30), 
                FONT_HERSHEY_SIMPLEX, 
                0.7, 
                Scalar(255, 255, 255), 
                2,
                CV_AA);



        imshow("Back ground image", background);
        imshow("Result(x,y) - foregroundMask", foregroundMask);
        imshow("final result video", gray);

        waitKey(33);
    }
    return 0;
}