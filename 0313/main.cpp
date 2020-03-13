#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

string window_name = "binaryMat";
void threshod_Mat(int th, void*data)
{
	Mat src = *(Mat*)(data);
	Mat dst;
	//二值化
	threshold(src, dst, th, 255, 0);
	imshow(window_name, dst);
}

int main()
{
	int lowth = 30;
	int maxth = 255;
	//.........练习三.回调函数.....................//
	Mat greyMat = imread("C:\\Users\\YangYF\\Desktop\\1.JPG",0);
	if (!greyMat.data)
	{
		cout << "图像载入失败！" << endl;
		return 0;
	}
	
	imshow(window_name, greyMat);
	createTrackbar("滑动条", 
				     window_name,
				     &lowth, maxth, 
				     threshod_Mat,
				     &greyMat);
			waitKey(0);
	//.........练习二.二值化.调用两种函数..........//
	Mat scrM = imread("C:\\Users\\YangYF\\Desktop\\1.JPG", 0);
	Mat result;
	threshold(scrM, result, 100, 255, THRESH_BINARY);
	imshow("result", result);
	
	Mat result2;
	
	adaptiveThreshold(scrM, result2, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 15, 10);//反二进制阈值
	imshow("result2",result2);

	waitKey(0);

	// .......练习一肤色检测.......//

	VideoCapture cap(0);
	double scale = 1.5;
	//定义肤色
	double i_minh = 0;
	double i_maxh = 20;
	//饱和度
	double i_mins = 43;
	double i_maxs = 255;
	//亮度
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


