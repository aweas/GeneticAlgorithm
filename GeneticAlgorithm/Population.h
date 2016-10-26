#pragma once
#define POPULATION_H
#ifdef POPULATION_H

#include <vector>
#include "Specimen.h"

using namespace std;

class Population
{
	private:
		int populationSize;
		Specimen * specimen;

	public: 
		Population(int size, bool init);
		Specimen getSpecimen(int index);
		Specimen getFittest();
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

Specimen Population::getFittest()
{
	Specimen fittest = specimen[0];
	for (int i = 1; i < populationSize; i++)
	{
		if (specimen[i].fitness() >= fittest.fitness())
			fittest = specimen[i];
	}
	
	return fittest;
}
#endif