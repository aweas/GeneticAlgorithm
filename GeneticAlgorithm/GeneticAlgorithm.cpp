
#include "stdafx.h"
#include "Population.h"
#include "Evolve.h"

#include <iostream>
#include <cstdio>
#include <ctime>

#define POPULATION_SIZE 10
#define ELITES_NUMBER 3
#define SOLUTION_LENGTH 901030

string generateGenes();
string decToBin(int num);

int main()
{
	int i;
	FILE* f = fopen("C:\\Users\\wwydm\\Desktop\\Bez tytu³u.bmp", "rb");
	FILE* o = fopen("C:\\Users\\wwydm\\Desktop\\test.bmp", "wb");
	unsigned char info[54];

	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header									   
	int width = *(int*)&info[18];			// extract image height and width from header
	int height = *(int*)&info[22];
	int size = 3 * width * height;
	fclose(f);

	

	//char* newbuf = new char[size];

	//long bufpos = 0;

	//for (int y = 0; y < height; y++)
	//	for (int x = 0; x < 3 * width; x += 3)
	//	{
	//		bufpos = y * 3 * width + x;     // position in original buffer
	//		newbuf[bufpos] = rand() % 255;       // swap r and b
	//		newbuf[bufpos + 1] = rand() % 255; // g stays
	//		newbuf[bufpos + 2] = rand() % 255;     // swap b and r
	//	}

	//fwrite(info, sizeof(char),54,o);
	//fwrite(newbuf, sizeof(char), size, o);
	//cin.get();
	srand(time(NULL));

	int generationsCount = 0;
	Fitness * solution;
	Population * test;
	Evolve * evolution;
	std::clock_t start;


	solution = new Fitness(generateGenes());
	test = new Population(POPULATION_SIZE, true);
	evolution = new Evolve(*test, *solution, ELITES_NUMBER);

	printf("Elites: %i, Population: %i\n", ELITES_NUMBER, POPULATION_SIZE);
	start = clock();

	for (generationsCount; (*test).getFittest(*solution).fitness(*solution) != (*solution).solutionLength ; generationsCount++)
	{
		(*evolution).EvolvePop();
		if(generationsCount% (50/(*test).populationSize)==0)
			printf("#%i Fitness: %i\n", generationsCount, (*test).getFittest(*solution).fitness(*solution));
		if ((*test).getFittest(*solution).fitness(*solution) >= (0.95*SOLUTION_LENGTH) && (*test).populationSize == POPULATION_SIZE)
			(*test).setPopulation(50);

	}

	double timer = (clock() - start) / (double)CLOCKS_PER_SEC;

	printf("\nSolution found in %i generations\nTime: %5.3f seconds", generationsCount-1,timer);
	cin.get();
}

string generateGenes()
{
	string solutionGenes;
	FILE* f = fopen("C:\\Users\\wwydm\\Desktop\\Bez tytu³u.bmp", "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

	int width = *(int*)&info[18];			// extract image height and width from header
	int height = *(int*)&info[22];

	int size = 3 * width * height;
	unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
	fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
	fclose(f);

	for (int i = 0; i < size; i += 3)
	{
		unsigned char tmp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = tmp;

		solutionGenes += decToBin(data[i]);
		solutionGenes += decToBin(data[i + 1]);
		solutionGenes += decToBin(data[i + 2]);
	}

	return solutionGenes;
}

string decToBin(int number)
{
	if (number == 0) return "0";
	if (number == 1) return "1";

	if (number % 2 == 0)
		return decToBin(number / 2) + "0";
	else
		return decToBin(number / 2) + "1";
}