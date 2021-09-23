#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(){

    // Lena
    Mat lenaImg = imread("/Users/ahnssu/git/Class_ComputerVision/2_Assignment/assn3/src/Lena.png");

    int lena_len = int(lenaImg.cols/2);

    Rect lena_LHS(0, 0, lena_len, lenaImg.rows);
    Mat lenaLeft = lenaImg(lena_LHS).clone();
    blur(lenaLeft, lenaLeft, Size(7,7));


    // Moon
    Mat moonImg = imread("/Users/ahnssu/git/Class_ComputerVision/2_Assignment/assn3/src/moon.png");
    
    int moon_len = int(moonImg.cols/2);

    Rect moon_RHS(moon_len, 0, moon_len, moonImg.rows);
    Mat moonRight = moonImg(moon_RHS).clone();
    Mat laplacian;
    Laplacian(moonRight, laplacian, CV_16S);
    convertScaleAbs(laplacian, laplacian);
    moonRight = moonRight + laplacian;


    // Salt n Pepper
    Mat saltnPepperImg = imread("/Users/ahnssu/git/Class_ComputerVision/2_Assignment/assn3/src/saltnpepper.png");
    Mat saltFilterd;
    medianBlur(saltnPepperImg, saltFilterd, 9);




    // display
    imshow("lena", lenaImg);
    imshow("lena_filtered", lenaLeft);

    imshow("moon", moonImg);
    imshow("moon_filetered", moonRight);

    imshow("saltnpepper", saltnPepperImg);
    imshow("saltnpepper_filtered", saltFilterd);

    waitKey(0);
    return 0;

}