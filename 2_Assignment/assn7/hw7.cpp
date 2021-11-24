#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

Mat drawHistogram(Mat src, int bin);

int main(){

    // Use ‘finger_print.png’, ‘adaptive_1.jpg’, and ‘adaptive.png’.
    // Read all images as gray scale images.
    Mat fingp = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/finger_print.png", 0);
    Mat adapt1 = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/adaptive_1.jpg", 0);
    Mat adapt = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/adaptive.png", 0);

    Mat fingp_result, adapt1_result, adapt_result;


    // Select and apply a threshold method for each image.
    // For ‘finger_print.png’, set finger print region to 0 and background region to 255.
    // Mat img_graph = drawHistogram(fingp, 256);
    // imshow("finger_print_histo", img_graph);

    threshold(fingp, fingp_result, 150, 255, THRESH_BINARY); // BEST


    // For ‘adatpve_1.jpg’, and ‘adaptive.png’, set character region to 0 and background region to 255.
    adaptiveThreshold(adapt1, adapt1_result, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 35,15);
    adaptiveThreshold(adapt, adapt_result, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 13,13);

    // imshow("origin", fingp);
    // imshow("adaptive_1 origin", adapt1);
    // imshow("adaptive origin", adapt);

    // Display results on three windows
    // Windows name: ‘finger_print ’, ‘adaptive_1’, and ‘adaptive’
    imshow("finger_print", fingp_result);
    imshow("adaptive_1", adapt1_result);
    imshow("adaptive", adapt_result);

    
    waitKey(0);

    return 0;
}

Mat drawHistogram(Mat src, int bin=-1){
    Mat hist, histimage;

    int i, hist_w, hist_h, bin_w, histSize;
    float range[] = {0 , 256};
    const float* histRange = {range};

    hist_w = 512;
    hist_h = 512;
    if (bin == -1) 
        histSize=hist_w;
    else histSize = bin;
    bin_w = cvRound((double)hist_w / histSize);

    histimage = Mat(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

    calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);

    normalize(hist, hist, 0, histimage.rows, NORM_MINMAX, -1, Mat());

    for ( i = 0; i < histSize; i++){
        rectangle(histimage, 
                    Point(bin_w * i, hist_h), 
                    Point(bin_w * i + hist_w/histSize, 
                    hist_h -cvRound(hist.at<float>(i))), 
                    Scalar(0,0,0), 
                    -1);
    }
    rectangle(histimage, Point(hist_w/2, hist_h), Point(hist_w/2, 0), Scalar(0,0,255), -1);

    return histimage;
}