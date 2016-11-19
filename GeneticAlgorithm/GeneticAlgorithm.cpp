
#include "stdafx.h"
#include "Population.h"
#include "Evolve.h"

#include <iostream>
#include <sstream>
#include <cstdio>
#include <ctime>
#include <conio.h>
#include <numeric>

#include <opencv\cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"

#define POPULATION_SIZE 100
#define ELITES_NUMBER 3
#define SOLUTION_LENGTH 911

using namespace cv;
using namespace std;

template <typename T>
Mat plotGraph(std::vector<T>& vals, int YRange[2]);

int main(int argc, char** argv)
{
	srand(time(NULL));

	Population test(POPULATION_SIZE, true);
	Fitness solution;
	Evolve evolvePop(test, solution, ELITES_NUMBER);
	int generationsCount = 0;

	bool cont = true;
	float threshold=0.0;
	float last = 0.0;
	vector<float> data;

	for (int i = 0;test.getFittest(solution).fitness(solution)<100 && test.getFittest(solution).fitness(solution)>0 && !_kbhit();i++, generationsCount++)
	{
		evolvePop.EvolvePop();

		float fitness = test.getFittest(solution).fitness(solution);

		if (fitness == last && generationsCount % 5 == 0)
			printf("\r#%i Fitness: %f%c", generationsCount, fitness, '%');
		else if (fitness > last)
		{
			printf("\r#%i Fitness: %f%c\n", generationsCount, fitness, '%');
			last = fitness;
		}


		if (fitness >= 85 && test.populationSize == POPULATION_SIZE)
		{
			printf("------------- COLOR ADJUSTING -------------\n");
			test.setPopulation(1000);
			last = 0.0;
		}
		
		if (generationsCount % 10 == 0)
			data.push_back(fitness);

		if (fitness>threshold)
		{
			Mat temp = test.getFittest(solution).image;
			string name = "Similarity"+ to_string(fitness)+".jpg";
			imwrite(name.c_str(), temp);
			threshold = fitness + 0.5;
		}
	}
	Mat temp = test.getFittest(solution).image;

	string dupa = ""; dupa += to_string(test.getFittest(solution).fitness(solution)); dupa += "%";
	const char* ptr = dupa.c_str();
	string simOne = "Method 1: "; simOne += to_string(test.getFittest(solution).similarity[0]); simOne += "%";
	const char* ptr1 = simOne.c_str();
	string simTwo = "Circles num: "; simTwo += test.getFittest(solution).getGenes()[0]; simTwo += test.getFittest(solution).getGenes()[1];
	const char* ptr2 = simTwo.c_str();
	cout << endl<< ptr << endl;

	putText(temp, ptr, cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);
	putText(temp, ptr1, cvPoint(30, 60), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);
	putText(temp, ptr2, cvPoint(30, 90), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);

	imshow("Image", temp);

	iota(data.begin(), data.end(), 0);
	int range[2] = { 0,100 };

	Mat graph = plotGraph(data, range);
	imshow("Graph", graph);

	waitKey(1);
	cin.get();
	return 0;
}

template <typename T>
Mat plotGraph(std::vector<T>& vals, int YRange[2])
{

	auto it = minmax_element(vals.begin(), vals.end());
	float scale = 1. / ceil(*it.second - *it.first);
	float bias = *it.first;
	int rows = YRange[1] - YRange[0] + 1;
	cv::Mat image = Mat::zeros(rows, vals.size(), CV_8UC3);
	image.setTo(0);
	for (int i = 0; i < (int)vals.size() - 1; i++)
	{
		cv::line(image, cv::Point(i, rows - 1 - (vals[i] - bias)*scale*YRange[1]), cv::Point(i + 1, rows - 1 - (vals[i + 1] - bias)*scale*YRange[1]), Scalar(255, 0, 0), 1);
	}

	imwrite("Graph", image);
	return image;
}