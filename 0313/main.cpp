#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

string window_name = "binaryMat";
void threshod_Mat(int th, void*data)
{
	Mat src = *(Mat*)(data);
	Mat dst;
	//��ֵ��
	threshold(src, dst, th, 255, 0);
	imshow(window_name, dst);
}

int main()
{
	Mat greyMat;
	int lowth = 30;
	int maxth = 255;
	//.........��ϰ��.�ص�����.....................//
	Mat scrMat = imread("C:\\Users\\YangYF\\Desktop\\1.JPG");
	if (!scrMat.data)
	{
		cout << "ͼ������ʧ�ܣ�" << endl;
		return 0;
	}
	cvtColor(scrMat, greyMat, CV_BGR2GRAY);
	imshow(window_name, greyMat);
	createTrackbar("������", 
				     window_name,
				     &lowth, maxth, 
				     threshod_Mat,
				     &greyMat);
			waitKey(0);
	//.........��ϰ��.��ֵ��.�������ֺ���..........//
	Mat scrM = imread("C:\\Users\\YangYF\\Desktop\\1.JPG", 0);
	Mat result;
	threshold(scrM, result, 100, 255, THRESH_BINARY);
	imshow("result", result);
	
	Mat result2;
	
	adaptiveThreshold(scrM, result2, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 15, 10);//����������ֵ
	imshow("result2",result2);

	waitKey(0);

	// .......��ϰһ��ɫ���.......//

	VideoCapture cap(0);
	double scale = 1.5;
	//�����ɫ
	double i_minh = 0;
	double i_maxh = 20;
	//���Ͷ�
	double i_mins = 43;
	double i_maxs = 255;
	//����
	double i_minv = 100;
	double i_maxv = 255;

	while (1)
	{
		Mat frame;
		Mat hsvMat;
		Mat detectMat;

		cap >> frame;
		Size resimgsize = Size(frame.cols*scale, frame.rows*scale);
		Mat rFrame = Mat(resimgsize, frame.type());
		resize(frame, rFrame, resimgsize, INTER_LINEAR);

		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);

		rFrame.copyTo(detectMat);
		inRange(hsvMat, Scalar(i_minh, i_mins, i_minv), Scalar(i_maxh, i_maxs, i_maxv), detectMat);
		imshow("while :in the range", detectMat);
		imshow("frame", rFrame);
		waitKey(30);
	}



	return 0;
}


