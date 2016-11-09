
#include "stdafx.h"
#include "Population.h"
#include "Evolve.h"

#include <iostream>
#include <sstream>
#include <cstdio>
#include <ctime>
#include <conio.h>

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

int main(int argc, char** argv)
{
	srand(time(NULL));

	Population test(10, true);
	Fitness solution;
	Evolve evolvePop(test, solution, ELITES_NUMBER);
	int generationsCount = 0;

	bool cont = true;

	for (int i = 0;test.getFittest(solution).fitness(solution)<50 && !_kbhit();i++, generationsCount++)
	{
		evolvePop.EvolvePop();

		if (generationsCount % (50 / test.populationSize) == 0)
			printf("#%i Fitness: %f%c\n", generationsCount, test.getFittest(solution).fitness(solution), '%');

		if (test.getFittest(solution).fitness(solution) >= 30 && test.populationSize == POPULATION_SIZE)
			test.setPopulation(50);

	}

	Mat temp = test.getFittest(solution).image;

	string dupa = "";
	dupa += to_string(test.getFittest(solution).fitness(solution));
	dupa += "%";
	const char* ptr = dupa.c_str();
	cout << ptr << endl;

	cout << "Time spent on add: " << evolvePop.timeSort << "s" << endl;
	//cout << "Time spent on filling: " << evolvePop.timeFill << "s" << endl;
	cout << "Time spent on crossing: " << evolvePop.timeCross << "s" << endl;
	cout << "Time spent on mutation: " << evolvePop.timeMutate << "s" << endl;

	putText(temp, ptr, cvPoint(30, 30),	FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
	imshow("Image", temp);

	waitKey(1);
	cin.get();
	return 0;
}
