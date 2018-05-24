#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include "Effects.hpp"
#include <math.h>

using namespace std;
//cvをusingするとimshowがあいまいになる。

void SampleEye() {
	static int count = 0;		//目を閉じている秒数を数える
	static bool done = false;	//発動フラグ
	// カメラの起動
	cv::VideoCapture cap(0);
	cv::CascadeClassifier cascade;
	if (!cascade.load("./haarcascade_eye.xml"))
	{
		cout << "分類器が見つかりませんでした" << endl;
		return;
	}
	vector<cv::Rect> eyes;
	cv::Mat frame;
	while (true) {
		// カメラから取得した画像をフレームに落とし込む
		cap >> frame;
		// 目を検出するための下準備 → やらなくても検出はできる
		cv::Mat gray, smallimg;
		cv::cvtColor(frame, gray, CV_BGR2GRAY);	// equalizeHist()のために、グレースケール画像へ変換
		cv::equalizeHist(gray, gray); 			// ヒストグラム均一化

		double scale = 3.0;						// 処理時間短縮のために画像を縮小
		cv::resize(gray, smallimg, cv::Size(frame.cols / scale, frame.rows / scale));
		// 下準備終わり

		// 指定した識別器を用いて画像から対象を検出
		cascade.detectMultiScale(smallimg, eyes);
		//縮小画像の破棄
		smallimg.release();
		// 検出した対象を囲む矩形を元画像に描画
		//目が認識されない場合に起動
		if (eyes.size()<=1) {
			cout << "Go on";
			cout << count;
			count++;
			if (count >= 30) {
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
			// 元の画像サイズに合わせるために、scaleをかける
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

		//目元を判定しただけの画像
		cv::imshow("Old eyes", frame);

		if (done&&eyes.size() >= 2) {
			cout << doneh;
			donex = donex / eyes.size();
			doney = doney / eyes.size()+doneh;		//目1個分上げる
			donew /= eyes.size();
			doneh/=eyes.size();
			if (doney + doneh > frame.rows) {
				doney = frame.rows-doneh ;
			}
			x_roi2 = donex + (eyes.size()*donew);
			y_roi2 = doney-doneh;
			if (y_roi2 < 0) {
				y_roi2 = 0;
			}
			//目の囲いの真ん中からそれぞれ「ほにゃ％」
			cout << "_"<<frame.cols;
			cv::Mat roi(frame, cv::Rect(0, doney, frame.cols, doneh));	//目元付近の関心領域
			cv::Mat bigRoi;			//目元アップ画像格納
			cv::resize(roi, bigRoi, cv::Size(frame.cols * 2, doneh * 2), frame.cols, doneh);
			cv::Mat roi2(bigRoi, cv::Rect(x_roi2, y_roi2, roi.cols, roi.rows));
			//Sharpening(roi2).copyTo(roi2);	先鋭化フィルタ
			BlueUpper(roi2).copyTo(roi2);
			Darker(frame).copyTo(frame);

			cv::Mat center_roi(frame, cv::Rect(0, (frame.rows-roi.rows)/2,roi.cols,roi.rows ));		//画像の中央に配置する用
			roi2.copyTo(center_roi);
			
			//frameを透明化
			AlphaPlus(frame);

			//「カッ」を入れる。200*200のroi
			cv::Mat4b se_roi(frame, cv::Rect(frame.cols-200,center_roi.rows-100 , 200, 200));
			KatIn(se_roi).copyTo(se_roi);
			
			cv::imshow("BigRoi", bigRoi);
			cv::imshow("roi", roi);
			cv::imshow("se_roi",se_roi);
			cv::imshow("New eyes", frame);
			done = false;
		}
		cv::imshow("Detect eyes", frame);

		if (cv::waitKey(33) >= 0)	//33ms待機後、入力があればbreak
			break;
	}
}

void main() {
	SampleEye();
	
}