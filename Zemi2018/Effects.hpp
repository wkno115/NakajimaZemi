#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <stdio.h>

using namespace std;


cv::Mat Darker(cv::Mat frame) {//�����Ă����摜���Â��Ȃ�
	//�Â������摜������
	cv::Mat dark_frame(cv::Size(frame.cols,frame.rows),CV_8UC3);
	//�e�F�v�f���Â�����
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

cv::Mat BlueUpper(cv::Mat frame) {//���Ȃ莾�������o��
	//������̉摜������
	cv::Mat blue_frame(cv::Size(frame.cols,frame.rows),CV_8UC3);
	//�e�F�v�f������
	int r;	//�����Â��邩�����߂闐��
	int k;	//�F����߂�W��
	for (int y = 0; y < frame.rows; y++) {
		uchar *fp = frame.ptr(y);
		uchar *bfp = blue_frame.ptr(y);
		for (int x = 0; x < frame.cols; x++) {
			if (fp[x * 3] * 1.5 > 255) {
				bfp[x * 3] = fp[x * 3];
			}
			else {
				bfp[x * 3] = fp[x * 3] +30;
			}
			bfp[x * 3 + 1] = fp[x * 3 + 1] *0.99;
			bfp[x * 3 + 2] = fp[x * 3 + 2] *0.85;
		}
	}

	return blue_frame;
}
/*
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
*/