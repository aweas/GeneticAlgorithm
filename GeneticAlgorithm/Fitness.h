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
		int getFitness(Mat image);
};

int Fitness::getFitness(Mat image)
{
	/*				WORKING IMAGE COMPARISION		*/
	Mat src_base, hsv_base;
	Mat src_test1, hsv_test1;
	Mat src_test2, hsv_test2;
	Mat hsv_half_down;

	/// Load three images with different environment settings

	src_base = imread("asdf.jpg", 1);
	src_test1 = image;

	if (!src_base.data || !src_test1.data)
	{
		cout << "No image found, or not opened .exe directly";
		cin.get();
	}
	cout << 1;
	/// Convert to HSV
	cvtColor(src_base, hsv_base, COLOR_BGR2HSV);
	cvtColor(src_test1, hsv_test1, COLOR_BGR2HSV);

	/// Using 50 bins for hue and 60 for saturation
	int h_bins = 50; int s_bins = 60;
	int histSize[] = { h_bins, s_bins };

	// hue varies from 0 to 179, saturation from 0 to 255
	float h_ranges[] = { 0, 180 };
	float s_ranges[] = { 0, 256 };

	const float* ranges[] = { h_ranges, s_ranges };

	// Use the o-th and 1-st channels
	int channels[] = { 0, 1 };

	/// Histograms
	MatND hist_base;
	MatND hist_test1;

	/// Calculate the histograms for the HSV images
	calcHist(&hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false);
	normalize(hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false);
	normalize(hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat());

	double max_base_value[4] = { 1,1000,46.739756, 1 };
	double test1_sum = 0;
	cout << "Comparing start" << endl;

	/// Apply the histogram comparison methods
	for (int i = 0; i < 4; i++)
	{
		int compare_method = i;
		double base_base = compareHist(hist_base, hist_base, compare_method);
		double base_test1 = compareHist(hist_base, hist_test1, compare_method);

		if (i == 0)
			test1_sum += base_test1 / max_base_value[i] * 100;
		else if (i == 2)
			test1_sum += base_test1 / max_base_value[i] * 100;
		else if (i == 3)
			test1_sum += (1 - base_test1) / max_base_value[i] * 100;
	}
	printf("Similarity: %f %c\n", test1_sum / 3, '%');

	//imshow("Image", image);

	return test1_sum * 1000;
}
#endif