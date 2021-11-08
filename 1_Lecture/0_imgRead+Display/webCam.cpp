#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat frame;
    VideoCapture cap(0);

   

    double fps = cap.get(CAP_PROP_FPS);
    double time_in_msec = cap.get(CAP_PROP_POS_MSEC);
    int total_frams = cap.get(CAP_PROP_FRAME_COUNT);
    

    cout << "fps: "<< fps << endl;              // fps: 12
    cout << "msec: "<< fps << endl;             // msec: 12
    cout << "total frame: "<< fps << endl;      // total frame: 12


    while (1) {
        cap >> frame;

        if( frame.empty()){
            cout << "end of video" << endl;
            break;
        }
        imshow("video", frame);
        waitKey(33);
    }
}