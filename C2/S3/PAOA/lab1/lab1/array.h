#pragma once
#include <stdio.h>

int* memoryallocationarray(int num)
{
	return (int*)malloc(num * sizeof(int));
}
int readarray(char* fileName, int** array)
{
	FILE* file = fopen(fileName, "r");
	int num;
	free(*array);
	fscanf(file, "%d", &num);
	*array = memoryallocationarray(num);
	for (int i = 0; i < num; i++)
	{
		fscanf(file, "%d", &(*array)[i]);
	}
	return num;
}
int transformation(int* array1, int* array2, int num)
{
	int i2 = 0;
	for (int i1 = 0; i1 < num; i1++)
		if (array1[i1] > 0)
			array2[i2++] = array1[i1];
	for (int i1 = 0; i1 < num; i1++)
		if (array1[i1] < 0)
			array2[i2++] = array1[i1];
	return i2;
}
void prinarray(int* array, int num)
{
	for (int i = 0; i < num; i++)
		printf("%3d ", array[i]);
	printf("\n");
}