#define _CRT_SECURE_NO_WARNINGS
#include "determinant.h"
#include "array.h"
#include "integrate.h"

int main()
{
	int** matrix = memoryallocationmatrix(3, 3);
	readmatrix("Matrix.txt", matrix, 3, 3);
	printf("Your matrix A:\n\n");
	printmatrix(matrix, 3, 3);
	printf("\ndet(A)=%lf\n", determinant(matrix));
	freematrix(matrix, 3, 3);

	printf("\n\n------------------------------------\n\n\n");

	int* array1 = NULL;
	int num = readarray("Array.txt", &array1);
	int* array2 = memoryallocationarray(num);
	int newNum = transformation(array1, array2, num);
	printf("Your array:\n");
	prinarray(array1, num);
	printf("New array:\n");
	prinarray(array2, newNum);
	free(array1);
	free(array2);

	printf("\n\n------------------------------------\n\n\n");

	double lowerBound, upperBound;
	int power;
	printf("Integrate function ln^n (x) dx from a to b\n");
	printf("Enter a = ");
	scanf("%lf", &lowerBound);
	printf("Enter b = ");
	scanf("%lf", &upperBound);
	printf("Enter n = ");
	scanf("%d", &power);
	if (lowerBound > 0.00 && upperBound > 0.00 && power > 0)
		printf("Answer = %lf\n", integrate(lowerBound, upperBound, power));
	else
		printf("Input data is not correct\n");

	system("pause");
	return 0;
}
