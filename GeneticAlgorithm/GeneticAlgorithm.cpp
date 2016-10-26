#include "stdafx.h"
#include "Population.h"
#include "Evolve.h"

#include <iostream>

int main()
{
	srand(10);
	Fitness solution("1001101011100010110010101001100110011100101111000011010110001111");
	Population test(10,true);

	for (int i = 0;i < 10;i++)
		cout << test.getSpecimen(i).getGenes() << " F: " << test.getSpecimen(i).fitness(solution)<<endl;

	cout << endl << endl;

	Evolve evolution;
	evolution.EvolvePop(test, solution);

	for (int i = 0;i < 10;i++)
		cout << test.getSpecimen(i).getGenes() << " F: " << test.getSpecimen(i).fitness(solution) << endl;

	cin.get();
}

