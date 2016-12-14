
#include "stdafx.h"
#include "Population.h"
#include "Evolve.h"

#include <iostream>
#include <sstream>
#include <cstdio>
#include <ctime>
#include <conio.h>
#include <numeric>
#include <vector>

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
Mat plotGraph(std::vector<T>& vals, int YRange[2], int value);

int main(int argc, char** argv)
{
	srand(time(NULL));

	Population test(POPULATION_SIZE, true);
	cout << "1. Population created" << endl;
	Fitness solution;

	Evolve evolvePop(test, solution, ELITES_NUMBER);
	int generationsCount = 0;

	bool cont = true;
	float threshold = test.getFittest(solution).fitness(solution);

	solution.Initialize(test.getFittest(solution).image);

	float last = 0.0;
	bool color = false;
	vector<float> data;

	for (int i = 0;/*i<300 &&*/ !_kbhit();i++, generationsCount++)
	{
		evolvePop.EvolvePop();
		
		float fitness = test.getFittest(solution).fitness(solution);

		if (generationsCount % 5 == 0)
		{
			printf("\r#%i Fitness: %f%c (%f/%f)", generationsCount, fitness, '%', test.getFittest(solution).similarity[0], test.getFittest(solution).similarity[1]);
		}
		//else if (fitness > last)
		//{
		//	printf("\r#%i Fitness: %f%c\n", generationsCount, fitness, '%');
		//	last = fitness;
		//}

		if (fitness > threshold)
		{
			Mat temp = test.getFittest(solution).image;
			string name = "Similarity" + to_string(fitness) + ".jpg";
			string simOne = "G: " + to_string(generationsCount);

			putText(temp, simOne.c_str(), cvPoint(0, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);
			imwrite(name.c_str(), temp);
			threshold = fitness + 0.25;
		}

		data.push_back(fitness);
		imshow("Image", test.getFittest(solution).image);
		imshow("Image Canny", test.getFittest(solution).imageCanny);
		imshow("Source", solution.source);
		imshow("Source Canny", solution.canny);
		waitKey(1);
	}
	Mat temp = test.getFittest(solution).image;

	string dupa = to_string(test.getFittest(solution).fitness(solution)) + ".jpg";
	const char* ptr = dupa.c_str();
	string simOne = "G: "; simOne += to_string(generationsCount);
	const char* ptr1 = simOne.c_str();
	string simTwo = "C: "; simTwo += test.getFittest(solution).getGenes()[0]; simTwo += test.getFittest(solution).getGenes()[1];
	const char* ptr2 = simTwo.c_str();

	putText(temp, ptr, cvPoint(0, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);
	putText(temp, ptr1, cvPoint(0, 60), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);
	putText(temp, ptr2, cvPoint(0, 90), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);

	resize(temp, temp, Size(128, 128));
	imshow("Image", temp);

	imwrite(dupa.c_str(), temp);

	int range[2] = { 0,200 };

	cv::Mat lineGraph = plotGraph(data, range, test.getFittest(solution).fitness(solution));
	
	imshow("Graph", lineGraph);
	string name = "Graph " + to_string(test.getFittest(solution).fitness(solution)) + ".jpg";
	imwrite(name.c_str(), lineGraph);
	waitKey(0);
	return 0;
}

template <typename T>
cv::Mat plotGraph(std::vector<T>& vals, int YRange[2], int value)
{
	auto it = minmax_element(vals.begin(), vals.end());
	float scale = ceil(abs(vals[0])-abs(vals[vals.size()-1]));
	float bias = *it.first;
	int rows = YRange[1] - YRange[0] + 1;
	cv::Mat image = Mat::zeros(rows, vals.size(), CV_8UC3);
	image.setTo(0);

	for (int i = 0; i < (int)vals.size() - 1; i++)
		cv::line(image, cv::Point(i, (abs(vals[i]) - abs(vals[vals.size()-1]))/scale*YRange[1]), cv::Point(i + 1, (abs(vals[i+1]) - abs(vals[vals.size()-1]))/scale*YRange[1]), Scalar(255, 0, 0), 1);

	string simOne = to_string(value);

	putText(image, simOne.c_str(), cvPoint(10, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 255, 0), 1, CV_AA);

	return image;
}