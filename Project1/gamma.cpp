#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

/*实现gamma变换*/
Mat gammaTransform(Mat &srcImage, float gamma)
{
	//建立查询表
	unsigned char LUT[256] = {0};
	for (int i = 0; i < 256; i++)
	{
		float f = (float)i / 255;
		f = (float)(pow(f, gamma));
		LUT[i] = saturate_cast<uchar>(f*255.0f);
	}
	Mat resultImage;
	srcImage.copyTo(resultImage);

	//根据通道数不同进行处理图像
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
int main()
{
	Mat srcMat = imread("G:/picture/5.jpg", 0);
	Mat dstMat_1, dstMat_2;
	float gamma_1 = 0.5;
	float gamma_2 = 2.0;
	
	//gamma变换
	dstMat_1 = gammaTransform(srcMat, gamma_1);
	dstMat_2 = gammaTransform(srcMat, gamma_2);
	
	imshow("srcMat",srcMat);
	imshow("dstMat_1",dstMat_1);
	imshow("dstMat_2", dstMat_2);
	waitKey(0);
}