#pragma once
#define SPECIMEN_H
#ifdef SPECIMEN_H

#define SOLUTION_LENGTH 100 

#include <string>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include "Fitness.h"

using namespace std;

class Specimen
{
	private:
		char genes[SOLUTION_LENGTH];
		int fit=-1;

	public:
		int genesLength = SOLUTION_LENGTH;
		void generate();
		int fitness(Fitness solution);
		string getGenes();
		void setGenes(string data);
};

void Specimen::generate()
{
	for (int i = 0;i < genesLength;i++)
		genes[i]= (char)(rand() % 2 + 48);
}

int Specimen::fitness(Fitness solution)
{
	if (fit == -1)
	{
		string tempGenes;
		for (int i = 0;i < genesLength;i++)
			tempGenes += genes[i];
		fit = solution.getFitness(tempGenes);
	}
	return fit;
}

string Specimen::getGenes()
{
	string temp="";
	for (int i = 0; i<genesLength; i++)
		temp += genes[i];
	return temp;
}

void Specimen::setGenes(string data)
{
	for (int i = 0;i < data.length();i++)
		genes[i] = data[i];
}
#endif