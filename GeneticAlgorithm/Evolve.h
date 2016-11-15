#pragma once
#define EVOLVE_H
#ifdef EVOLVE_H
#include "Population.h"

#define MUTATION_RATE 15

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
		string intToString(int num);
		string randomNum(int max, char hun, char dec, char one);
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
	
	Specimen father = (*population).getSpecimen(0);

	int max = father.getGenes().length();
	int maxPop = (*population).populationSize;
	
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
	}
}

void Evolve::mutate(int index)
{
	string newGenes;
	string oldGenes = (*population).getSpecimen(index).getGenes();

	int max = (*population).getSpecimen(index).genesLength;
	int geneNum = 2;
	newGenes += randomNum(50, oldGenes[0], oldGenes[0], oldGenes[1]);

	for (int j = 0;j < 3;j++)
	{
		//RGB
		//cout << newGenes << endl;
		newGenes += randomNum(255, oldGenes[geneNum], oldGenes[geneNum+1], oldGenes[geneNum+2]);
		geneNum += 3;
	}
	
	for (int j = 0;j < 50;j++)
	{
		//Coords X and Y
		newGenes += randomNum(511, oldGenes[geneNum], oldGenes[geneNum + 1], oldGenes[geneNum + 2]);
		geneNum += 3;
		newGenes += randomNum(511, oldGenes[geneNum], oldGenes[geneNum + 1], oldGenes[geneNum + 2]);
		geneNum += 3;
		//Radius
		newGenes += randomNum(127, oldGenes[geneNum], oldGenes[geneNum + 1], oldGenes[geneNum + 2]);
		geneNum += 3;
		//Color
		newGenes += randomNum(255, oldGenes[geneNum], oldGenes[geneNum + 1], oldGenes[geneNum + 2]);
		geneNum += 3;
		newGenes += randomNum(255, oldGenes[geneNum], oldGenes[geneNum + 1], oldGenes[geneNum + 2]);
		geneNum += 3;
		newGenes += randomNum(255, oldGenes[geneNum], oldGenes[geneNum + 1], oldGenes[geneNum + 2]);
		geneNum += 3;
	}
	
		//if (rand() % 1000 <= MUTATION_RATE)
		//{
		//	if (rand() % 2 == 0)
		//		newGenes += '0';
		//	else
		//		newGenes += '1';
		//}
		//else
		//	newGenes += oldGenes[i];

	(*population).addSpecimen(newGenes, index);
}

void Evolve::EvolvePop()
{
	sort();
	fill();
	crossover();
	
	int max = (*population).populationSize;

	for(int i=1;i<max;i++)
		mutate(i);
}

string Evolve::intToString(int num)
{
	char a = num + 48;
	string temp(1, a);
	return temp;
}

string Evolve::randomNum(int max, char hunD, char decD, char oneD)
{
	string newGenes = "";
	int i = 0;
	int hun = max / 100;
	int dec = (max / 10) % 10;
	int one = max % 10;

	if (max >= 100)
	{
		if (rand() % 1000 <= MUTATION_RATE)
			newGenes += intToString(rand() % hun);
		else
			newGenes += hunD;
		i++;
	}

	if (rand() % 1000 <= MUTATION_RATE)
	{
		if (newGenes[i - 1] != intToString(hun)[0])
			newGenes += intToString(rand() % 9);
		else
			newGenes += intToString(rand() % (dec+1));
	}
	else
		newGenes += decD;
	i++;

	if (rand() % 1000 <= MUTATION_RATE)
	{
		if (newGenes[i - 2] != intToString(hun)[0] && newGenes[i - 1] != intToString(dec)[0])
			newGenes += intToString(rand() % 9);
		else
			newGenes += intToString(rand() % (one + 1));
	}
	else
		newGenes += oneD;

	return newGenes;
}
#endif