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

Mat equalizeHist_3(Mat srcMat)
{
	
	vector<Mat>channels;
	split(srcMat, channels);

	
	equalizeHist(channels.at(0), channels.at(0));
	equalizeHist(channels.at(1), channels.at(1));
	equalizeHist(channels.at(2), channels.at(2));

	
	Mat dstMat;
	srcMat.copyTo(dstMat);
	merge(channels, dstMat);

	return dstMat;
}

int main()
{
	Mat srcMat = imread("G:\\picture\\6.jpg", 1);
	Mat dstMat_1;
	float gamma_1 = 4;
	
	dstMat_1 = equalizeHist_3(srcMat);


	dstMat_1 = gammaTransform(dstMat_1, gamma_1);

	imshow("srcMat", srcMat);
	imshow("dstMat_1", dstMat_1);
	waitKey(0);
}