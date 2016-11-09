
#include "stdafx.h"
#include "Population.h"
#include "Evolve.h"

#include <iostream>
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
#define SOLUTION_LENGTH 2491

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

	Population test(10, true);
	Fitness solution;

	test.getFittest(solution).fitness(solution);

	Mat temp = test.getFittest(solution).image;
	imshow("Image", temp);

	waitKey(0);
	cin.get();
	return 0;
}