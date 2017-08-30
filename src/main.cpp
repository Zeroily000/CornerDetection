#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int maxCorners = 60;
int maxTrackbar = 600;

int main( int argc, char** argv )
{
    // Load source image and convert it to gray
	cv::Mat img, gray;
	if(argc > 1)
		img = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
	else{
		std::cerr << "Error: No input image" << std::endl;
		return -1;
	}
	cvtColor(img, gray, CV_RGB2GRAY);

	// Set parameters
	std::vector<cv::Point2f> corners;
	int maxCorners = 1000;
	double qualityLevel = 0.001;
	double minDistance = 9;
	int blockSize = 9;
	bool useHarrisDetector = false;
	double k = 0.04;

	cv::goodFeaturesToTrack(gray, corners, maxCorners, qualityLevel, minDistance, cv::Mat(), blockSize, useHarrisDetector, k);

	cv::Size winSize = cv::Size( 9, 9 );
	cv::Size zeroZone = cv::Size( -1, -1 );
	cv::TermCriteria criteria = cv::TermCriteria( CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001 );

	cv::cornerSubPix( gray, corners, winSize, zeroZone, criteria );


	// Draw corners
	for(cv::Point2f p : corners){
		cv::circle(img, p, 3, cv::Scalar(200,10,10));
	}

    /// Create Window
    std::string window = "Corner Detection";
    cv::namedWindow( window, CV_WINDOW_AUTOSIZE );
    cv::imshow( window, img );
    cv::waitKey(0);

    return(0);
}