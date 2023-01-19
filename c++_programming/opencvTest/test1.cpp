#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(void)
{
	Mat src, gray,grayThresh, dst;
	
	src = imread("CESImage.jpg",1);
    namedWindow("src", CV_WINDOW_AUTOSIZE);
	namedWindow("gray",CV_WINDOW_AUTOSIZE);
	namedWindow("grayThreshold",CV_WINDOW_AUTOSIZE);
	namedWindow("Canny",CV_WINDOW_AUTOSIZE); 
	cvtColor(src, gray,CV_BGR2GRAY);
    
	//color images are BGR!
    threshold(gray, grayThresh, 100, 250, CV_THRESH_BINARY);
	Canny(src, dst, 100, 250, 3);
    imshow("src", src); imshow("gray", gray);
	imshow("grayThreshold", grayThresh);
	imshow("Canny", dst);

    waitKey(0);//waits for a key: it also handles the GUI events.

	return 0;
}
