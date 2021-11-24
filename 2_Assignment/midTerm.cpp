#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define L UINT8_MAX

// for common
Mat resetImage(Mat src, Mat origin); // r key [114]

// for Lena img
Mat negativeTransform(Mat src); // n key [110]
Mat grammaTransform(Mat src);   // g key [103]
Mat HistogramEqualization(Mat src);   // h key [104]

// for colorful image
Mat sliceColor(Mat src); // s key [115]
Mat conversionColor(Mat src); // c key [99]

// for balancing image
Mat averageFiltering(Mat src); // a key [97]
void whiteBalancing(Mat src); // w key [119]

int main(){
    Mat lena, display_lena;
    Mat colorful, display_colorful;
    Mat balancing, display_balancing;

    lena = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/Lena.png");
    display_lena = lena.clone();

    colorful = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/colorful.jpg");
    display_colorful = colorful.clone();

    balancing = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/balancing.jpg");
    display_balancing = balancing.clone();
    

    int recive = 0 ;

    while(1){
        

        if (recive == 27){cout << "ESC enter "<<recive << endl; break;}

        if (recive == 114){ cout << "r enter "<<recive << endl;
        display_lena      = resetImage(display_lena, lena);
        display_colorful  = resetImage(display_colorful, colorful);
        display_balancing = resetImage(display_balancing, balancing);
        }

        if (recive == 110){ // cout << "n enter "<<recive << endl;
        display_lena = negativeTransform(display_lena);
        }

        if (recive == 103){ //cout << "g enter "<<recive << endl;
        display_lena = grammaTransform(display_lena);
        }
        
        if (recive == 104){ //cout << "h enter "<<recive << endl;        
        display_lena = HistogramEqualization(display_lena);
        }

        if (recive == 115){// cout << "s enter "<<recive << endl;
        display_colorful = sliceColor(display_colorful);
        }

        if (recive == 99){// cout << "c enter "<<recive << endl;
        display_colorful = conversionColor(display_colorful);
        }

        if (recive == 97){ //cout << "a enter "<<recive << endl;
        display_balancing = averageFiltering(display_balancing);
        }

        if (recive == 119){//cout << "w enter "<<recive << endl;
        whiteBalancing(display_balancing);
        }


        imshow("lena", display_lena);
        imshow("colorful", display_colorful);
        imshow("balancing", display_balancing);

        recive = waitKey(0);
    }
    return 0;

}

Mat resetImage(Mat src, Mat origin){ // r key [114]
    src = origin.clone();
    return src;
}

Mat negativeTransform(Mat src){
    // https://www.geeksforgeeks.org/negative-transformation-of-an-image-using-python-and-opencv/
    // https://www.codespeedy.com/negative-transformation-of-an-image-using-pil/
    // https://dyclassroom.com/image-processing-project/how-to-convert-a-color-image-into-negative 
    Mat negative_img = src.clone();

    negative_img.setTo(L-1);
    subtract(negative_img, src, src);

    return src;
    // Mat cvt = src.clone();
    // vector<Mat> HSV(3);

    // uchar * v;

    // cvtColor(cvt, cvt, CV_BGR2HSV);
    // split(cvt, HSV);

    // for (int j = 0 ; j < cvt.rows ; j ++){
    //     v = HSV[2].ptr<uchar>(j);
    //     for (int i = 0; i < cvt.cols;i++){
    //         v[i] = 255 - v[i];
    //     }
    // }

    // merge(HSV, cvt);
    // cvtColor(cvt, cvt, CV_HSV2BGR);

    // return cvt;
}



Mat grammaTransform(Mat src){

    float constant = 1.0f;
    float gamma = 2.5f;

    src.convertTo(src, CV_32F);
    normalize(src, src, 0, 1.0f, NORM_MINMAX);
    pow(src, gamma, src);
    normalize(src, src, 0, L, NORM_MINMAX);
    convertScaleAbs(src, src, constant);
    src.convertTo(src, CV_8UC1);
    return src;
}

Mat HistogramEqualization(Mat src){
    Mat histoEq = src.clone();
    vector<Mat> HSV(3);

    cvtColor(histoEq, histoEq, CV_BGR2HSV);
    split(histoEq, HSV);

    equalizeHist(HSV[2
    
    
    
    ], HSV[2]);

    merge(HSV, histoEq);
    cvtColor(histoEq, histoEq, CV_HSV2BGR);

    return histoEq;
}

Mat sliceColor(Mat src){
    Mat slice = src.clone();
    vector<Mat> HSV(3);

    uchar * h, *s;

    cvtColor(slice, slice, CV_BGR2HSV);
    split(slice, HSV);


    for (int j = 0 ; j < slice.rows ; j ++){
        h = HSV[0].ptr<uchar>(j);
        s = HSV[1].ptr<uchar>(j);
        for (int i = 0; i < slice.cols;i++){
            if( 9 < h[i] && h[i] < 23) ;
            else s[i] = 0;
        }
    }

    merge(HSV, slice);
    cvtColor(slice, slice, CV_HSV2BGR);

    return slice;
}


Mat conversionColor(Mat src){
    Mat cvt = src.clone();
    vector<Mat> HSV(3);

    uchar * h, *s;

    cvtColor(cvt, cvt, CV_BGR2HSV);
    split(cvt, HSV);


    for (int j = 0 ; j < cvt.rows ; j ++){
        h = HSV[0].ptr<uchar>(j);
        s = HSV[1].ptr<uchar>(j);
        for (int i = 0; i < cvt.cols;i++){
            
            if (h[i] > 129) h[i] = h[i] - 129;
            else h[i] += 50;
        }
    }

    merge(HSV, cvt);
    cvtColor(cvt, cvt, CV_HSV2BGR);

    return cvt;
}


Mat averageFiltering(Mat src){
    Mat avg = src.clone();

    blur(avg, avg, Size(9, 9));

    return avg;
}


void whiteBalancing(Mat src){
    Mat bgr_channels[3];
    split(src, bgr_channels);


    double avg;
    int sum, temp, i, j, c;


    for(c=0;c<src.channels(); c++){
        sum = 0 ;
        avg = 0.0f;
        for(i=0; i<src.rows; i++){
            for( j = 0 ; j < src.cols ; j++){
                sum += bgr_channels[c].at<uchar>(i,j);
            }
        }

        avg = sum / (src.rows * src.cols);
        for(i=0; i<src.rows; i++){
            for( j = 0 ; j < src.cols ; j++){
                temp = (128/avg) * bgr_channels[c].at<uchar>(i,j);

                if(temp>255) bgr_channels[c].at<uchar>(i,j) = 255;
                else bgr_channels[c].at<uchar>(i,j) = temp;
            }
        }

    }

    merge(bgr_channels,3,src);
}