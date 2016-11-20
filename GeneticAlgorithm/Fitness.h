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
		Mat source;
		MatND source_hist;
	public:
		int method = 0;
		Fitness();
		int solutionLength;
		double getSim(Mat image, int method);
};

Fitness::Fitness()
{
	source = imread("asdf.jpg", 1);

	int channels[] = { 0,1 };
	int histSize[] = { 50,60 };
	float hueRange[] = { 0,180 };
	float satRange[] = { 0,256 };
	const  float* ranges[] = { hueRange, satRange };

	if (!source.data)
	{
		cout << "No image found, or you did not open .exe directly";
		cin.get();
	}

	calcHist(&source, 1, channels, Mat(), source_hist, 2, histSize, ranges, true, false);
	normalize(source_hist, source_hist, 0, 1, NORM_MINMAX, -1, Mat());

	resize(source, source, Size(26, 26));
}
double Fitness::getSim(Mat image, int method)
{
	Mat test, temp;
	MatND hist_test;

	if (method == 0)
		resize(image, test, source.size());
	else
	{
		int channels[] = { 0,1 };
		int histSize[] = { 50,60 };
		float hueRange[] = { 0,180 };
		float satRange[] = { 0,256 };
		const  float* ranges[] = { hueRange, satRange };
		test = image;

		calcHist(&test, 1, channels, Mat(), hist_test, 2, histSize, ranges, true, false);
		normalize(hist_test, hist_test, 0, 1, NORM_MINMAX, -1, Mat());
	}

	if (!source.data || !test.data)
	{
		cout << "No image found, or you did not open .exe directly";
		cin.get();
	}
	double result;

	if(method==0)
		result = (10 - (norm(source, test, 4) / (double)(source.rows*test.cols)))*10;
	if (method == 1)
	{
		double base_base = compareHist(source_hist, source_hist, 3);
		double base_test1 = compareHist(source_hist, hist_test, 3);

		result = (1-base_test1) * 100;
	}
	return result;
}

#endif