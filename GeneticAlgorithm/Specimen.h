#pragma once
#define SPECIMEN_H
#ifdef SPECIMEN_H

#define SOLUTION_LENGTH 911 

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
	int circlesNum = atoi(temp.c_str());
	temp = "";

	for (int i = 0;i < 3;i++, currentGene++)
		temp += genes[currentGene];
	int bR = atoi(temp.c_str());
	temp = "";
	for (int i = 0;i < 3;i++, currentGene++)
		temp += genes[currentGene];
	int bG = atoi(temp.c_str());
	temp = "";
	for (int i = 0;i < 3;i++, currentGene++)
		temp += genes[currentGene];
	int bB= atoi(temp.c_str());
	temp = "";
	image.setTo(cv::Scalar(255, 255, 255));

	for (int j = 0;j < circlesNum;j++)
	{
		for (int i = 0;i < 3;i++, currentGene++)
			temp += genes[currentGene];
		int coordX = atoi(temp.c_str());
		temp = "";

		for (int i = 0;i < 3;i++, currentGene++)
			temp += genes[currentGene];
		int coordY = atoi(temp.c_str());
		temp = "";

		for (int i = 0;i < 3;i++, currentGene++)
			temp += genes[currentGene];
		int radius = atoi(temp.c_str());
		temp = "";

		int R=bR, G=bG, B=bB;
		
		for (int i = 0;i < 3;i++, currentGene++)
			temp += genes[currentGene];
		R = atoi(temp.c_str());
		temp = "";
		for (int i = 0;i < 3;i++, currentGene++)
			temp += genes[currentGene];
		G = atoi(temp.c_str());
		temp = "";
		for (int i = 0;i < 3;i++, currentGene++)
			temp += genes[currentGene];
		B = atoi(temp.c_str());
		temp = "";

		try
		{
			circle(image, Point(coordX, coordY), radius, Scalar(R, G, B), -1, 8);
		}
		catch (Exception e)
		{
			cout << e.msg << endl;
			cout << radius << " " << R << " " << G << " " << B << " " << endl;
		}
	}

}

void Specimen::generate()
{
	int geneNum=2;
	int temp = rand() % 50;
	genes[0] = temp / 10 + 48;
	genes[1] = temp % 10 + 48;

	for (int i = 0;i < 3;i++, geneNum+=3)
	{
		int temp = rand() % 256;
		genes[geneNum] = temp / 100 + 48;
		genes[geneNum+1] = (temp / 10)%10 + 48;
		genes[geneNum + 2] = temp % 10 + 48;
	}
	for (int i = 0; i < 50; i++)
	{
		//X and Y coordinates
		int temp = rand() % 256;
		genes[geneNum] = temp / 100 + 48;
		genes[geneNum + 1] = (temp / 10) % 10 + 48;
		genes[geneNum + 2] = temp % 10 + 48;
		geneNum += 3;
		temp = rand() % 256;
		genes[geneNum] = temp / 100 + 48;
		genes[geneNum + 1] = (temp / 10) % 10 + 48;
		genes[geneNum + 2] = temp % 10 + 48;
		geneNum += 3;

		//Radius
		temp = rand() % 64;
		genes[geneNum] = temp / 100 + 48;
		genes[geneNum + 1] = (temp / 10) % 10 + 48;
		genes[geneNum + 2] = temp % 10 + 48;
		geneNum += 3;

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
	//cout << sizeof(genes)/sizeof(char) << endl;
}

double Specimen::fitness(Fitness solution)
{
	if (fit == -1)
	{
		double sum = 0;
		image = Mat::zeros(256, 256, CV_8UC3);
		showCircle(genes);

		similarity[0] = solution.getSim(image, 0);
		fit = similarity[0];

		/*if(fit>38)
			fit += (solution.getSim(image, 1)/2);*/
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