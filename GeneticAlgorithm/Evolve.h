#pragma once
#define EVOLVE_H
#ifdef EVOLVE_H
#include "Population.h"

#define MUTATION_RATE 50

class Evolve
{
	private:
		Population * population;
		Fitness * solution;
		void sort();
		void fill();
		void crossover();
		Specimen select();
		void mutate(int index);
		int elite = 5;

	public:
		double timeSort;
		double timeFill;
		double timeCross;
		double timeMutate;

		Evolve(Population& pop, Fitness& sol, int eliteI);
		void EvolvePop();
};

Evolve::Evolve(Population& pop, Fitness& sol, int eliteI)
{
	population = &pop;
	solution = &sol;
	elite = eliteI;
}

void Evolve::sort()
{
	int j;

	for (int i = 0; i < (*population).populationSize; i++)
	{
		j = i;
		while (j > 0 && (*population).getSpecimen(j).fitness(*solution) > (*population).getSpecimen(j - 1).fitness(*solution))
		{
			(*population).swap(j, j - 1);
			j--;
		}
	}
}

void Evolve::fill()
{
	vector<Specimen> best;
	Specimen temp;
	int counter=0;

	for (int i = 0;i < elite;i++)
		best.push_back((*population).getSpecimen(i));

	for (int i = 0;i < (*population).populationSize;i++)
	{
		temp.generate();
		(*population).addSpecimen(temp.getGenes(),i);
	}

	for (int i = 0;i < elite; i++)
	{
		int limit = (counter + (*population).populationSize / (2 * (i + 1)));
		for (int j = counter; j < limit && j<(*population).populationSize; j++)
		{
			(*population).addSpecimen(best[i].getGenes(), j);
			counter++;
		}
	}
}

Specimen Evolve::select()
{
	std::clock_t sortClock;
	
	Population tournament(2, false);
	static int max = (*population).populationSize;
	for (int i = 0;i < 2;i++)
	{
		int pick = rand() % max;

		
		string genes = (*population).getSpecimen(pick).getGenes();
		

		tournament.addSpecimen(genes, i);
	}
	
	return tournament.getFittest(*solution);
}

void Evolve::crossover()
{
	std::clock_t sortClock;
	Specimen father = select();
	
	static int max = father.getGenes().length();
	static int maxPop = (*population).populationSize;
	for (int j = 1;j < maxPop; j++)
	{
		
		Specimen father = select();
		Specimen mother = select();
		string genes;

		for (int i = 0;i < max; i++)
		{
			string gene[2] = { father.getGenes(i), mother.getGenes(i) };
			int pick = rand() % 2;	
			genes += gene[pick];
		}
		
		(*population).addSpecimen(genes, j);	

		sortClock = clock();
		//int fit = (*population).getSpecimen(j).fitness(*solution);
		timeSort += (clock() - sortClock) / (double)CLOCKS_PER_SEC;
	}
}

void Evolve::mutate(int index)
{
	string newGenes;
	string oldGenes = (*population).getSpecimen(index).getGenes();

	static int max = (*population).getSpecimen(index).genesLength;
	for (int i = 0; i < max; i++)
	{
		if (rand() % 1000 <= MUTATION_RATE)
		{
			if (rand() % 2 == 0)
				newGenes += '0';
			else
				newGenes += '1';
		}
		else
			newGenes += oldGenes[i];
	}

	(*population).addSpecimen(newGenes, index);
}

void Evolve::EvolvePop()
{
	std::clock_t sortClock;
	std::clock_t fillClock;
	std::clock_t crossClock;
	std::clock_t mutateClock;

	sortClock = clock();
	sort();
	timeSort+= (clock() - sortClock) / (double)CLOCKS_PER_SEC;

	fillClock = clock();
	fill();
	timeFill += (clock() - fillClock) / (double)CLOCKS_PER_SEC;

	crossClock = clock();
	crossover();
	timeCross += (clock() - crossClock) / (double)CLOCKS_PER_SEC;

	sortClock = clock();
	static int max = (*population).populationSize;
	for(int i=1;i<max;i++)
		mutate(i);
	timeMutate += (clock() - sortClock) / (double)CLOCKS_PER_SEC;
}



#endif