#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include "Effects.hpp"
#include <math.h>

using namespace std;
//cv��using�����imshow�������܂��ɂȂ�B

void SampleEye() {
	static int count = 0;		//�ڂ���Ă���b���𐔂���
	static bool done = false;	//�����t���O
	// �J�����̋N��
	cv::VideoCapture cap(0);
	cv::CascadeClassifier cascade;
	if (!cascade.load("./haarcascade_eye.xml"))
	{
		cout << "���ފ킪������܂���ł���" << endl;
		return;
	}
	vector<cv::Rect> eyes;
	cv::Mat frame;
	while (true) {
		// �J��������擾�����摜���t���[���ɗ��Ƃ�����
		cap >> frame;
		// ������o���邽�߂̉����� �� ���Ȃ��Ă����o�͂ł���
		cv::Mat gray, smallimg;
		cv::cvtColor(frame, gray, CV_BGR2GRAY);	// equalizeHist()�̂��߂ɁA�O���[�X�P�[���摜�֕ϊ�
		cv::equalizeHist(gray, gray); 			// �q�X�g�O�����ψꉻ

		double scale = 3.0;						// �������ԒZ�k�̂��߂ɉ摜���k��
		cv::resize(gray, smallimg, cv::Size(frame.cols / scale, frame.rows / scale));
		// �������I���

		// �w�肵�����ʊ��p���ĉ摜����Ώۂ����o
		cascade.detectMultiScale(smallimg, eyes);
		// ���o�����Ώۂ��͂ދ�`�����摜�ɕ`��
		//�ڂ��F������Ȃ��ꍇ�ɋN��
		if (eyes.size()<=1) {
			cout << "Go on";
			cout << count;
			count++;
			if (count >= 10) {
				done = true;
			}
		}
		else if(eyes.size()>=2){
			count = 0;
		}
		int donex = 0;
		int doney = 0;
		int doneh = 0;
		int donew = 0;
		int x_roi2 = 0;
		int y_roi2 = 0;
		for (int i = 0; i < eyes.size(); i++) {
			// ���̉摜�T�C�Y�ɍ��킹�邽�߂ɁAscale��������
			int eyex = eyes[i].x * scale,
				eyey = eyes[i].y * scale,
				eyew = eyes[i].width,
				eyeh = eyes[i].height;
				rectangle(frame, cv::Point(eyex, eyey), cv::Point(eyex + eyew * scale, eyey + eyeh * scale), cv::Scalar(0, 200, 0), 3, CV_AA);
			if (done) {
				donex += eyex;
				doney += eyey;
				doneh += eyeh;
				donew += eyew;
			}
		}

		if (done&&eyes.size()>=2) {
			cout << doneh;
			donex = donex / eyes.size();
			doney = doney / eyes.size()-doneh;		//��1���グ��
			donew /= eyes.size();
			doneh *= 4;
			if (doney+doneh>frame.rows) {
				doney = frame.rows - doneh;
			}
			x_roi2 = donex + (eyes.size()*donew);
			y_roi2 = (doney - doneh);
			if (y_roi2 < 0) {
				y_roi2 = 0;
			}
			cv::Mat roi(frame, cv::Rect(0, doney,frame.cols , doneh));	//�̈�̐؂蔲��
			cv::Mat bigRoi;
			cv::resize(roi,bigRoi,cv::Size(frame.cols*2,doneh*2), frame.cols, doneh);
			cv::Mat roi2(bigRoi, cv::Rect(x_roi2, y_roi2,frame.cols,doneh ));
			//Sharpening(roi2).copyTo(roi2);
			BlueUpper(roi2).copyTo(roi2);
			Darker(frame).copyTo(frame);
			roi2.copyTo(roi);
			cv::imshow("BigRoi", bigRoi);
			cv::imshow("roi", roi);
			cv::imshow("New eyes", frame);
			cv::waitKey();
		}
		cv::imshow("Detect eyes", frame);

		if (cv::waitKey(33) >= 0)	//33ms�ҋ@��A���͂������break
			break;
	}
}

void main() {
	SampleEye();
	
}