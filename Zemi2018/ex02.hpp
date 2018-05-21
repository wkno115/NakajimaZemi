#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

void blurTest() {
	cv::Mat image = cv::imread("lena.jpg");
	cv::Mat blurimage;
	cv::blur(image, blurimage,cv::Size(1,20));
	cv::imshow("Blur", blurimage);

	cv::waitKey();
}

void blurToOrientation() {
	int blursize = 2;	//平滑化のカーネルサイズ
	int dblursize = 1;		//ブラーの変化量
	while (true) {
		cv::Mat image = cv::imread("lena.jpg");
		cv::Mat blurimage;
		cv::blur(image, blurimage, cv::Size(blursize, blursize));
		cv::imshow("Blur", blurimage);	

		if (blursize==1||blursize==20) {
			dblursize = -dblursize;
		}

		blursize += dblursize;
		
		cv::waitKey(33);
	}
}

void only_V_blur() {
	cv::Mat image = cv::imread("lena.jpg");
	cv::Mat hsvImage;
	cv::Mat channels[3];
	cv::Mat mergechannels[3];
	cv::Mat blurImage;
	cv::Mat result;

	cv::cvtColor(image, hsvImage, cv::COLOR_BGR2HSV);
	cv::split(hsvImage, channels);
	mergechannels[0] = channels[0];
	mergechannels[1] = channels[1];
	cv::blur(channels[2] ,mergechannels[2], cv::Size(7, 7));
	cv::merge(mergechannels,3, blurImage);
	cv::cvtColor(blurImage,result,cv::COLOR_HSV2BGR);

	cv::imshow("Image", image);
	cv::imshow("HSV", hsvImage);
	cv::imshow("Gray", channels[2]);
	cv::imshow("Blur_Gray", mergechannels[2]);
	cv::imshow("Blur", blurImage);
	cv::imshow("Result", result);

	cv::waitKey();
}

void main(){
	//blurTest();
	//blurToOrientation();
	only_V_blur();
}