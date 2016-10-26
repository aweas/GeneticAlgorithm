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

	int i = 0;
	for (i;i < 40, test.getFittest(solution).fitness(solution)!=64;i++)
	{
		evolution.EvolvePop();
		cout << endl << "Fittest: " <<test.getFittest(solution).fitness(solution);
	}
	cout << endl<<"Finished in: " << i << " generations";
	cin.get();
}

