#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat histNorm(Mat src, int bin);
Mat drawHistogram(Mat src, int bin);

int main(){
    Mat image,hist_equalized_image;
    Mat img_graph, hist_graph, hist_graph8;

    // Read an image "moon.png" as gray scale image
    image = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/exam1.png", 0);
    if ( !image.data) exit(1); //Check image
    
    // Perform histogram equalization on the input image
    equalizeHist(image, hist_equalized_image);

    // Display each image with the window name as “before”, “after”
    imshow("before", image);
    imshow("after", hist_equalized_image);

    // Display each histogram of the input and the result image
    // Set the number of bins to 16
    img_graph = drawHistogram(image, 16);
    hist_graph = drawHistogram(hist_equalized_image, 16);

    // Display each image with the window name as “h1”, “h2”
    imshow("h1", img_graph);
    imshow("h2", hist_graph);

    // Compute the value of each component of a normalized histogram of the input image;
    // write all values on the input image; and display the result
    hist_graph8 = histNorm(image, 8);

    for(int iter=0; iter < 8 ; iter++)
        putText(image, 
                format("bin %d : %f",iter, hist_graph8.at<float>(iter)), 
                Point(50,80 + 30*iter), 
                FONT_HERSHEY_SIMPLEX, 
                0.5, 
                Scalar(1, 1, 1), 
                1,
                CV_AA);

    imshow("c val", image);



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

    return histimage;
}

Mat histNorm(Mat src, int bin=-1){
    Mat hist, histimage;

    int i, hist_w, hist_h, bin_w, histSize;
    float range[] = {0 , 256};
    const float* histRange = {range};

    hist_w = 512;
    hist_h = 512;
    if (bin == -1) 
        histSize=256;
    else histSize = bin;
    bin_w = cvRound((double)hist_w / histSize);

    histimage = Mat(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

    calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);

    normalize(hist, hist, 0, histimage.rows, NORM_MINMAX, -1, Mat());

    return hist;
}