#include "stdafx.h"
#include "Population.h"
#include "Evolve.h"

#include <iostream>

int main()
{
	srand(time(NULL));
	Fitness solution("1001101011100010110010101001100110011100101111000011010110001111");
	Population test(50,true);

	Evolve evolution(test,solution);

	for (int i = 0;i < 40;i++)
	{
		evolution.EvolvePop();
		cout << endl << "Fittest: " << test.getFittest(solution).getGenes() <<": "<<test.getFittest(solution).fitness(solution);
	}
	cin.get();
}

