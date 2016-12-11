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
		CvMat src;
		unsigned char *BGRdata;
		float firstSpecimen=1;
	public:
		Mat source;
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
	resize(source, source, Size(128,128));
	cout << "3. Image decoded. Rows: " << source.rows << endl;
}

void Fitness::Initialize(int num)
{
	firstSpecimen = num;
}

double Fitness::getSim(Mat image, int number)
{
	Mat test, tempsrc;
	//if(test.rows!=source.rows)
	//	resize(source, source, image.size());
	test = image;
	unsigned char *imageData = (unsigned char*)(test.data);
	CvMat temp = test;

	int cols = test.cols;
	int rows = test.rows;
	long fit = 0;

	for (int i = 0;i < cols;i++) {
		//double multiplier = 1.0;
		for (int j = 0;j < rows;j++) {
			//if (i > 35 && i < 95)
			//	multiplier = 2.0;

			Point3_<uchar>* p = test.ptr<Point3_<uchar> >(j, i);
			Point3_<uchar>* s = source.ptr<Point3_<uchar> >(j, i);

			long mean = (p->z + s->z) / 2;
			long r = p->z - s->z;
			long g = p->y - s->y;
			long b = p->x - s->x;

			fit -= (sqrt((((512 + mean)*r*r) >> 8) + 4 * g*g + (((767 - mean)*b*b) >> 8)));
		}
	}
	//cout << fit << " " << firstSpecimen << endl;
	if (firstSpecimen== 1)
		return fit;
	return ((double)(firstSpecimen - fit)*100/firstSpecimen);
}

#endif