#include "cv.hpp"
#include <iostream>
#include <opencv2/dnn.hpp> /////// for using dnn
#include <fstream>

using namespace cv;
using namespace std;
using namespace dnn;

int main(int argc, char** argv){
    String modelConfiguration = "/Users/ahn_ssu/git/Class_ComputerVision/src/deep/fromSITE/yolov2.cfg";
    String modelBinary = "/Users/ahn_ssu/git/Class_ComputerVision/src/deep/fromSITE/yolov2.weights";

    Net net = readNetFromDarknet(modelConfiguration, modelBinary);

    VideoCapture cap("/Users/ahn_ssu/git/Class_ComputerVision/src/Quiz2 Video.mp4");

    vector <String> classNamesVec;
    ifstream classNamesFile("/Users/ahn_ssu/git/Class_ComputerVision/src/deep/coco.names");

    if(classNamesFile.is_open()){
        string className = "";
        while(std::getline(classNamesFile, className)) classNamesVec.push_back(className);
    }

    while (1){
        Mat frame;
        cap >> frame; // get a net frame from camera/vidoe or read image

        if ( frame.empty()){
            waitKey();
            break;
        }

        if( frame.channels()==4) cvtColor(frame, frame, COLOR_BGRA2BGR);

        // Convert Mat to batch of images
        
        Mat inputBlob = blobFromImage(frame, 1 / 255.F, Size(800, 800), Scalar(), true, false);
        net.setInput(inputBlob, "data");
        Mat detectionMat = net.forward("detection_out");

        float confidenceThreshold = 0.12; // by default
        int count_person = 0;
        int count_ball = 0;
        for (int i= 0 ; i< detectionMat.rows; i++){
            const int probability_index = 5;
            const int probability_size = detectionMat.cols - probability_index;
            float *prob_array_ptr = &detectionMat.at<float>(i, probability_index);
            size_t objectClass = max_element(prob_array_ptr, prob_array_ptr + probability_size) - prob_array_ptr;
            // obejct class { 0:person, 32:sport ball}

            if (objectClass == 32) count_ball++;

            // prediction probability of each class
            float confidence = detectionMat.at<float>(i, (int)objectClass + probability_index);

            // for drawing labels with name and confidence
            if ( confidence > confidenceThreshold) {
                if (objectClass == 0) count_person ++;

                float x_center = detectionMat.at<float>(i, 0) * frame.cols;
                float y_center = detectionMat.at<float>(i, 1) * frame.rows;
                float width = detectionMat.at<float>(i, 2) * frame.cols;
                float height = detectionMat.at<float>(i, 3) * frame.rows;

                Point p1(cvRound(x_center - width/2), cvRound(y_center - height/2));
                Point p2(cvRound(x_center + width/2), cvRound(y_center + height/2));
                Rect object(p1, p2);
                Scalar object_roi_color(0, 255, 0);

                rectangle(frame, object, object_roi_color);
            }

        }
        putText(frame, format("# of person = %d", count_person), Point(50,30), FONT_HERSHEY_SIMPLEX, 1, Scalar(98, 128, 0), 2, CV_AA);
        putText(frame, format("# of ball   = %d", count_ball), Point(50,70), FONT_HERSHEY_SIMPLEX, 1, Scalar(98, 128, 0), 2, CV_AA);
        imshow("YOLO: Detections", frame);
        if( waitKey(1) >= 0) break;
    }
    return 0;

}