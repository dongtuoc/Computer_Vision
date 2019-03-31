#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("C:\\Users\\Administrator\\Desktop\\C++_AI\\butterfly.jpg");

	Mat DownImg;
	resize(src, DownImg, Size(src.cols/2, src.rows/2));
	imshow("source img", DownImg);

	Mat AverImg;
	blur(DownImg, AverImg, Size(3, 3));
	imshow("Average Img",AverImg);

	/*�˴�СԼ����sigma��3�� 3sigma֮��Խ��99%����Ϣ*/
	Mat GausImg;
	GaussianBlur(DownImg, GausImg, Size(5, 5), 0, 0);
	imshow("GaussianBlur img", GausImg);

	Mat MidumImg;
	medianBlur(DownImg, MidumImg,3);
	imshow("Median img", MidumImg);

	/*SOBEL ����*/
	Mat SobelImg;
	Mat sobel_x, sobel_y, sobleall;
	Sobel(DownImg, SobelImg, CV_16S, 1, 0);
	convertScaleAbs(SobelImg, sobel_x);
	imshow("Sobel X����", sobel_x);

	Sobel(DownImg, SobelImg, CV_16S, 0, 1);
	convertScaleAbs(SobelImg, sobel_y);
	imshow("Sobel Y����", sobel_y);

	addWeighted(sobel_x, 0.5, sobel_y, 0.5, 0, sobleall);
	imshow("���Ϻ�ͼ�� img", sobel_y);

	/*canny����*/
	Mat CannyImg;
	Canny(DownImg, CannyImg, 3, 9, 3);
	imshow("Canny���� img", CannyImg);


	//��˹�˲���ʹ�ô���㷨Ч������
	const int channels[1] = { 0 };
	const int histsize[1] = { 256 };
	float pranges[2] = { 0,255 };
	const float* ranges[1] = { pranges };
	MatND hist;

	calcHist(&GausImg, 1, channels, Mat(), hist, 1, histsize, ranges);
	//��ʾֱ��ͼ��Ϣ
	for (int i = 0; i < 256; ++i)
	{
		std::cout << "value" << i << " " << hist.at<float>(i) << std::endl;
	}

	Mat dranImg = Mat::zeros(Size(256, 256), CV_8UC3);
	double HisMaxV;
	minMaxLoc(hist, 0, &HisMaxV, 0, 0);
	for (int j = 0; j < 256; ++j)
	{
		int value = cvRound(hist.at<float>(j) * 256 * 0.9 / HisMaxV);
		line(dranImg, Point(j, dranImg.rows - 1), Point(j, dranImg.rows - 1 - value), Scalar(255, 0, 0));
	}

	imshow("�Ҷ�ֱ��ͼ", dranImg);

	/*����㷨 ͼƬ�ָ�*/
	Mat OTsu,gry;
	cvtColor(GausImg,gry,COLOR_BGR2GRAY);
	threshold(gry,OTsu,100,255, THRESH_OTSU);
	imshow("Otsu img",OTsu);

	waitKey(0);
	return 0;
}