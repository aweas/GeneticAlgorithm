
#include "stdafx.h"
#include "Population.h"
#include "Evolve.h"

#include <iostream>
#include <sstream>
#include <cstdio>
#include <ctime>
#include <opencv\cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"

#define POPULATION_SIZE 10
#define ELITES_NUMBER 3
#define SOLUTION_LENGTH 2515

using namespace cv;
using namespace std;

Mat img; Mat templ; Mat result;
char* image_window = "Source Image";
char* result_window = "Result window";

int match_method;
int max_Trackbar = 5;

int main(int argc, char** argv)
{
	srand(time(NULL));

	Population test(50, true);
	Fitness solution;
	Evolve evolvePop(test, solution, ELITES_NUMBER);
	int generationsCount = 0;

	for (int i = 0;i < 20;i++, generationsCount++)
	{
		evolvePop.EvolvePop();
		if (generationsCount % (50 / 50) == 0)
			printf("#%i Fitness: %f\n", generationsCount, test.getFittest(solution).fitness(solution));
	}


	Mat temp = test.getFittest(solution).image;

	string dupa = "";
	dupa += to_string(test.getFittest(solution).fitness(solution));
	dupa += "%";
	const char* ptr = dupa.c_str();
	cout << ptr;

	putText(temp, ptr, cvPoint(30, 30),
		FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
	imshow("Image", temp);

	waitKey(0);
	cin.get();
	return 0;
}