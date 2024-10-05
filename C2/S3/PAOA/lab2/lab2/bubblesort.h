#pragma once
#include <ctime>

void bubblesort(int* array, int amount, int* compare, int* move, int* time)
{
	*compare = *move = *time = 0;
	int start = clock();
	for (int unsortedPart = amount - 1; unsortedPart > 0; unsortedPart--)
		for (int index = 0; index < unsortedPart; index++)
		{
			(*compare)++;
			if (array[index] > array[index + 1])
			{
				(*move)+=3;
				std::swap(array[index], array[index + 1]);
			}
		}
	int finish = clock();
	*time = (finish - start);
}