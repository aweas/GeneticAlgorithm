#pragma once
#define POPULATION_H
#ifdef POPULATION_H

#include <vector>
using namespace std;

class Population
{
	private:
		int populationSize;
		bool initialize;

	public: 
		Population(int size, bool init);
};

Population::Population(int size, bool init)
{
	initialize = init;
	populationSize = size;
}

#endif