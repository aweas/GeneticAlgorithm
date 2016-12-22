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
		int elite = 3;
		string intToString(int num);
		string randomNum(int max, char hun, char dec, char one, int min=0, string reserved="256");
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
	cout << "4. Evolve data is set" << endl;
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
	int size = (*population).populationSize;
	Population temporaryPopulation(size, true);

	for (int i = 0;i < 0.9*size; i++)
	{
		int limit = 1;
		if (i < elite)
			limit = (size / (3 * (i + 1)));

		for (int j=0; j < limit && counter< 0.9*size; j++, counter++)
			temporaryPopulation.addSpecimen((*population).getSpecimen(i).getGenes(), counter);
	}

	for (int i = 0;i < 100;i++)
		(*population).addSpecimen(temporaryPopulation.getSpecimen(i).getGenes(), i);
}

Specimen Evolve::select()
{
	//std::clock_t sortClock;
	Population tournament(5, false);
	static int max = (*population).populationSize;
	for (int i = 0;i < 5;i++)
	{
		int pick = rand() % max;		
		string genes = (*population).getSpecimen(pick).getGenes();
		tournament.addSpecimen(genes, i);
	}
	return tournament.getFittest(*solution);
}

void Evolve::crossover()
{
	//Specimen father = (*population).getSpecimen(0);

	int max = (*population).getSpecimen(0).getGenes().length();
	int maxPop = (*population).populationSize;
	for (int j = 1;j < maxPop; j++)
	{
		Specimen father = (*population).getSpecimen(j);
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
	string color[3];
	string circlesNum = randomNum(50, oldGenes[0], oldGenes[0], oldGenes[1],1);
	newGenes += circlesNum;

	for (int j = 0;j < 3;j++)
	{
		//RGB
		string res = randomNum(255, oldGenes[geneNum], oldGenes[geneNum + 1], oldGenes[geneNum + 2]);
		newGenes += res;
		color[j] = res;
		geneNum += 3;
	}
	for (int j = 0;j < 50;j++)
	{
		//Coords X and Y
		newGenes += randomNum(128, oldGenes[geneNum], oldGenes[geneNum + 1], oldGenes[geneNum + 2]);
		geneNum += 3;
		newGenes += randomNum(128, oldGenes[geneNum], oldGenes[geneNum + 1], oldGenes[geneNum + 2]);
		geneNum += 3;
		
		//Radius
		newGenes += randomNum(32, oldGenes[geneNum], oldGenes[geneNum + 1], oldGenes[geneNum + 2]);
		geneNum += 3;
		
		//Color
		//printf("%i: %c%c%c\n", geneNum, oldGenes[geneNum], oldGenes[geneNum + 1], oldGenes[geneNum + 2]);
		newGenes += randomNum(255, oldGenes[geneNum], oldGenes[geneNum + 1], oldGenes[geneNum + 2]);
		geneNum += 3;
		newGenes += randomNum(255, oldGenes[geneNum], oldGenes[geneNum + 1], oldGenes[geneNum + 2]);
		geneNum += 3;
		newGenes += randomNum(255, oldGenes[geneNum], oldGenes[geneNum + 1], oldGenes[geneNum + 2]);
		geneNum += 3;
	}
	/*string str(oldGenes);
	newGenes += str.substr(atoi(circlesNum.c_str())*18+12);*/

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

string Evolve::randomNum(int max, char hunD, char decD, char oneD, int min, string reserved)
{
	string newGenes = "";
	int temp;
	int i = 0;
	int hun = max / 100;
	int dec = (max / 10) % 10;
	int one = max % 10;
	int num = 0;

	while (newGenes == reserved || newGenes=="" || num<min || num>max)
	{
		newGenes = "";

		if (max >= 100)
		{
			if (rand() % 1000 <= MUTATION_RATE)
				newGenes += intToString(rand() % hun);
			else
				newGenes += hunD;
		}
		else if (max == 32 || max == 23)
			newGenes += "0";
		i++;

		if (rand() % 1000 <= MUTATION_RATE)
		{
			if (newGenes[i - 1] != intToString(hun)[0] && max>=100)
				newGenes += intToString(rand() % 10);
			else
				newGenes += intToString(rand() % (dec + 1));
		}
		else if (max == 6)
			newGenes += "0";
		else
			newGenes += decD;
		i++;

		if (rand() % 1000 <= MUTATION_RATE)
		{
			if ((newGenes[i - 2] != intToString(hun)[0] && newGenes[i - 1] != intToString(dec)[0]) || (max<100 && newGenes[i - 1] != intToString(dec)[0]))
				newGenes += intToString(rand() % 10);
			else
				newGenes += intToString(rand() % (one + 1));
		}
		else
			newGenes += oneD;
		num = stoi(newGenes);
	}
	
	return newGenes;
}
#endif