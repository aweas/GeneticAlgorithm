#pragma once
#define FITNESS_H
#ifdef FITNESS_H

#include <string>
#include <opencv\cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"

using namespace std;
using namespace cv;

class Fitness
{
	private:
		string solution;
		
	public:
		int solutionLength;
		double getFitness(Mat image);
		double getSim(int method, Mat image);
};

double Fitness::getSim(int method, Mat image)
{
	Mat source, test, temp;
	double PSNR = 100;

	source = imread("asdf.jpg", 1);
	resize(image, test, source.size());
	/*test = imread("zielony_mur.jpg", 1);
	resize(test, test, source.size());*/

	absdiff(source, test, temp);
	temp.convertTo(temp, CV_32F);
	temp = temp.mul(temp);

	Scalar summary = sum(temp);
	double channelSum = summary.val[0] + summary.val[1] + summary.val[2];

	if (channelSum <= 1e-10)
		return 0;
	
	double MSE = channelSum / (double)(source.channels()*source.total());

	if(MSE != 0)
		 PSNR = 10.0 * log10((255 * 255)/ MSE);
	else
		cout << MSE << endl;

	return PSNR;

	//if (!source.data || !test.data)
	//{
	//	cout << "No image found, or you did not open .exe directly";
	//	cin.get();
	//}
	//
	//double result = 100 - (norm(source, test, method) / (double)(source.rows*test.cols));
	//return result;
}

double Fitness::getFitness(Mat image)
{
	/*				WORKING IMAGE COMPARISION		*/
	Mat src_base, hsv_base;
	Mat src_test1, hsv_test1;

	src_base = imread("asdf.jpg", 1);
	//resize(image, src_test1, src_base.size());
	src_test1 = imread("kropki.jpg", 1);

	if (!src_base.data || !src_test1.data)
	{
		cout << "No image found, or you did not open .exe directly";
		cin.get();
	}

	/// Convert to HSV
	//cvtColor(src_base, hsv_base, COLOR_BGR2HSV);
	//cvtColor(src_test1, hsv_test1, COLOR_BGR2HSV);

	///// Using 50 bins for hue and 60 for saturation
	//int h_bins = 50; int s_bins = 60;
	//int histSize[] = { h_bins, s_bins };

	//// hue varies from 0 to 179, saturation from 0 to 255
	//float h_ranges[] = { 0, 180 };
	//float s_ranges[] = { 0, 256 };

	//const float* ranges[] = { h_ranges, s_ranges };

	//// Use the o-th and 1-st channels
	//int channels[] = { 0, 1 };

	///// Histograms
	//MatND hist_base;
	//MatND hist_test1;

	///// Calculate the histograms for the HSV images
	//calcHist(&hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false);
	//normalize(hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat());

	//calcHist(&hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false);
	//normalize(hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat());

	//double max_base_value[4] = { 1,1000,46.739756, 1 };
	double test1_sum = 0;

	/// Apply the histogram comparison methods
	//for (int i = 0; i < 4; i++)
	//{
	//	//int compare_method = i;
	//	//double base_base = compareHist(hist_base, hist_base, compare_method);
	//	//double base_test1 = compareHist(hist_base, hist_test1, compare_method);

	//	//switch (i)
	//	//{
	//	//case 0:
	//	//	//test1_sum += base_test1 / base_base * 100 * 2;
	//	//	//cout << "Algorithm " << i << ": " << base_test1 / base_base * 100<<endl;
	//	//	break;
	//	//case 1:
	//	//	//test1_sum += (1000 - base_test1) / (1000 - base_base) * 100;
	//	//	//cout << "Algorithm " << i << ": " << (1000 - base_test1) / (1000 - base_base) * 100 << endl;
	//	//	break;
	//	//case 2:
	//	//	//test1_sum += base_test1 / max_base_value[i] * 100;
	//	//	//cout << "Algorithm " << i << ": " << base_test1 / base_base * 100 << endl;
	//	//	break;
	//	//case 3:
	//	//	//test1_sum += ((1 - base_test1) / (1 - base_base)) * 100;
	//	//	//cout << "Algorithm " << i << ": " << ((1 - base_test1) / (1 - base_base)) * 100 << endl;
	//	//	break;
	//	//}
	//}
	//printf("Similarity: %f %c\n", test1_sum / 3, '%');
	test1_sum += 100 - norm(src_base, src_test1, 1) / (src_base.rows*src_base.cols);
	cout << "Algorithm " << 1 << ": " << 100 - norm(src_base, src_test1, 1) / (src_base.rows*src_base.cols) << "%" << endl;

	test1_sum += 100 - norm(src_base, src_test1, 2) / (src_base.rows*src_base.cols);
	cout << "Algorithm " << 2 << ": " << 100 - norm(src_base, src_test1, 2) / (src_base.rows*src_base.cols) << "%" << endl;

	test1_sum += 100 - norm(src_base, src_test1, 4) / (src_base.rows*src_base.cols);
	cout << "Algorithm " << 4 << ": " << 100 - norm(src_base, src_test1, 4) / (src_base.rows*src_base.cols) << "%" << endl;
	//imshow("Image", image);
	//cout << norm(src_base, image) << endl;
	return test1_sum/3;
}
#endif