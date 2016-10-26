#pragma once
#define SPECIMEN_H
#ifdef SPECIMEN_H

#include <string>
#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;

class Specimen
{
	private:
		int genesLength=64;
		char genes[64];

	public:
		void generate();
		int fitness();
		string getGenes();
};

void Specimen::generate()
{
	for (int i = 0;i < genesLength;i++)
	{
		if (rand() % 2 == 0)
			genes[i] = '0';
		else
			genes[i] = '1';
	}
}

int Specimen::fitness()
{
	return 9;
}

string Specimen::getGenes()
{
	string temp;
	for (int i = genesLength - 1;i >= 0;i--)
		temp += genes[i];
	return temp;
}
#endif