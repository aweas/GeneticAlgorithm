#pragma once
#define POPULATION_H
#ifdef POPULATION_H

#include <vector>
#include <iostream>
#include "Specimen.h"

using namespace std;

class Population
{
	private:
		Specimen * specimen;

	public: 
		int populationSize;
		Population(int size, bool init);
		Specimen getSpecimen(int index);
		Specimen getFittest(Fitness solution);
		void addSpecimen(string genes, int index);
		void swap(int indexfrom, int indexto);
};



Population::Population(int size, bool init)
{
	populationSize = size;
	specimen = new Specimen[size];
	if (init)
	{
		for (int i = 0;i < size;i++)
		{
			Specimen tempSpecimen;
			tempSpecimen.generate();
			specimen[i] = tempSpecimen;
		}
	}
}

Specimen Population::getSpecimen(int index)
{
	return specimen[index];
}

Specimen Population::getFittest(Fitness solution)
{
	Specimen fittest = specimen[0];
	for (int i = 1; i < populationSize; i++)
	{
		if (specimen[i].fitness(solution) >= fittest.fitness(solution))
			fittest = specimen[i];
	}
	
	return fittest;
}

void Population::addSpecimen(string genes, int index)
{
	Specimen tempSpecimen;
	tempSpecimen.setGenes(genes);
	specimen[index] = tempSpecimen;
}

void Population::swap(int indexfrom, int indexto)
{
	Specimen temp = specimen[indexto];
	specimen[indexto] = specimen[indexfrom];
	specimen[indexfrom] = temp;
}

#endif