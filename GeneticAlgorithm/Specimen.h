#pragma once
#define SPECIMEN_H
#ifdef SPECIMEN_H

#define SOLUTION_LENGTH 2515 

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
	int circlesNum = (SOLUTION_LENGTH-24) / 47;
	int currentGene = 0;

	string temp = "";
	for (int i = 0;i < 8;i++, currentGene++)
		temp += genes[currentGene];
	int R = BinToDec(temp);
	temp = "";
	for (int i = 0;i < 8;i++, currentGene++)
		temp += genes[currentGene];
	int G = BinToDec(temp);
	temp = "";
	for (int i = 0;i < 8;i++, currentGene++)
		temp += genes[currentGene];
	int B= BinToDec(temp);
	temp = "";

	image.setTo(cv::Scalar(R, G, B));
	for (int j = 0;j < circlesNum;j++)
	{
		for (int i = 0;i < 9;i++, currentGene++)
			temp += genes[currentGene];
		int coordX = BinToDec(temp);
		temp = "";

		for (int i = 0;i < 9;i++, currentGene++)
			temp += genes[currentGene];
		int coordY = BinToDec(temp);
		temp = "";

		for (int i = 0;i < 5;i++, currentGene++)
			temp += genes[currentGene];
		int radius = BinToDec(temp);
		temp = "";

		for (int i = 0;i < 8;i++, currentGene++)
			temp += genes[currentGene];
		int R = BinToDec(temp);
		temp = "";
		for (int i = 0;i < 8;i++, currentGene++)
			temp += genes[currentGene];
		int G = BinToDec(temp);
		temp = "";
		for (int i = 0;i < 8;i++, currentGene++)
			temp += genes[currentGene];
		int B = BinToDec(temp);
		temp = "";

		//cout << coordX << " : " << coordY << "   " << radius << endl;

		circle(image, Point(coordX, coordY), radius, Scalar(R, G, B), -1, 8);
	}

}

void Specimen::generate()
{
	for (int i = 0;i < genesLength;i++)
	{
		if (rand() % 2 == 0)
			genes[i] = '0';
		else
			genes[i] = '1';
	}
}

double Specimen::fitness(Fitness solution)
{
	if (fit == -1)
	{
		image = Mat::zeros(511, 511, CV_8UC3);
		showCircle(genes);
		fit = solution.getFitness(image);
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