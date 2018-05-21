#include <opencv2/opencv.hpp>
#include <iostream>

//#ifdef _DEBUG	//lib�t�@�C���������N
//#pragma comment(lib, "opencv_ts300d.lib")
//#pragma comment(lib, "opencv_world300d.lib")
//#else
//#pragma comment(lib, "opencv_ts300.lib")
//#pragma comment(lib, "opencv_world300.lib")
//#endif

using namespace std;

int mainF(int argc, char *argv[])
{
	//������o�������摜��ǂݍ���
	string imagename = "./lena.jpg";
	cv::Mat img = cv::imread(imagename);
	if (img.empty()){
		cout << "�摜�t�@�C����������܂���ł���" << endl;
		return -1;
	}

	// ������o���邽�߂̉����� �� ���Ȃ��Ă����o�͂ł���
	cv::Mat gray, smallimg;
	cv::cvtColor(img, gray, CV_BGR2GRAY);	// equalizeHist()�̂��߂ɁA�O���[�X�P�[���摜�֕ϊ�
	cv::equalizeHist(gray, gray); 			// �q�X�g�O�����ψꉻ

	double scale = 3.0;						// �������ԒZ�k�̂��߂ɉ摜���k��
	cv::resize(gray, smallimg, cv::Size(img.cols / scale, img.rows / scale));
	// �������I���

	// ���ފ�̓ǂݍ���
	string cascadeName = "./haarcascade_frontalface_alt.xml"; // Haar-like
	cv::CascadeClassifier cascade;
	if (!cascade.load(cascadeName))
	{
		cout << "���ފ킪������܂���ł���" << endl;
		return -1;
	}

	//���ފ�ɂ���Č��o����
	vector<cv::Rect> faces;	//�猟�o�̈���i�[����z��I�Ȃ���
	cascade.detectMultiScale(smallimg, faces);	// �����F�摜�C�o�͋�`�i���o���ꂽ����͂ށj
	
	// ���ʂ̕`��
	for (int i=0; i < faces.size(); i++) {	//���o������̐��������[�v
		// ���̉摜�T�C�Y�ɍ��킹�邽�߂ɁAscale��������
		int facex = faces[i].x * scale,
			facey = faces[i].y * scale,
			facew = faces[i].width * scale,
			faceh = faces[i].height * scale;
		
		// �����炭�ڂ��낤�ʒu��ROI�𒊏o
		cv::Mat eye(img, 
			cv::Rect(facex, facey + faceh * 0.25,facew, faceh * 0.25));
		eye = cv::Scalar(0, 0, 0);	// ���œh��Ԃ�
	}

	cv::imshow("image", img);
	cv::waitKey(0);
}