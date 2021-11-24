#include "cv.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int main(){
    Mat query, image, descripotrs1, descripotrs2;
    Ptr <ORB> orbF = ORB::create(1000);
    vector <KeyPoint> keypoints1, keypoints2;
    vector < vector < DMatch> > matches;
    vector < DMatch > goodMatches;
    BFMatcher matcher(NORM_HAMMING);

    int i, k;
    float nndr;

    query = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/feature1.png");
    image = imread("/Users/ahn_ssu/git/Class_ComputerVision/src/feature2.png");

    if ( query.empty() || image.empty()) return -1;

    // Compute ORB Feature
    resize(image, image, Size(640, 480));
    orbF->detectAndCompute(query, noArray(), keypoints1, descripotrs1);
    orbF->detectAndCompute(image, noArray(), keypoints2, descripotrs2);
    // KNN matching
    k = 2;
    matcher.knnMatch(descripotrs1, descripotrs2, matches, k);

    nndr = 0.6f;
    for( i=0; i< matches.size(); i++){
        if (matches.at(i).size() == 2 && matches.at(i).at(0).distance <= nndr * matches.at(i).at(1).distance){
            goodMatches.push_back(matches[i][0]);
        }
    }

    // Draw matching
    Mat imgMatches;
    drawMatches(query, keypoints1, image, keypoints2, goodMatches, imgMatches,
            Scalar::all(-1),Scalar(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    // printf("HI\n");

    imshow("imgMatches", imgMatches);
    waitKey(0);

    return 0;

}