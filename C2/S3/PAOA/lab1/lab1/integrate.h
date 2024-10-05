#pragma once
#include <math.h>

double integrate(double  lowerBound, double upperBound, int power)
{
	if (power == 1)
		return (upperBound * log(upperBound) - upperBound) - (lowerBound * log(lowerBound) - lowerBound);
	double integrate(double  lowerBound, double upperBound, int power);
	return ((upperBound * pow(log(upperBound), power)) - (lowerBound * pow(log(lowerBound), power))) -
		power * integrate(lowerBound, upperBound, power - 1);
}