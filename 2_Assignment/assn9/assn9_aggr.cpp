#include "cv.hpp"
#include <iostream>
#include <opencv2/dnn.hpp> /////// for using dnn
#include <fstream>

using namespace cv;
using namespace std;
using namespace dnn;

int main()
{
    // open the video
    VideoCapture cap("/Users/ahn_ssu/git/Class_ComputerVision/src/Faces.mp4");
    VideoCapture storm_cap("/Users/ahn_ssu/git/Class_ComputerVision/src/storm.mp4");
    Mat frame, storm_frame;

    // for face detection set up
    CascadeClassifier face_classifier;
    Mat grayframe_4_faceDection;
    vector<Rect> faces;
    face_classifier.load("/Users/ahn_ssu/git/Class_ComputerVision/src/haarcascade_frontalface_alt.xml");

    // for back ground subtraction (MoG2 model + yolov2 model)
    Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2();
    vector<String> classNamesVec;
    String modelConfiguration = "/Users/ahn_ssu/git/Class_ComputerVision/src/deep/fromSITE/yolov2.cfg";
    String modelBinary = "/Users/ahn_ssu/git/Class_ComputerVision/src/deep/fromSITE/yolov2.weights";
    ifstream classNamesFile("/Users/ahn_ssu/git/Class_ComputerVision/src/deep/coco.names");
    Net net = readNetFromDarknet(modelConfiguration, modelBinary);

    // validation check for yolo
    if (classNamesFile.is_open())
    {
        string className = "";
        while (std::getline(classNamesFile, className))
            classNamesVec.push_back(className);
    }

    // validation check for straming
    if (!cap.isOpened() || !storm_cap.isOpened())
    {
        cout << "Could not open video" << endl;
        return -1;
    }

    int user_input = 0;
    int B_key_flag = 0, F_key_flag = 0, G_key_flag = 0, I_key_flag = 0;
    while (true) // Video stream iteration
    {
        // get a new frame from webcam
        cap >> frame;
        storm_cap >> storm_frame; // gif라서 프레임수는 같은데 바뀌는게 5배 차이남
        storm_cap >> storm_frame;
        storm_cap >> storm_frame;
        storm_cap >> storm_frame;
        storm_cap >> storm_frame;
        storm_cap >> storm_frame;

        cout << "now input (f,g,b,i): " << F_key_flag << G_key_flag << B_key_flag << I_key_flag << endl;

        if (frame.empty())
            break;

        // resize to 1/2, 3/4
        // origin video size 720 x 1280
        // resize(frame, frame, Size(640, 360));
        // resize(frame, frame, Size(960, 480));

        if (frame.channels() == 4)
            cvtColor(frame, frame, COLOR_BGRA2BGR);

        // use face detection when input key f || g
        // g = grap cut mode, i = inrange mode
        if (F_key_flag || G_key_flag || I_key_flag)
        {
            cvtColor(frame, grayframe_4_faceDection, COLOR_BGR2GRAY); // convert captured frame to gray scale
            face_classifier.detectMultiScale(
                grayframe_4_faceDection,
                faces,
                1.1,         // increase search scale by 10%  each pass
                8,           // merge groups of 3 detections
                0,           // not used for a new cascade
                Size(10, 10) // min size
            );

            // for input key f
            // calc nearest, farthest
            if (F_key_flag)
            {
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

                // for f input
                Mat faceDetection; // -> frame으로 사용 가능
                frame.copyTo(faceDetection);

                for (int i = 0; i < faces.size(); i++)
                {
                    Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
                    Point tr(faces[i].x, faces[i].y);

                    if (i == nearest_idx)
                        rectangle(faceDetection, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
                    else if (i == farthest_idx)
                        rectangle(faceDetection, lb, tr, Scalar(255, 0, 0), 3, 4, 0);
                    else
                    {
                        rectangle(faceDetection, lb, tr, Scalar(0, 235, 255), 3, 4, 0);
                    }
                }
                imshow("stream", faceDetection);
            } // end of F condition
            else if (G_key_flag || I_key_flag)
            {
                // Mat fgMask, fgImg;
                Mat face_mask, face_area;
                Mat grab_result, bgModel, fgModel;

                face_mask = Mat(frame.size(), CV_8UC1, Scalar(0, 0, 0));
                // draw the results
                for (int i = 0; i < faces.size(); i++)
                {

                    Point zoom_lb(faces[i].x + (int)(faces[i].width * 1.1), faces[i].y + (int)(faces[i].height * 1.1));
                    Point zoom_tr(faces[i].x - (int)(faces[i].width * 0.1), faces[i].y - (int)(faces[i].height * 0.1));

                    if (G_key_flag)
                    { // ** 그랩 컷 사용 코드 - 매우느림!!
                        grabCut(frame, grab_result, Rect(zoom_lb, zoom_tr), bgModel, fgModel, 2, GC_INIT_WITH_RECT);
                        compare(grab_result, GC_PR_FGD, grab_result, CMP_EQ);
                        face_mask += grab_result;
                    }
                    else if (I_key_flag)
                    {
                        // ** in range 사용 코드 사각형 마스크 따기
                        rectangle(face_mask, Rect(zoom_lb, zoom_tr), Scalar(255), -1, 8, 0);
                    }
                }

                if (G_key_flag)
                { // ** 그랩 컷 사용 코드
                    // cvtColor(face_mask, face_mask, CV_GRAY2BGR);
                    frame.copyTo(face_area, face_mask);
                    resize(storm_frame, storm_frame, Size(frame.cols, frame.rows));
                    face_mask = 255 - face_mask;
                    Mat for_bg;
                    storm_frame.copyTo(for_bg, face_mask);
                    for_bg += face_area;
                    imshow("stream", for_bg);
                }
                else if (I_key_flag)
                {

                    // inRange를 써봅시다
                    // 1) 마스크에 의해서 이미지를 먼저 추출
                    frame.copyTo(face_area, face_mask);

                    // 2) 추출한 이미지 YcrCb로 변환하고, 피부색 필터 적용해서 inRanged_mask 겟
                    Mat inRanged_mask, inRanged_img;
                    cvtColor(face_area, face_area, CV_BGR2YCrCb);
                    inRange(face_area, Scalar(20, 133, 77), Scalar(220, 173, 127), inRanged_mask);

                    // added 
                    Mat kernel_shape = getStructuringElement(MORPH_ELLIPSE, Size(10, 10));
                    morphologyEx(inRanged_mask, inRanged_mask, MORPH_CLOSE, kernel_shape);

                    // 3) 얻어낸 살색 마스크로 인물 따내고 YCrCb -> BGR
                    frame.copyTo(inRanged_img, inRanged_mask);

                    // 새로운 배경;
                    Mat for_bg;
                    resize(storm_frame, storm_frame, Size(frame.cols, frame.rows));
                    inRanged_mask = 255 - inRanged_mask;
                    storm_frame.copyTo(for_bg, inRanged_mask);

                    // 배경사진 짠
                    for_bg += inRanged_img;
                    imshow("stream", for_bg);
                }
            } // end of G || Icondition
        }     // end of f||g ||i condition
        else if (B_key_flag)
        {
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
                size_t objectClass = max_element(prob_array_ptr, prob_array_ptr + probability_size)
                                                         - prob_array_ptr;

                if (objectClass != 0) continue; // only for person

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

            { //  average를 사용 성능 안좋아서 버림
                // Mat detected_area;
                // frame.copyTo(detected_area, detect_mask);

                // cvtColor(detected_area,detected_area, CV_BGR2GRAY);
                // subtract(mean_bg, detected_area, detected_area, detect_mask);
                // threshold(detected_area, detect_mask, 25, 255, CV_THRESH_BINARY);

                // morphologyEx(detect_mask, detect_mask, MORPH_CLOSE, kernel_shape);
                // Mat kernel_shape = getStructuringElement(MORPH_ELLIPSE, Size(9,9));
                // morphologyEx(detect_mask, detect_mask, MORPH_CLOSE, kernel_shape);
                // morphologyEx(detect_mask, detect_mask, MORPH_CLOSE, kernel_shape);
                // // imshow("Detected mask af", detect_mask);

                // frame.copyTo(detected_area, detect_mask);
                // imshow("stream", detected_area);

                // imshow("Detected frame", mask_frame);
                // imshow("stream", frame);
            }

            // MOG를 사용
            Mat mog_mask;
            bg_model->apply(frame, mog_mask);
            GaussianBlur(mog_mask, mog_mask, Size(13, 13), 3.5, 3.5);
            threshold(mog_mask, mog_mask, 25, 255, THRESH_BINARY);
            Mat mog_fg;
            mog_fg = Scalar::all(0);
            Mat kernel_shape = getStructuringElement(MORPH_ELLIPSE, Size(75, 150));
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

            putText(detected_area, format("There are %d people.", person_count),
                     Point(50, 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4, CV_AA);

            imshow("stream", detected_area);
        } // end of B condition
        else if (!(F_key_flag && G_key_flag && B_key_flag && I_key_flag))
        {
            imshow("stream", frame);
        }

        user_input = waitKey(33);

        if (user_input == 27) break; // ESC; escape
        else if (user_input == 66 || user_input == 98) B_key_flag > 0 ? B_key_flag = 0 : B_key_flag = 1;
        else if (user_input == 70 || user_input == 102) F_key_flag > 0 ? F_key_flag = 0 : F_key_flag = 1;
        else if (user_input == 71 || user_input == 103) G_key_flag > 0 ? G_key_flag = 0 : G_key_flag = 1;
        else if (user_input == 81 || user_input == 105) I_key_flag > 0 ? I_key_flag = 0 : I_key_flag = 1;
    }
    return 0;
}