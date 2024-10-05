#pragma once
#include <fstream>
#include <string>

int* readarray(std::string nameFile, int amount)
{
	std::ifstream input("IncomingData/" + nameFile);
	int* array = new int[amount];
	for (int index = 0; index < amount; index++)
	{
		input >> array[index];
		input.seekg(1, std::ios::cur);
	}
	input.close();
	return array;
}

void writearray(std::string nameFile, int* array, int amount)
{
	std::ofstream output("OutgoingData/" + nameFile);
	output << array[0];
	for (int index = 1; index < amount; index++)
		output << ',' << array[index];
	output.close();
}
