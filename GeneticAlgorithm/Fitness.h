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
		CvMat src;
		unsigned char *BGRdata;
	public:
		int method = 0;
		Fitness();
		int solutionLength;
		double getSim(Mat image, int method);
};

Fitness::Fitness()
{
	source = imread("asdf.jpg", 1);
	if (!source.data)
	{
		cout << "No image found, or you did not open .exe directly";
		cin.get();
	}
	cout << "2. Source image read" << endl;
	BGRdata = (unsigned char*)(source.data);
	cout << "3. Image decoded" << endl;
}
double Fitness::getSim(Mat image, int number)
{
	Mat test;
	resize(image, test, source.size());
	unsigned char *imageData = (unsigned char*)(test.data);
	CvMat temp = test;

	int cols = source.cols;
	int rows = source.rows;
	int fit = 1228800;

	for (int i = 0;i < cols;i++) {
		for (int j = 0;j < rows;j++) {
			fit-= abs(imageData[temp.step * j + i] - BGRdata[temp.step * j + i]);
			fit-= abs(imageData[temp.step * j + i + 1] - BGRdata[temp.step * j + i + 1]);
			fit-= abs(imageData[temp.step * j + i + 2] - BGRdata[temp.step * j + i + 2]);
		}
	}
	return fit;
}

#endif