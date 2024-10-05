#pragma once
#include "binaryinsertionsort.h"
#include <algorithm> 

void merge(int* array, int left, int middle, int right, int* compare, int* move)
{
	int lengthLeft = middle - left + 1, lengthRight = right - middle;
	int* leftArray = new int[lengthLeft];
	int* rightArray = new int[lengthRight];
	for (int index = 0; index < lengthLeft; index++)
	{
		leftArray[index] = array[left + index];
		(*move)++;
	}

	for (int index = 0; index < lengthRight; index++)
	{
		rightArray[index] = array[middle + 1 + index];
		(*move)++;
	}
	int indexLeft = 0;
	int indexRight = 0;
	int index = left;

	while (indexLeft < lengthLeft && indexRight < lengthRight)
	{
		(*compare)++;
		(*move)++;
		if (leftArray[indexLeft] <= rightArray[indexRight])
			array[index] = leftArray[indexLeft++];
		else
			array[index] = rightArray[indexRight++];
		index++;
	}
	while (indexLeft < lengthLeft)
	{
		(*move)++;
		array[index++] = leftArray[indexLeft++];
	}
	while (indexRight < lengthRight)
	{
		(*move)++;
		array[index++] = rightArray[indexRight++];
	}
	delete leftArray;
	delete rightArray;
}

void timsort(int* array, int amount, int* compare, int* move, int* time)
{
	*compare = *move = 0;
	int start = clock();
	const int RUN = 32;
	int* leftArray = new int[32];
	for (int i = 0; i < amount; i += RUN)
		binaryinsertionsort(array + i, std::min(RUN, amount - i), compare, move);
	for (int size = RUN; size < amount; size *= 2)
	{
		for (int left = 0; left < amount; left += 2 * size)
		{
			int mid = left + size - 1;
			int right = std::min((left + 2 * size - 1), (amount - 1));
			if (mid < right)
				merge(array, left, mid, right, compare, move);
		}
	}
	int finish = clock();
	*time = finish - start;
}