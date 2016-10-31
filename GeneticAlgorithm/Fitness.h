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
	//Branch prediction workaround (http://stackoverflow.com/questions/11227809/why-is-it-faster-to-process-a-sorted-array-than-an-unsorted-array?rq=1)
	for (int i = 0;i < specimenGenes.length();i++)
	{
		int t = (specimenGenes[i] - solution[i]);
		fitness += abs(t);
	}
	fitness = specimenGenes.length() - fitness;
	return fitness;
}
#endif