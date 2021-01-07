#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


Mat gammaTransform(Mat &srcImage, float gamma)
{
	
	unsigned char LUT[256] = { 0 };
	for (int i = 0; i < 256; i++)
	{
		float f = (float)i / 255;
		f = (float)(pow(f, gamma));
		LUT[i] = saturate_cast<uchar>(f*255.0f);
	}
	Mat resultImage;
	srcImage.copyTo(resultImage);

	
	if (srcImage.channels() == 1)
	{
		for (int i = 0; i < srcImage.rows; i++)
		{
			uchar *data = resultImage.ptr<uchar>(i);
			for (int j = 0; j < srcImage.cols; j++)
			{
				data[j] = LUT[data[j]];
			}
		}
	}
	else
	{
		for (int i = 0; i < srcImage.rows; i++)
		{
			for (int j = 0; j < srcImage.cols; j++)
			{
				resultImage.at<Vec3b>(i, j)[0] = LUT[resultImage.at<Vec3b>(i, j)[0]];
				resultImage.at<Vec3b>(i, j)[1] = LUT[resultImage.at<Vec3b>(i, j)[1]];
				resultImage.at<Vec3b>(i, j)[2] = LUT[resultImage.at<Vec3b>(i, j)[2]];
			}
		}
	}
	return resultImage;
}


void gamma(int gamma, void*)
{
	Mat srcMat = imread("G:\\picture\\5.jpg", 1);
	Mat dstMat;

	float scale = 100;

	float gamma_1 = gamma / scale;

	
	dstMat = gammaTransform(srcMat, gamma_1);

	imshow("srcMat", srcMat);
	imshow("dstMat", dstMat);
}


int main()
{
	int minth = 0;
	int maxth = 50;

				
	namedWindow("dstMat_1", WINDOW_AUTOSIZE);
	createTrackbar("gamma", "dstMat_1", &minth, maxth, gamma);

	waitKey(0);
}