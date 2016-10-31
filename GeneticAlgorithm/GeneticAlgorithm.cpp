#include "stdafx.h"
#include "Population.h"
#include "Evolve.h"

#include <iostream>
#include <cstdio>
#include <ctime>

#define POPULATION_SIZE 10
#define ELITES_NUMBER 3
#define SOLUTION_LENGTH 100

string generateGenes();

int main()
{
	srand(time(NULL));

	int generationsCount = 0;
	Fitness * solution;
	Population * test;
	Evolve * evolution;
	std::clock_t start;


	solution = new Fitness(generateGenes());
	test = new Population(POPULATION_SIZE, true);
	evolution = new Evolve(*test, *solution, ELITES_NUMBER);

	printf("Elites: %i, Population: %i\n", ELITES_NUMBER, POPULATION_SIZE);
	start = clock();

	for (generationsCount; (*test).getFittest(*solution).fitness(*solution) != (*solution).solutionLength ; generationsCount++)
	{
		(*evolution).EvolvePop();
		if(generationsCount% (50/(*test).populationSize)==0)
			printf("#%i Fitness: %i\n", generationsCount, (*test).getFittest(*solution).fitness(*solution));
		if ((*test).getFittest(*solution).fitness(*solution) >= (0.95*SOLUTION_LENGTH) && (*test).populationSize == POPULATION_SIZE)
			(*test).setPopulation(50);

	}

	double timer = (clock() - start) / (double)CLOCKS_PER_SEC;

	printf("\nSolution found in %i generations\nTime: %5.3f seconds", generationsCount-1,timer);
	cin.get();
}

string generateGenes()
{
	string solutionGenes;
	for (int i = 0;i < SOLUTION_LENGTH;i++)
		if (rand() % 2 == 0)
			solutionGenes += '0';
		else
			solutionGenes += '1';
	return solutionGenes;
}