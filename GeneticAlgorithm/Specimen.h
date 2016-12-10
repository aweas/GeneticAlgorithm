#pragma once
#define SPECIMEN_H
#ifdef SPECIMEN_H

#define SOLUTION_LENGTH 1352 

#include <string>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include "Fitness.h"

using namespace std;
using namespace cv;

class Specimen
{
	private:
		char genes[SOLUTION_LENGTH];
		double fit=-1;

	public:
		double similarity[3];
		double genesLength = SOLUTION_LENGTH;
		void generate();
		double fitness(Fitness solution);
		string getGenes();
		string getGenes(int i);
		Mat image;
		void setGenes(string data);
		void showCircle(char genes[]);
		int BinToDec(string number);
};

void Specimen::showCircle(char genes[])
{
	int currentGene = 0;

	string temp = "";
	for (int i = 0;i < 2;i++, currentGene++)
		temp += genes[currentGene];
	int circlesNum = atoi(temp.c_str()) ;
	temp = "";

	image.setTo(cv::Scalar(255, 255, 255));

	for (int j = 0;j < 50;j++)
	{
		//cout << j <<" "<<circlesNum[0]<<endl;
		Point trianglePoints[1][3];

		for (int k = 0;k < 3;k++)
		{
			for (int i = 0;i < 3;i++, currentGene++)
				temp += genes[currentGene];
			int coordX = atoi(temp.c_str());
			temp = "";

			for (int i = 0;i < 3;i++, currentGene++)
				temp += genes[currentGene];
			int coordY = atoi(temp.c_str());
			temp = "";

			trianglePoints[0][k] = Point(coordX, coordY);
		}

		for (int i = 0;i < 3;i++, currentGene++)
			temp += genes[currentGene];
		int radius = atoi(temp.c_str());
		temp = "";
		
		for (int i = 0;i < 3;i++, currentGene++)
			temp += genes[currentGene];
		int R = atoi(temp.c_str());
		temp = "";
		for (int i = 0;i < 3;i++, currentGene++)
			temp += genes[currentGene];
		int G = atoi(temp.c_str());
		temp = "";
		for (int i = 0;i < 3;i++, currentGene++)
			temp += genes[currentGene];
		int B = atoi(temp.c_str());
		temp = "";

		//circle(image, Point(coordX, coordY), radius, Scalar(R, G, B), -1, 8);
		Mat overlay;
		image.copyTo(overlay);
		const Point* ppt[1] = { trianglePoints[0] };
		int num[] = { 3 };

		fillPoly(overlay, ppt, num, 1, Scalar(R, G, B), 8);
		addWeighted(overlay, 0.8, image, 0.2, 0, image);
	}

}

void Specimen::generate()
{
	int geneNum=2;
	int temp = rand() % 50;
	genes[0] = temp / 10 + 48;
	genes[1] = temp % 10 + 48;
	
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0;j < 3;j++)
		{
			//X and Y coordinates
			int temp = rand() % 128;
			genes[geneNum] = temp / 100 + 48;
			genes[geneNum + 1] = (temp / 10) % 10 + 48;
			genes[geneNum + 2] = temp % 10 + 48;
			geneNum += 3;
			temp = rand() % 128;
			genes[geneNum] = temp / 100 + 48;
			genes[geneNum + 1] = (temp / 10) % 10 + 48;
			genes[geneNum + 2] = temp % 10 + 48;
			geneNum += 3;
		}

		//Color
		temp = rand() % 256;
		genes[geneNum] = temp / 100 + 48;
		genes[geneNum + 1] = (temp / 10) % 10 + 48;
		genes[geneNum + 2] = temp % 10 + 48;
		geneNum += 3;
		temp = rand() % 256;
		genes[geneNum] = temp / 100 + 48;
		genes[geneNum + 1] = (temp / 10) % 10 + 48;
		genes[geneNum + 2] = temp % 10 + 48;
		geneNum += 3;
		temp = rand() % 256;
		genes[geneNum] = temp / 100 + 48;
		genes[geneNum + 1] = (temp / 10) % 10 + 48;
		genes[geneNum + 2] = temp % 10 + 48;
		geneNum += 3;
	}
}

double Specimen::fitness(Fitness solution)
{
	if (fit == -1)
	{
		double sum = 0;
		image = Mat::zeros(128, 128, CV_8UC3);
		showCircle(genes);
		similarity[0] = solution.getSim(image, 0);
		fit = similarity[0]/2;

		if(fit>42.5)
			fit = 42.5+(solution.getSim(image, 1)/2);
	}

	return fit;
}

string Specimen::getGenes()
{
	string temp(genes);
	return temp;
}

string Specimen::getGenes(int i)
{
	string temp="";
	temp += genes[i];
	return temp;
}

void Specimen::setGenes(string data)
{
	for (int i = 0;i < data.length();i++)
		genes[i] = data[i];
}

int Specimen::BinToDec(string number)
{
	int result = 0, pow = 1;
	for (int i = number.length() - 1; i >= 0; --i, pow <<= 1)
		result += (number[i] - '0') * pow;

	return result;
}
#endif