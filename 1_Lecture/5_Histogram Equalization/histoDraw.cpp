#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

Mat drawHistogram(Mat src){
    Mat hist, histimage;

    int i, hist_w, hist_h, bin_w, histSize;
    float range[] = {0 , 256};
    const float* histRange = {range};

    hist_w = 512;
    hist_h = 400;
    histSize = 256;
    bin_w = cvRound((double)hist_w / histSize);

    histimage = Mat(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

    calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);

    normalize(hist, hist, 0, histimage.rows, NORM_MINMAX, -1, Mat());

    for ( i = 0; i < histSize; i++){
        rectangle(histimage, Point(bin_w * i, hist_h), Point(bin_w * i + hist_w/histSize, hist_h -cvRound(hist.at<float>(i))), Scalar(0,0,0), -1);
    }

    return histimage;


}

int main(){
    Mat image;
    Mat hist_equalized_image;
    Mat hist_graph;
    Mat hist_equalized_graph;

    image = imread("/Users/ahnssu/git/Class_ComputerVision/Lena.png", 0);
    if ( !image.data) exit(1); //Check image
    
    equalizeHist(image, hist_equalized_image);

    hist_graph = drawHistogram(image);
    hist_equalized_graph = drawHistogram(hist_equalized_image);

    imshow("Input image", image);
    imshow("Graph Input image", hist_graph);
    imshow("Hist equalized image", hist_equalized_image);
    imshow("Graph Hist equalized image", hist_equalized_graph);

    waitKey(0);
    return 0;

}

