#include <opencv2/opencv.hpp>
#include <iostream>

//#ifdef _DEBUG	//libファイルをリンク
//#pragma comment(lib, "opencv_ts300d.lib")
//#pragma comment(lib, "opencv_world300d.lib")
//#else
//#pragma comment(lib, "opencv_ts300.lib")
//#pragma comment(lib, "opencv_world300.lib")
//#endif

using namespace std;

int mainF(int argc, char *argv[])
{
	//顔を検出したい画像を読み込む
	string imagename = "./lena.jpg";
	cv::Mat img = cv::imread(imagename);
	if (img.empty()){
		cout << "画像ファイルが見つかりませんでした" << endl;
		return -1;
	}

	// 顔を検出するための下準備 → やらなくても検出はできる
	cv::Mat gray, smallimg;
	cv::cvtColor(img, gray, CV_BGR2GRAY);	// equalizeHist()のために、グレースケール画像へ変換
	cv::equalizeHist(gray, gray); 			// ヒストグラム均一化

	double scale = 3.0;						// 処理時間短縮のために画像を縮小
	cv::resize(gray, smallimg, cv::Size(img.cols / scale, img.rows / scale));
	// 下準備終わり

	// 分類器の読み込み
	string cascadeName = "./haarcascade_frontalface_alt.xml"; // Haar-like
	cv::CascadeClassifier cascade;
	if (!cascade.load(cascadeName))
	{
		cout << "分類器が見つかりませんでした" << endl;
		return -1;
	}

	//分類器によって検出する
	vector<cv::Rect> faces;	//顔検出領域を格納する配列的なもの
	cascade.detectMultiScale(smallimg, faces);	// 引数：画像，出力矩形（検出された顔を囲む）
	
	// 結果の描画
	for (int i=0; i < faces.size(); i++) {	//検出した顔の数だけループ
		// 元の画像サイズに合わせるために、scaleをかける
		int facex = faces[i].x * scale,
			facey = faces[i].y * scale,
			facew = faces[i].width * scale,
			faceh = faces[i].height * scale;
		
		// おそらく目だろう位置のROIを抽出
		cv::Mat eye(img, 
			cv::Rect(facex, facey + faceh * 0.25,facew, faceh * 0.25));
		eye = cv::Scalar(0, 0, 0);	// 黒で塗りつぶす
	}

	cv::imshow("image", img);
	cv::waitKey(0);
}