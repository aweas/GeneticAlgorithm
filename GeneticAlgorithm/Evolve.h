#pragma once
#define EVOLVE_H
#ifdef EVOLVE_H
#define MUTATION_RATE 50



#include "Population.h"
//ToDo: write statistics on what is more efficient: mutation or crossover
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
	for (int i = 0;i<(*population).populationSize;i++)
		for (int j = 0;j < (*population).populationSize - 1;j++)
			if ((*population).getSpecimen(j).fitness(*solution) < (*population).getSpecimen(j + 1).fitness(*solution))
				(*population).swap(j, j + 1);
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
	Population tournament((*population).populationSize/2, false);
	for (int i = 0;i < tournament.populationSize; i++)
	{
		int pick = rand() % (*population).populationSize;
		tournament.addSpecimen((*population).getSpecimen(pick).getGenes(), i);
	}
	return tournament.getFittest(*solution);
}

void Evolve::crossover()
{
	for (int j = 1;j < (*population).populationSize; j++)
	{
		Specimen father = select();
		Specimen mother = select();
		string genes;
		for (int i = 0;i < father.getGenes().length(); i++)
		{
			if (rand() % 2 == 0)
				genes += father.getGenes()[i];
			else
				genes += mother.getGenes()[i];
		}
		(*population).addSpecimen(genes, j);
		int fit = (*population).getSpecimen(j).fitness(*solution);
	}
}

void Evolve::mutate(int index)
{
	string newGenes;
	string oldGenes = (*population).getSpecimen(index).getGenes();
	for (int i = 0;i < 64;i++)
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
	sort();
	fill();
	crossover();
	for(int i=1;i<(*population).populationSize;i++)
		mutate(i);
}



#endif