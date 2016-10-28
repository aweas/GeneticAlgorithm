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
		int solutionLength;
		Fitness(string input);
		int getFitness(string specimenGenes);
};

Fitness::Fitness(string input)
{
	solution = input;
	solutionLength = solution.length();
	cout << "Solution: " << input << endl;
}

int Fitness::getFitness(string specimenGenes)
{
	int fitness = 0;
	for (int i = 0;i < specimenGenes.length() ;i++)
	{
		if (specimenGenes[i] == solution[i])
			fitness++;
	}
	return fitness;
}
#endif