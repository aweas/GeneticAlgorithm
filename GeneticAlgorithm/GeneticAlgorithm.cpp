#include "stdafx.h"
#include "Population.h"

#include <iostream>

int main()
{
	srand(time(NULL));

	Population test(10,true);
	for (int i = 0;i < 10;i++)
		cout << test.getSpecimen(i).getGenes() << endl;

	cin.get();
}

