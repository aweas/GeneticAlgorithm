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
	srand(935);
	int sum = 0;
	double timer00 = 0;
	std::clock_t time00;
	std::clock_t time90;
	double timer90 = 0;
	bool start90 = true;
	std::clock_t time95;
	double timer95 = 0;
	bool start95 = true;
	std::clock_t time98;
	double timer98 = 0;
	bool start98 = true;
	
	int generationsCount = 0;

	Fitness * solution;
	Population * test;
	Evolve * evolution;

	//Test variables
	int eliteNumbers[4] = { 3,3,3,3 };
	int populationNumbers[2] = { 10, 10 };
	int repetitions = 1;

	for (int e = 0; e < 1;e++)
	{
		for (int p = 0; p < 1; p++)
		{
			for (int j=0; j < repetitions; j++)
			{
				srand(rand());

				time00 = std::clock();
				solution = new Fitness(generateGenes());
				test = new Population(populationNumbers[p], true);
				evolution = new Evolve(*test, *solution, 3);


				for (generationsCount; (*test).getFittest(*solution).fitness(*solution) != SOLUTION_LENGTH; generationsCount++)
				{
					(*evolution).EvolvePop();
					if (generationsCount % (50 / (*test).populationSize) == 0)
						printf("#%i Fitness: %i\n", generationsCount, (*test).getFittest(*solution).fitness(*solution));
					if ((*test).getFittest(*solution).fitness(*solution)>=90 && start90)
					{
						time90 = clock();
						start90 = false;
						(*test).setPopulation(50);
					}
					if ((*test).getFittest(*solution).fitness(*solution) >= 95 && start95)
					{
						time95 = clock();
						start95 = false;
					}
					if ((*test).getFittest(*solution).fitness(*solution)>=98 && start98)
					{
						time98 = clock();
						start98 = false;
					}
				}

				timer00 += (std::clock() - time00) / (double)CLOCKS_PER_SEC;
				timer90 += (std::clock() - time90) / (double)CLOCKS_PER_SEC;
				timer95 += (std::clock() - time95) / (double)CLOCKS_PER_SEC;
				timer98 += (std::clock() - time98) / (double)CLOCKS_PER_SEC;

				time00 = clock();
				start90 = true;
				start95 = true;
				start98 = true;

				if (j % 1 == 0)
					printf("\rRepetitions: %i", j);
				delete solution;
				delete test;
				delete evolution;
			}
			float average = sum / repetitions;
			timer00 /= repetitions;
			timer90 /= repetitions;
			timer95 /= repetitions;
			timer98 /= repetitions;
			
			printf("\rRepetitions: %i\nPopulation: %i\n", repetitions, populationNumbers[p]);
			printf("Average of generations needed: %i\n", (generationsCount-1)/repetitions);
			printf("Time needed: %4.1f s\n", timer00);
			printf("Time from fitness 90: %4.1f s\n", timer90);
			printf("Time from fitness 95: %4.1f s\n", timer95);
			printf("Time from fitness 98: %4.1f s\n\n", timer98);
			
			generationsCount = 0;

			sum = 0;
		}
	}

	cin.get();
}

string generateGenes()
{
	string solutionGenes;
	for (int i = 0;i < SOLUTION_LENGTH;i++)
		solutionGenes += (char)(rand() % 2 + 48);
	return solutionGenes;
}