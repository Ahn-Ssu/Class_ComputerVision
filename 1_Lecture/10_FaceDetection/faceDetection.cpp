#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    CascadeClassifier face_classifier;
    Mat frame, grayframe;
    vector<Rect> faces;
    int i;

    // open the webcam
    VideoCapture cap("/Users/ahn_ssu/git/Class_ComputerVision/src/Faces.mp4");

    // valid check
    if (!cap.isOpened())
    {
        cout << "Could not open camera" << endl;
        return -1;
    }

    // face detection configuration
    face_classifier.load("/Users/ahn_ssu/git/Class_ComputerVision/src/haarcascade_frontalface_alt.xml");

    while (true)
    {
        // get a new frame from webcam
        cap >> frame;

        // convert captured frame to gray scale
        cvtColor(frame, grayframe, COLOR_BGR2GRAY);

        face_classifier.detectMultiScale(
            grayframe,
            faces,
            1.1,         // increase search scale by 10%  each pass
            8,           // merge groups of 3 detections
            0,           // not used for a new cascade
            Size(30, 30) // min size
        );

        // calc nearest, farthest
        int nearest_size = 0, farthest_size = 0;
        int nearest_idx = 0, farthest_idx = 0;
        if (faces.size())
        {
            nearest_size = farthest_size = faces[0].width * faces[0].height;
            for (int iter = 1; iter < faces.size(); iter++)
            {
                if (nearest_size < faces[iter].width * faces[iter].height)
                {
                    nearest_size = faces[iter].width * faces[iter].height;
                    nearest_idx = iter;
                }

                if (farthest_size > faces[iter].width * faces[iter].height)
                {
                    farthest_size = faces[iter].width * faces[iter].height;
                    farthest_idx = iter;
                }
            }
        }

        // draw the results
        for (i = 0; i < faces.size(); i++)
        {
            Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
            Point tr(faces[i].x, faces[i].y);

            if (i == nearest_idx)
                rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
            else if (i == farthest_idx)
                rectangle(frame, lb, tr, Scalar(255, 0, 0), 3, 4, 0);
            else
            {
                rectangle(frame, lb, tr, Scalar(0, 235, 255), 3, 4, 0);
            }
        }

        // print the ouput
        imshow("Face Detection", frame);
        if (waitKey(33) == 27)
            break;
    }
    return 0;
}