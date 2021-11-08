#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat img1 = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/Lena.png",1);
    Mat img2 = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/Lena.png",1 );
    Mat dst;
    cout << img1.type() << endl;
    Mat mask = Mat::zeros(img1.size(), 0); // mask의 타입을 16(BGR)로 설정하면 에러가 남... 0으로 하면 컬러채널에서도 동작

    Rect rect = Rect(10, 10, 300, 300);
    rectangle(mask, rect, Scalar(128,0,0), -1, 8 , 0 ); // thinkness를 -1 해야 mask가 정상적으로 작동 ㄴ
    // cout << img2.size();
    add(img1, img2, img2, mask); // color channel을 사용하면 여기에서 터짐 
    cout << img1.type() << endl;
    
    // float coef_ = 1.5F;
    // scaleAdd(img1, coef_, img2, dst);
    // absdiff(img1, img2, dst);
    // subtract(img1, img2, dst);


    // imshow("addition result", dst);
    // imshow("img1 result", img1);
    imshow("img2 result", img2);
    waitKey(0);
    return 0;

}