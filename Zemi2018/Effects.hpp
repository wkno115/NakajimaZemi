#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <stdio.h>

using namespace std;

void AlphaPlus(cv::Mat& image) {
	cv::Mat alpha_image = cv::Mat(image.size(), CV_8UC4);
	cv::cvtColor(image, alpha_image, CV_RGB2RGBA);
	for (int y = 0; y < alpha_image.rows; ++y) {
		unsigned char* px = alpha_image.ptr(y);
		for (int x = 0; x < alpha_image.cols; ++x) {
			if (px[0] + px[1] + px[2] == 0) {
				px[3] = 0;
			}
		}
	}
	alpha_image.copyTo(image);
}

cv::Mat Darker(cv::Mat frame) {//送られてきた画像が暗くなる
	//暗くした画像を入れる
	cv::Mat dark_frame(cv::Size(frame.cols, frame.rows), CV_8UC3);
	//各色要素を暗くする
	for (int y = 0; y < frame.rows; y++) {
		uchar *fp = frame.ptr(y);
		uchar *dfp = dark_frame.ptr(y);
		for (int x = 0; x < frame.cols; x++) {
			dfp[x * 3] = fp[x * 3] * 0.2;
			dfp[x * 3 + 1] = fp[x * 3 + 1] * 0.2;
			dfp[x * 3 + 2] = fp[x * 3 + 2] * 0.2;
		}
	}
	return dark_frame;
}

cv::Mat BlueUpper(cv::Mat frame) {//青くなり疾走感も出る
	//処理後の画像を入れる
	cv::Mat blue_frame(cv::Size(frame.cols, frame.rows), CV_8UC3);
	//各色要素を処理
	int r;	//勢いづけるかを決める乱数
	int k;	//色を弱める係数
	for (int y = 0; y < frame.rows; y++) {
		uchar *fp = frame.ptr(y);
		uchar *bfp = blue_frame.ptr(y);
		for (int x = 0; x < frame.cols; x++) {
			if (fp[x * 3] * 1.5 > 255) {
				bfp[x * 3] = fp[x * 3];
			}
			else {
				bfp[x * 3] = fp[x * 3] + 30;
			}
			bfp[x * 3 + 1] = fp[x * 3 + 1] * 0.99;
			bfp[x * 3 + 2] = fp[x * 3 + 2] * 0.85;
		}
	}

	return blue_frame;
}

//カッが表示される
cv::Mat KatIn(cv::Mat image) {
	cv::Mat se_image = cv::imread("SE_P4.png", CV_LOAD_IMAGE_UNCHANGED);
	//カッが大きすぎたら修正
	if (se_image.rows != image.rows || se_image.cols != image.cols) {
		cv::resize(se_image, se_image, cv::Size(image.rows, image.cols));
	}
	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			for (int i = 0; i < image.channels()-1; i++) {	//透過度はいじらない
				if (se_image.ptr(x, y)[i] + image.ptr(x, y)[i] < 255) {
					se_image.ptr(x, y)[i] += image.ptr(x, y)[i];
				}
				else {
					se_image.ptr(x, y)[i]=255;
				}
			}
		}
	}
	return se_image;
}
/*
void blend_two_images() {
	cv::Mat underlay = cv::imread("/home/underlay.png", CV_LOAD_IMAGE_UNCHANGED);
	cv::Mat overlay = cv::imread("/home/overlay.png", CV_LOAD_IMAGE_UNCHANGED);
	cv::Mat roi = underlay(cv::Rect(0, 0, overlay.cols, overlay.rows));

	cv::addWeighted(roi, 0, overlay, 1, 0, roi);
	cv::imwrite("/home/result.png", underlay);
}
*/

cv::Mat3b Sharpening(cv::Mat3b frame) {
	cv::Mat sharp_frame(cv::Size(frame.cols,frame.rows),CV_8UC3);
	cv::Mat hsvFrame;
	cv::Mat lap;
	cv::Mat channels[3];
	cv::Mat mergechannels[3];
	
	cv::cvtColor(frame, hsvFrame, cv::COLOR_BGR2HSV);
	cv::split(hsvFrame, channels);
	mergechannels[0] = channels[0];
	mergechannels[1] = channels[1];
	cv::Laplacian(channels[2], lap, CV_8U, 3);
	mergechannels[2] =channels[2] - lap;
	cv::merge(mergechannels, 3, sharp_frame);
	cv::cvtColor(sharp_frame, sharp_frame, cv::COLOR_HSV2BGR);
	
	return sharp_frame;
}

static cv::Mat Speedy(cv::Mat image) {
	cv::Mat speedy_image = image;
	
	return speedy_image;
}

