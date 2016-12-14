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
		float firstSpecimen[2] = { 1,1 };
		int kernel_size = 3;
		int ratio = 3;
		int lowThreshold;
		int const max_lowThreshold = 100;
	public:
		Mat source, canny;
		int method = 0;
		Fitness();
		void Initialize(Mat image);
		int solutionLength;
		double getSim(Mat image, int method);
};

Fitness::Fitness()
{
	Mat temp;

	source = imread("asdf.jpg", 1);
	if (!source.data)
	{
		cout << "No image found, or you did not open .exe directly";
		cin.get();
	}
	cout << "2. Source image read" << endl;
	resize(source, source, Size(128,128));
	cvtColor(source, temp, CV_BGR2GRAY);
	blur(temp, canny, Size(3, 3));
	Canny(canny, canny, 50, 150, kernel_size);
	cout << "3. Image decoded. Rows: " << source.rows << endl;
}

void Fitness::Initialize(Mat image)
{
	Mat imageCanny;
	cvtColor(image, imageCanny, CV_BGR2GRAY);
	blur(imageCanny, imageCanny, Size(3, 3));
	Canny(imageCanny, imageCanny, 50, 150, 3);

	int cols = image.cols;
	int rows = image.rows;
	float fit = 0, fitCanny=0;

	for (int i = 0;i < cols;i++) {
		for (int j = 0;j < rows;j++)
		{
			Point3_<uchar>* p = image.ptr<Point3_<uchar> >(j, i);
			Point3_<uchar>* s = source.ptr<Point3_<uchar> >(j, i);

			long mean = (p->z + s->z) / 2;
			long r = p->z - s->z;
			long g = p->y - s->y;
			long b = p->x - s->x;

			fit -= (sqrt((((512 + mean)*r*r) >> 8) + 4 * g*g + (((767 - mean)*b*b) >> 8)));

			Point3_<uchar>* pc = imageCanny.ptr<Point3_<uchar> >(j, i);
			Point3_<uchar>* sc = canny.ptr<Point3_<uchar> >(j, i);

			r = pc->z - sc->z;

			if (r == 0 && pc->z == 255)
				fitCanny++;
			if (r != 0)
				fitCanny--;

		}
	}
	firstSpecimen[0] = fit;
	firstSpecimen[1] = fitCanny;
	printf("First image fitness: %f, canny: %f\n", fit, fitCanny);
}

double Fitness::getSim(Mat image, int number)
{
	Mat test, tempSource;
	//if(test.rows!=source.rows)
	//	resize(source, source, image.size());
	test = image;

	if (number == 0)
		tempSource = source;
	else if (number == 1)
		tempSource = canny;

	int cols = test.cols;
	int rows = test.rows;
	long fit = 0;

	for (int i = 0;i < cols;i++) {
		for (int j = 0;j < rows;j++) 
		{
			Point3_<uchar>* p = test.ptr<Point3_<uchar> >(j, i);
			Point3_<uchar>* s = tempSource.ptr<Point3_<uchar> >(j, i);

			long mean = (p->z + s->z) / 2;
			long r = p->z - s->z;
			long g = p->y - s->y;
			long b = p->x - s->x;

			if (number == 0)
				fit -= (sqrt((((512 + mean)*r*r) >> 8) + 4 * g*g + (((767 - mean)*b*b) >> 8)));
			else if (number == 1 && r == 0 && p->z == 255)
				fit++;
			else if (number == 1 && r != 0)
				fit--;
		}
	}
	//cout << fit << " " << firstSpecimen << endl;
	//double fit = norm(test, tempSource);

	return ((double)(firstSpecimen[number] - fit)*100/firstSpecimen[number]);

}

#endif