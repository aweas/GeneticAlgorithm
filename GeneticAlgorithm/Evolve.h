#pragma once
#define EVOLVE_H
#ifdef EVOLVE_H

#include "Population.h"

class Evolve
{
	public:
		Population EvolvePop(Population pop, Fitness solution);
};

Population Evolve::EvolvePop(Population pop, Fitness solution)
{
	for(int i=0;i<pop.populationSize;i++)
		for (int j = 0;j < pop.populationSize-1;j++)
			if (pop.getSpecimen(j).fitness(solution) < pop.getSpecimen(j + 1).fitness(solution))
				pop.swap(j, j + 1);
	return pop;
}

#endif

