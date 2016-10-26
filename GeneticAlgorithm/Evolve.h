#pragma once
#define EVOLVE_H
#ifdef EVOLVE_H

#include "Population.h"

class Evolve
{
	private:
		Population * population;
		Fitness * solution;
		void sort();
		void fill();
		void crossover();
		Specimen select(int offset);
		Specimen mutate();
	public:
		Evolve(Population& pop, Fitness& sol);
		void EvolvePop();
};

Evolve::Evolve(Population& pop, Fitness& sol)
{
	population = &pop;
	solution = &sol;
}

void Evolve::sort()
{
	for (int i = 0;i<(*population).populationSize;i++)
		for (int j = 0;j < (*population).populationSize - 1;j++)
			if ((*population).getSpecimen(j).fitness(*solution) < (*population).getSpecimen(j + 1).fitness(*solution))
				(*population).swap(j, j + 1);
}

void Evolve::fill()
{
	Specimen best[5];
	Specimen temp;
	int counter=0;

	for (int i = 0;i < 5;i++)
		best[i]=(*population).getSpecimen(i);

	for (int i = 0;i < (*population).populationSize;i++)
	{
		temp.generate();
		(*population).addSpecimen(temp.getGenes(),i);
	}

	for (int i = 0;i < 5; i++)
	{
		int limit = (counter + (*population).populationSize / (3 * (i + 1)));
		for (int j = counter; j < limit ; j++)
		{
			(*population).addSpecimen(best[i].getGenes(), j);
			counter++;
		}
	}
}

Specimen Evolve::select(int offset)
{
	int pick = rand() % ((*population).populationSize-offset)+offset;
	return (*population).getSpecimen(pick);
}

void Evolve::crossover()
{
	for (int j = 0;j < (*population).populationSize; j++)
	{
		Specimen father = select(j);
		Specimen mother = select(j);
		string genes;
		for (int i = 0;i < father.getGenes().length(); i++)
			if (rand() % 2 == 0)
				genes += father.getGenes()[i];
			else
				genes += mother.getGenes()[i];
		(*population).addSpecimen(genes, j);
	}

}

void Evolve::EvolvePop()
{
	sort();
	fill();
	crossover();
	//mutate();
}



#endif