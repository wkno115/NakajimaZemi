#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

void GrayReadVideo()
{
	cv::VideoCapture cap("sora.avi");	//動画ファイルの読み込み

	if (cap.isOpened() == false)	//動画ファイルを正しく読み込めたか
	{
		cout << "動画ファイルを読み込めませんでした．" << endl;
		return;
	}

	while (true)
	{
		cv::Mat frame;
		cap >> frame;	//動画からの画像を取得

		if (frame.data == NULL)	//動画からの画像を全て読み込んだら終了
			break;

		cv::Mat grayframe;
		cv::cvtColor(frame, grayframe, CV_BGR2GRAY);
		cv::imshow("Output", grayframe);

		cv::waitKey(33);	//引数の数値を変化させると…？
	}
}

void GrayCamera()
{
	cv::VideoCapture cap(0);	//カメラ入力の読み込み//0はwindowsに標準装備

	if (cap.isOpened() == false)	//カメラ入力の読み込みに失敗したら終了
	{
		cout << "カメラ入力を読み込めませんでした．" << endl;
		return;
	}

	while (true)
	{
		cv::Mat frame;
		cap >> frame;	//カメラからの画像を取得

		if (frame.empty())	//画像が正しく読み込めたのかを確認
		{
			cout << "カメラ入力のために待機" << endl;
			continue;
		}
		cv::Mat grayframe;
		cv::cvtColor(frame, grayframe, CV_BGR2GRAY);

		cv::imshow("Output", grayframe);	//画像の表示

		if (cv::waitKey(33) >= 0)	//33ms待機後、入力があればbreak
			break;
	}
}

void ExNegaPosi()
{
	cv::Mat image = cv::imread("sample_split.jpg");

	if (image.empty())
	{
		cout << "画像ファイルを読み込めませんでした．" << endl;
		return;
	}

	cv::imshow("image", image);

	image = ~image;	//ネガポジ反転

	cv::imshow("invert", image);	//ネガポジ反転画像の表示

	cv::waitKey();
}

//画像内のある領域を抽出
void ExtractROI()
{
	cv::Mat image = cv::imread("sample.jpg");
	if (image.empty())
	{
		cout << "画像ファイルを読み込めませんでした．" << endl;
		return;
	}

	cv::Mat roi(image, cv::Rect(200, 150, 250, 150));	//領域の切り抜き

	image = ~image;
	roi = ~roi;

	cv::imshow("image", image);	//元画像の表示

	cv::waitKey();
}

//チャンネルの分割・統合
void BlueNegaImage()
{
	cv::Mat image = cv::imread("sample_split.jpg");

	if (image.empty())
	{
		cout << "画像ファイルを読み込めませんでした．" << endl;
		return;
	}

	cv::imshow("image", image);

	cv::Mat channels[3];
	cv::split(image, channels);	//imageを3つのMatオブジェクトに分離

	channels[0] = ~channels[0];

	cv::Mat negaImage;
	cv::merge(channels, 3, negaImage);	//チャンネルを並び替えた画像を生成

	cv::imshow("BlueNegaImage", negaImage);

	cv::waitKey();
}

void main() {
	//GrayReadVideo(); //動画をグレースケール化する。
	//GrayCamera();	//カメラの画像をグレースケール化。
	//ExNegaPosi();
	//ExtractROI();
	BlueNegaImage();
}