#pragma once
#define FITNESS_H
#ifdef FITNESS_H

#include <string>
using namespace std;

class Fitness
{
	private:
		string solution;

	public:
		Fitness(string input);
		int getFitness(string specimenGenes);
};

Fitness::Fitness(string input)
{
	solution = input;
}

int Fitness::getFitness(string specimenGenes)
{
	int fitness = 0;
	for (int i = 0;i < 64;i++)
	{
		if (specimenGenes[i] == solution[i])
			fitness++;
	}
	return fitness;
}
#endif