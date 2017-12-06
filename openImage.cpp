#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("F:\\大学生活\\1.jpg", 4);

	if (img.empty()){
		cout << "Fail to open an image\n";
		return -1;
	}

	imshow("The first opencv programmer", img);
	waitKey();

	return 0;
}