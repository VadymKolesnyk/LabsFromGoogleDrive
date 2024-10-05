#pragma once

int binarysearch(int* array, int item, int low, int high, int* compare)
{
	if (high <= low)
	{
		(*compare)++;
		return (item > array[low]) ? (low + 1) : low;
	}
	int middle = (low + high) / 2;
	(*compare)++;
	if (item == array[middle])
		return middle + 1;
	(*compare)++;
	if (item > array[middle])
		return binarysearch(array, item, middle + 1, high, compare);
	return binarysearch(array, item, low, middle - 1, compare);
}

void binaryinsertionsort(int* array, int amount, int* compare, int* move)
{
	int location, selected;
	for (int sortedPart = 1; sortedPart < amount; sortedPart++)
	{
		(*move)++;
		selected = array[sortedPart];
		location = binarysearch(array, selected, 0, sortedPart - 1, compare);
		for (int index = sortedPart - 1; index >= location; index--)
		{
			(*move)++;
			array[index + 1] = array[index];
		}
		(*move)++;
		array[location] = selected;
	}
}