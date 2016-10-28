#include "stdafx.h"
#include "Population.h"
#include "Evolve.h"

#include <iostream>
#include <cstdio>
#include <ctime>

#define POPULATION_SIZE 50
#define ELITES_NUMBER 3
#define SOLUTION_LENGTH 100

string generateGenes();

int main()
{
	srand(493);
	int j = 0;
	int sum = 0;
	std::clock_t start;
	int generationsCount = 0;

	Fitness * solution;
	Population * test;
	Evolve * evolution;

	//Test variables
	int eliteNumbers[4] = { 3,3,3,3 };
	int populationNumbers[2] = { POPULATION_SIZE,50 };
	int repetitions = 1;

	for (int e = 0;e < 1;e++)
	{
		for (int p = 0; p < 1; p++)
		{
			for (j; j < repetitions; j++)
			{
				//srand(rand());

				start = std::clock();
				solution = new Fitness(generateGenes());
				test = new Population(populationNumbers[p], true);
				evolution = new Evolve(*test, *solution, eliteNumbers[e]);


				for (generationsCount; (*test).getFittest(*solution).fitness(*solution) != SOLUTION_LENGTH; generationsCount++)
				{
					(*evolution).EvolvePop();
					if (generationsCount % (50 / POPULATION_SIZE ) == 0)
						printf("#%i Fitness: %i\n", generationsCount, (*test).getFittest(*solution).fitness(*solution));
				}

				if (j % 10 == 0)
					printf("\rRepetitions: %i", j);
				delete solution;
				delete test;
				delete evolution;
			}
			float average = sum / repetitions;
			double timer = (std::clock() - start) / (double)CLOCKS_PER_SEC;

			sum = 0;
			start = clock();

			printf("\rElites: %i, Population: %i\n", eliteNumbers[e], populationNumbers[p]);
			printf("Average of generations needed: %i\n", generationsCount-1);
			printf("Time needed: %4.1f s\n\n", timer);
			//printf("Successful mutations: %i, success rate: %i%", successMut, rateMut);
			//printf("\nSuccessful crossovers: %i, success rate: %i%\n\n", successCross, rateCross);
			j = 0;
		}
	}

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