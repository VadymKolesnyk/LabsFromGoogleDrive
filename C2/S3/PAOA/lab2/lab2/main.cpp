#include <iostream>
#include "readwritearray.h"
#include "bubblesort.h"
#include "timsort.h"

void sort(std::string fileName, int amount, void (*sortFunc)(int*, int, int*, int*, int*))
{
	int compare, move, time;
	int* array = readarray(fileName, amount);
	sortFunc(array, amount, &compare, &move, &time);
	std::cout << fileName << ":" << std::endl;
	std::cout << "Comparisons: " << compare << std::endl;
	std::cout << "Moves: " << move << std::endl;
	std::cout << "Time: " << time << "ms" << std::endl;
	writearray(fileName, array, amount);
	delete array;
}

void sortcycle(std::string fileName, int amount, void(*sortFunc)(int*, int, int*, int*, int*))
{
	int compare, move, time;
	double timeAverage = 0;
	int* array;
	int timeAll = 0;
	for (int i = 0; i < 100; i++)
	{
		array = readarray(fileName, amount);
		timeAll -= clock();
		sortFunc(array, amount, &compare, &move, &time);
		timeAll += clock();
		if (i!=99)
			delete array;
	}
	int finish = clock();
	timeAverage = ((double)timeAll) / 100;
	std::cout << fileName << ":" << std::endl;
	std::cout << "Comparisons: " << compare << std::endl;
	std::cout << "Moves: " << move << std::endl;
	std::cout << "Time: " << timeAverage << "ms" << std::endl;
	writearray(fileName, array, amount);
	delete array;
}

int main()
{
	std::cout << "Bubble sort:" << std::endl << std::endl;
	sortcycle("random100.txt", 100, bubblesort);
	sort("random1000.txt", 1000, bubblesort);
	sort("random10000.txt", 10000, bubblesort);
	std::cout << std::endl;
	sortcycle("constant100.txt", 100, bubblesort);
	sortcycle("constant1000.txt", 1000, bubblesort);
	sort("constant10000.txt", 10000, bubblesort);
	std::cout << std::endl;
	sortcycle("reversed100.txt", 100, bubblesort);
	sort("reversed1000.txt", 1000, bubblesort);
	sort("reversed10000.txt", 10000, bubblesort);
	std::cout << std::endl;
	sortcycle("sorted100.txt", 100, bubblesort);
	sortcycle("sorted1000.txt", 1000, bubblesort);
	sort("sorted10000.txt", 10000, bubblesort);
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Tim sort:" << std::endl << std::endl;
	sortcycle("random100.txt", 100, timsort);
	sortcycle("random1000.txt", 1000, timsort);
	sortcycle("random10000.txt", 10000, timsort);
	std::cout << std::endl;
	sortcycle("constant100.txt", 100, timsort);
	sortcycle("constant1000.txt", 1000, timsort);
	sortcycle("constant10000.txt", 10000, timsort);
	std::cout << std::endl;
	sortcycle("reversed100.txt", 100, timsort);
	sortcycle("reversed1000.txt", 1000, timsort);
	sortcycle("reversed10000.txt", 10000, timsort);
	std::cout << std::endl;
	sortcycle("sorted100.txt", 100, timsort);
	sortcycle("sorted1000.txt", 1000, timsort);
	sortcycle("sorted10000.txt", 10000, timsort);
	system("pause");
	return 0;
}