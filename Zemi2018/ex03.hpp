#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>


using namespace std;

void saveCameraImage() {
	cv::VideoCapture cap(0);	//カメラ入力の読み込み//0はwindowsに標準装備

	if (cap.isOpened() == false)	//カメラ入力の読み込みに失敗したら終了
	{
		cout << "カメラ入力を読み込めませんでした．" << endl;
		return;
	}

	cv::Mat frame;	//入力画像

	while (true)
	{
		cap >> frame;	//カメラからの画像を取得

		if (frame.empty())	//画像が正しく読み込めたのかを確認
		{
			cout << "カメラ入力のために待機" << endl;
			continue;
		}

		cv::imshow("Output", frame);	//画像の表示

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
	int xblursize = 1;	//平滑化のカーネルサイズ
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

		//入力があった場合はカーネルサイズを表示
		if(key!=-1){
			cout << "カーネルサイズ(" << xblursize << "," << yblursize << ")"<<endl;
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
			image.ptr(y, x)[0] = x/2+y/2;	//両者を割ってからじゃないとオーバーフロー
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
					image[count].ptr(y, x)[0] = 0;	//両者を割ってからじゃないとオーバーフロー
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
	int type = 2;	//グラデーションタイプ
	cv::Mat image = cv::imread("sample_gradation.jpg");
	cv::imshow("Image", image);

	int cols = image.cols, rows = image.rows;
	cv::Mat grayimage(cv::Size(cols,rows),CV_8UC1);
		for (int y = 0; y < image.rows; y++) {
			uchar *p = image.ptr(y);
			uchar *gp = grayimage.ptr(y);
			for (int x = 0; x < image.cols; x++) {
				//どのタイプでグラデーションするか
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