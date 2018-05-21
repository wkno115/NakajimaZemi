#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>


using namespace std;

void saveCameraImage() {
	cv::VideoCapture cap(0);	//�J�������͂̓ǂݍ���//0��windows�ɕW������

	if (cap.isOpened() == false)	//�J�������͂̓ǂݍ��݂Ɏ��s������I��
	{
		cout << "�J�������͂�ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	cv::Mat frame;	//���͉摜

	while (true)
	{
		cap >> frame;	//�J��������̉摜���擾

		if (frame.empty())	//�摜���������ǂݍ��߂��̂����m�F
		{
			cout << "�J�������͂̂��߂ɑҋ@" << endl;
			continue;
		}

		cv::imshow("Output", frame);	//�摜�̕\��

		switch (cv::waitKey(33))
		{
		case 's':
			cv::imwrite("Output.jpg", frame);
			break;
		case 'e':
		case 'q':
			return ;
		default:
			break;
		}
	}	
}

void ClickBlurChange() {
	int xblursize = 1;	//�������̃J�[�l���T�C�Y
	int yblursize = 1;
	cv::Mat image = cv::imread("lena.jpg");
	cv::Mat blurimage;

	while (true) {
		cv::blur(image, blurimage, cv::Size(xblursize, yblursize));
		cv::imshow("Blur", blurimage);

		int key=cv::waitKey(33);

		switch (key)
		{
		case 'w':
			yblursize++;
			break;
		case 's':
			yblursize--;
			break;
		case 'd':
			xblursize++;
			break;
		case 'a':
			xblursize--;
			break;
		case 'e':
		case 'q':
			return;
		default:
			break;
		}

		//���͂��������ꍇ�̓J�[�l���T�C�Y��\��
		if(key!=-1){
			cout << "�J�[�l���T�C�Y(" << xblursize << "," << yblursize << ")"<<endl;
		}

		if (xblursize == 0) {
			xblursize = 1;
		}
		if (yblursize == 0) {
			yblursize = 1;
		}
	}
}

void xGradation() {
	cv::Mat image(cv::Size(256, 256), CV_8UC1);

	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			image.ptr(y,x)[0]=x;
		}
	}
	cv::imshow("Gradation", image);
	cv::waitKey();
}

void Gradation() {
	cv::Mat image(cv::Size(256, 256), CV_8UC1);

	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			image.ptr(y, x)[0] = x/2+y/2;	//���҂������Ă��炶��Ȃ��ƃI�[�o�[�t���[
		}
	}
	cv::imshow("Gradation", image);
	cv::waitKey();
}

void Lines() {
	int arraysample[3] = { 1, 2, 3 };
	cv::Mat image[3] = { cv::Mat() ,cv::Mat(),cv::Mat() };
	int a[]{5,10,50};
	for (int count = 0; count < sizeof a/sizeof a[0]; count++) {
		image[count].create (cv::Size(256, 256), CV_8UC1);
		for (int y = 0; y < image[count].rows; y++) {
			for (int x = 0; x < image[count].cols; x++) {
				if(x%a[count]==0){
					image[count].ptr(y, x)[0] = 0;	//���҂������Ă��炶��Ȃ��ƃI�[�o�[�t���[
				}
				else {
					image[count].ptr(y, x)[0] = 255;
				}
			}
		}		
	}	
	cv::imshow("1", image[0]);
	cv::imshow("2", image[1]);
	cv::imshow("3", image[2]);
	cv::waitKey();
}

void GrayScale() {
	int type = 2;	//�O���f�[�V�����^�C�v
	cv::Mat image = cv::imread("sample_gradation.jpg");
	cv::imshow("Image", image);

	int cols = image.cols, rows = image.rows;
	cv::Mat grayimage(cv::Size(cols,rows),CV_8UC1);
		for (int y = 0; y < image.rows; y++) {
			uchar *p = image.ptr(y);
			uchar *gp = grayimage.ptr(y);
			for (int x = 0; x < image.cols; x++) {
				//�ǂ̃^�C�v�ŃO���f�[�V�������邩
				switch (type) {
				case 1:
					gp[x] = (p[x * 3] + p[x * 3 + 1] + p[x * 3 + 2]) / 3;
					break;
				case 2:
					gp[x] = (max({ p[x * 3], p[x * 3 + 1], p[x * 3 + 2] }) + min({ p[x * 3], p[x * 3 + 1], p[x * 3 + 2] })) / 2;
					break;
				case 3:
					gp[x] = (p[x * 3] * 0.298912 + p[x * 3 + 1] * 0.586611 + p[x * 3 + 2] * 0.114478);
					break;
				default:
					break;
				}
			}
		}
	cv::imshow("GrayImage",grayimage);
	cv::waitKey();
}

int main() {
	//saveCameraImage();
	//ClickBlurChange();
	//xGradation();
	//Gradation();
	//Lines();
	GrayScale();
}