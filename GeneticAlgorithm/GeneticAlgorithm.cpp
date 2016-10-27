#include "stdafx.h"
#include "Population.h"
#include "Evolve.h"

#include <iostream>
#include <cstdio>
#include <ctime>

int main()
{
	int j = 0;
	int sum = 0;
	std::clock_t start;
	start = std::clock();

	Fitness * solution;
	Population * test;
	Evolve * evolution;

	int elite[4] = { 5,4,3,2 };
	int pop[2] = { 10,50 };
	for (int e = 0;e < 4;e++)
	{
		for (int p = 0;p < 2;p++)
		{
			for (j; j < 2; j++)
			{
				srand(time(NULL));

				solution = new Fitness("1001101011100010110010101001100110011100101111000011010110001111");
				test = new Population(pop[p], true);
				evolution = new Evolve(*test, *solution, elite[e]);

				int i = 0;
				for (i; (*test).getFittest(*solution).fitness(*solution) != 64; i++)
					(*evolution).EvolvePop();

				sum += i;

				delete solution;
				delete test;
				delete evolution;
			}
			float average = sum / 2;
			double timer = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			
			sum = 0;
			start = clock();

			printf("Elites: %i, Population: %i\n", elite[e], pop[p]);
			printf("Average of generations needed: %5.2f\n", average);
			printf("Time needed: %4.1f s\n\n", timer);
			j = 0;
		}
	}

	cin.get();
}

