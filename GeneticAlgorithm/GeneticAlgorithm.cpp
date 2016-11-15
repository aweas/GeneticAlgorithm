
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
#define SOLUTION_LENGTH 911

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	srand(time(NULL));

	Population test(50, true);
	Fitness solution;
	Evolve evolvePop(test, solution, ELITES_NUMBER);
	int generationsCount = 0;

	bool cont = true;
	int last=0;

	for (int i = 0;test.getFittest(solution).fitness(solution)<100 && !_kbhit();i++, generationsCount++)
	{
		evolvePop.EvolvePop();
		int fitness = test.getFittest(solution).fitness(solution);

		if (generationsCount % (50 / test.populationSize) == 0)
			printf("#%i Fitness: %f%c\n", generationsCount, test.getFittest(solution).fitness(solution), '%');

		if (fitness >= 60 && test.populationSize == POPULATION_SIZE)
			test.setPopulation(50);
	
		if (fitness>last)
		{
			Mat temp = test.getFittest(solution).image;
			string name = "Similarity"+ to_string(fitness)+".jpg";
			string simAll = ""; simAll += to_string(test.getFittest(solution).fitness(solution)); simAll += "%";
			const char* ptr = simAll.c_str();
			string simOne = "Method 1: "; simOne += to_string(test.getFittest(solution).similarity[0]); simOne += "%";
			const char* ptr1 = simOne.c_str();
			//string simTwo = "Method 2: "; simTwo += to_string(test.getFittest(solution).similarity[1]); simTwo += "%";
			//const char* ptr2 = simTwo.c_str();
			//string simThree = "Method 3: "; simThree += to_string(test.getFittest(solution).similarity[2]); simThree += "%";
			//const char* ptr3 = simThree.c_str();
			//cout << ptr << endl;

			putText(temp, ptr, cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);
			putText(temp, ptr1, cvPoint(30, 60), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);
			//putText(temp, ptr2, cvPoint(30, 90), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);
			//putText(temp, ptr3,cvPoint(30, 120), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);

			imwrite(name.c_str(), temp);
			last = fitness + 4;
		}
	}
	Mat temp = test.getFittest(solution).image;

	string dupa = ""; dupa += to_string(test.getFittest(solution).fitness(solution)); dupa += "%";
	const char* ptr = dupa.c_str();
	string simOne = "Method 1: "; simOne += to_string(test.getFittest(solution).similarity[0]); simOne += "%";
	const char* ptr1 = simOne.c_str();
	//string simTwo = "Method 2: "; simTwo += to_string(test.getFittest(solution).similarity[1]); simTwo += "%";
	//const char* ptr2 = simTwo.c_str();
	//string simThree = "Method 3: "; simThree += to_string(test.getFittest(solution).similarity[2]); simThree += "%";
	//const char* ptr3 = simThree.c_str();
	cout << ptr << endl;

	putText(temp, ptr, cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);
	putText(temp, ptr1, cvPoint(30, 60), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);
	//putText(temp, ptr2, cvPoint(30, 90), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);
	//putText(temp, ptr3, cvPoint(30, 120), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);

	imshow("Image", temp);

	waitKey(1);
	cin.get();
	return 0;
}
