#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    Mat frame;
    VideoCapture cap;

    // require 1,  Read a video “background.mp4”
    // check if file exists. if none program ends
    if( cap.open("background.mp4")==0){ 
        cout << "no such file!" << endl;
        waitKey(0);
    }
    double fps = cap.get(CAP_PROP_FPS);
    int total_frams = cap.get(CAP_PROP_FRAME_COUNT);

    int delay = int(1000/fps); //msec
    cout << "delay: "<< delay << endl;

    while (1) {
        cap >> frame;

        if( frame.empty()){
            cout << "end of video" << endl;
            break;
        }
        // require 4, Print out the number of the current frame and the total number of frames
        cout << "Frames: " <<cap.get(CAP_PROP_POS_FRAMES)   << "/" << total_frams << "  time_in_msec:  "  << cap.get(CAP_PROP_POS_MSEC) << endl;
        imshow("video", frame);
        waitKey(delay);   // require 3, Find out the proper input parameter for waitKey()

        if ( cap.get(CAP_PROP_POS_MSEC)>=3000) break;   // require 2, Display video for the first 3 seconds
    }
    
}