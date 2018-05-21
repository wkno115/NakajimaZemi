#include <opencv2/opencv.hpp>

int main2()
{
	cv::Mat image = cv::imread("Lenna.png");
	cv::imshow("Sample", image);
	cv::waitKey();
	return 0;
}
