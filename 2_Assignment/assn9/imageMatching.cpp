#include "cv.hpp"
#include <iostream>
#include <opencv2/dnn.hpp> /////// for using dnn
#include <fstream>

using namespace cv;
using namespace std;
using namespace dnn;

int main(int argc, char **argv)
{
    VideoCapture cap("/Users/ahn_ssu/git/Class_ComputerVision/src/Faces.mp4");

    Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2();

    vector<String> classNamesVec;
    String modelConfiguration = "/Users/ahn_ssu/git/Class_ComputerVision/src/deep/fromSITE/yolov2.cfg";
    String modelBinary = "/Users/ahn_ssu/git/Class_ComputerVision/src/deep/fromSITE/yolov2.weights";
    ifstream classNamesFile("/Users/ahn_ssu/git/Class_ComputerVision/src/deep/coco.names");
    Net net = readNetFromDarknet(modelConfiguration, modelBinary);

    if (classNamesFile.is_open())
    {
        string className = "";
        while (std::getline(classNamesFile, className))
            classNamesVec.push_back(className);
    }

    {   // ** for avg ** back 
        // VideoCapture for_get_background("/Users/ahn_ssu/git/Class_ComputerVision/src/Faces.mp4");
        // Mat image, sum, mean_bg;
        // int cnt = 2;

        // for_get_background >> mean_bg;

        // while(true){

        //     if(!for_get_background.read(image)) break;

        //     add(image / cnt, mean_bg*(cnt - 1)/cnt, mean_bg);

        //     // imshow("avg", avg);
        //     cnt++;
        // }
        // GaussianBlur(mean_bg, mean_bg, Size(5,5), 3.5, 3.5);
        // cvtColor(mean_bg,mean_bg, CV_BGR2GRAY);
    }
     
    while (1) // Video stream iteration
    {
        Mat frame;
        cap >> frame; 

        if (frame.empty())
        {
            waitKey();
            break;
        }

        if (frame.channels() == 4)
            cvtColor(frame, frame, COLOR_BGRA2BGR);


        Mat inputBlob = blobFromImage(frame, 1 / 255.F, Size(412, 412), Scalar(), true, false);
        net.setInput(inputBlob, "data");
        Mat detectionMat = net.forward("detection_out");

        float confidenceThreshold = 0.12; // by default
        int person_count = 0;
        Mat detect_mask = Mat(frame.size(), CV_8UC1, Scalar(0, 0, 0));
        for (int i = 0; i < detectionMat.rows; i++)
        {
            const int probability_index = 5;
            const int probability_size = detectionMat.cols - probability_index;
            float *prob_array_ptr = &detectionMat.at<float>(i, probability_index);
            size_t objectClass = max_element(prob_array_ptr, prob_array_ptr + probability_size) - prob_array_ptr;

            if (objectClass != 0)
                continue; // only for person

            // prediction probability of each class
            float confidence = detectionMat.at<float>(i, (int)objectClass + probability_index);

            // for drawing labels with name and confidence
            if (confidence > confidenceThreshold)
            {
                float x_center = detectionMat.at<float>(i, 0) * frame.cols;
                float y_center = detectionMat.at<float>(i, 1) * frame.rows;
                float width = detectionMat.at<float>(i, 2) * frame.cols;
                float height = detectionMat.at<float>(i, 3) * frame.rows;

                Point p1(cvRound(x_center - width / 2), cvRound(y_center - height / 2));
                Point p2(cvRound(x_center + width / 2), cvRound(y_center + height / 2));

                rectangle(detect_mask, Rect(p1, p2), Scalar(255), -1, 8, 0);
                person_count++;
            }
        } // end of for state

        
        {   //  average를 사용
        // Mat detected_area;   
        // frame.copyTo(detected_area, detect_mask);

        // cvtColor(detected_area,detected_area, CV_BGR2GRAY);
        // subtract(mean_bg, detected_area, detected_area, detect_mask);
        // threshold(detected_area, detect_mask, 25, 255, CV_THRESH_BINARY);

        // morphologyEx(detect_mask, detect_mask, MORPH_CLOSE, kernel_shape);
        // Mat kernel_shape = getStructuringElement(MORPH_ELLIPSE, Size(9,9));
        // morphologyEx(detect_mask, detect_mask, MORPH_CLOSE, kernel_shape);
        // morphologyEx(detect_mask, detect_mask, MORPH_CLOSE, kernel_shape);
        // imshow("Detected mask af", detect_mask);

        // frame.copyTo(detected_area, detect_mask);
        // imshow("Detected area af", detected_area);

        // imshow("Detected frame", mask_frame);
        // imshow("YOLO: Detections", frame);
        }
        
        // MOG를 사용
        Mat mog_mask;
        bg_model->apply(frame, mog_mask);
        GaussianBlur(mog_mask, mog_mask, Size(13, 13), 3.5, 3.5);
        threshold(mog_mask, mog_mask, 20, 255, THRESH_BINARY);
        Mat mog_fg;
        mog_fg = Scalar::all(0);
        Mat kernel_shape = getStructuringElement(MORPH_ELLIPSE, Size(75, 75));
        morphologyEx(mog_mask, mog_mask, MORPH_CLOSE, kernel_shape);
        morphologyEx(mog_mask, mog_mask, MORPH_CLOSE, kernel_shape);
        morphologyEx(mog_mask, mog_mask, MORPH_CLOSE, kernel_shape);
        morphologyEx(mog_mask, mog_mask, MORPH_CLOSE, kernel_shape);
        morphologyEx(mog_mask, mog_mask, MORPH_CLOSE, kernel_shape);
        morphologyEx(mog_mask, mog_mask, MORPH_CLOSE, kernel_shape);
        morphologyEx(mog_mask, mog_mask, MORPH_CLOSE, kernel_shape);
        morphologyEx(mog_mask, mog_mask, MORPH_CLOSE, kernel_shape);
        morphologyEx(mog_mask, mog_mask, MORPH_CLOSE, kernel_shape);

        Mat detected_area;
        frame.copyTo(mog_fg, mog_mask);
        mog_fg.copyTo(detected_area, detect_mask);

        
        putText(detected_area, format("There are %d peopel.", person_count), Point(50,80), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4, CV_AA);

        imshow("mog fg image", detected_area);

        
        if (waitKey(1) >= 0)
            break;
    }
    return 0;
}