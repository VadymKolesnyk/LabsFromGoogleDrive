#pragma once
#include <stdio.h>

double determinant(int** matrix)
{
	return	matrix[0][0] * matrix[1][1] * matrix[2][2] +
		matrix[0][1] * matrix[1][2] * matrix[2][0] +
		matrix[0][2] * matrix[1][0] * matrix[2][1] -
		matrix[0][2] * matrix[1][1] * matrix[2][0] -
		matrix[0][0] * matrix[1][2] * matrix[2][1] -
		matrix[0][1] * matrix[1][0] * matrix[2][2];
}
int** memoryallocationmatrix(int numLines, int numColumns) //��������� ������ ��� ������� ������� numLines �� numColumns
{
	int **matrix = (int**)malloc(numLines * sizeof(int*));
	for (int line = 0; line < numLines; line++)
		matrix[line] = (int*)malloc(numColumns * sizeof(int));
	return matrix;
}
void readmatrix(char* fileName, int** matrix, int numLines, int numColumns) //������ ������� ������� numLines �� numColumns
{
	FILE *file = fopen(fileName, "r");
	for (int line = 0; line < numLines; line++)
		for (int column = 0; column < numColumns; column++)
			fscanf(file, "%d", &matrix[line][column]);
	fclose(file);
}
void printmatrix(int** matrix, int numLines, int numColumns) //����� ������� ������� numLines �� numColumns
{
	for (int line = 0; line < numLines; line++)
	{
		for (int column = 0; column < numColumns; column++)
		{
			printf("%3d ", matrix[line][column]);
		}
		printf("\n");
	}
}
void freematrix(int** matrix, int numLines, int numColumns)
{
	for (int line = 0; line < numLines; line++)
		free(matrix[line]);
	free(matrix);
}
