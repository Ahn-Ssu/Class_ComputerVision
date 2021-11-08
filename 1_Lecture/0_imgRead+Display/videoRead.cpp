#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat frame;
    VideoCapture cap;

    // check if file exists. if none program ends

    if( cap.open("/Users/ahnssu/git/Class_ComputerVision/2_Assignment/assn1/background.mp4")==0){
        cout << "no such file!" << endl;
        waitKey(0);
    }

    double fps = cap.get(CAP_PROP_FPS);
    double time_in_msec = cap.get(CAP_PROP_POS_MSEC);
    int total_frams = cap.get(CAP_PROP_FRAME_COUNT);
    

    cout << "fps: "<< fps << endl;              // fps: 24
    cout << "msec: "<< fps << endl;             // msec: 24
    cout << "total frame: "<< fps << endl;      // total frame: 24

}