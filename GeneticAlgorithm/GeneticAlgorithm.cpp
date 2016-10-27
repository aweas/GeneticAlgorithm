#include "stdafx.h"
#include "Population.h"
#include "Evolve.h"

#include <iostream>
#include <cstdio>
#include <ctime>

#define POPULATION_SIZE 50
#define ELITES_NUMBER 3

string generateGenes();

int main()
{
	srand(time(NULL));

	int generationsCount = 0;
	Fitness * solution;
	Population * test;
	Evolve * evolution;

	solution = new Fitness(generateGenes());
	test = new Population(POPULATION_SIZE, true);
	evolution = new Evolve(*test, *solution, ELITES_NUMBER);

	printf("Elites: %i, Population: %i\n", ELITES_NUMBER, POPULATION_SIZE);

	for (generationsCount; (*test).getFittest(*solution).fitness(*solution) != 64; generationsCount++)
	{
		(*evolution).EvolvePop();
		printf("#%i Fitness: %i\n", generationsCount, (*test).getFittest(*solution).fitness(*solution));
	}
	printf("\nSolution found in %i generations", generationsCount-1);
	cin.get();
}

string generateGenes()
{
	string solutionGenes;
	for (int i = 0;i < 64;i++)
		if (rand() % 2 == 0)
			solutionGenes += '0';
		else
			solutionGenes += '1';
	return solutionGenes;
}