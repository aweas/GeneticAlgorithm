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
	int firstSpecimen = 1;
public:
	int method = 0;
	Fitness();
	void Initialize(int num);
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

void Fitness::Initialize(int num)
{
	firstSpecimen = num;
}

double Fitness::getSim(Mat image, int number)
{
	Mat test;
	resize(image, test, source.size());
	unsigned char *imageData = (unsigned char*)(test.data);
	CvMat temp = test;

	int cols = source.cols;
	int rows = source.rows;
	long fit = 0;

	for (int i = 0;i < cols;i++) {
		//int multiplier = 0;
		for (int j = 0;j < rows;j++) {
			//if (i > 61 && i < 97 && j<76 && j>10)
			//multiplier = 3;

			Point3_<uchar>* p = test.ptr<Point3_<uchar> >(j, i);
			Point3_<uchar>* s = source.ptr<Point3_<uchar> >(j, i);

			long mean = (p->z + s->z) / 2;
			long r = p->z - s->z;
			long g = p->y - s->y;
			long b = p->x - s->x;

			fit -= (sqrt((((512 + mean)*r*r) >> 8) + 4 * g*g + (((767 - mean)*b*b) >> 8)));
		}
	}
	//	cout << fit << " " << firstSpecimen << endl;
	return ((double)(fit - firstSpecimen) * 100 / firstSpecimen);
}

#endif