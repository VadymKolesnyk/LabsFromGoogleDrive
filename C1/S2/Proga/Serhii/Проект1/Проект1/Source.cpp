#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

struct person
{
	string name;
	string surname;
	string patronymic;
};

int main()
{
	SetConsoleOutputCP(1251);
	ifstream mf;
	ofstream of;
	int i = 0, count = 0;
	string n;
	mf.open("input.txt");
	if (!mf.is_open())
	{
		cout << "Файл не открыт" << endl;
		exit(0);
	}
	while (!mf.eof())
	{
		getline(mf, n);
		count++;
	}
	mf.seekg(0);
	person *a = new person[25];
	while (!mf.eof())
	{
		mf >> a[i].name;
		mf >> a[i].patronymic;
		mf >> a[i].surname;
		i++;
	}
	mf.close();
	//for (i = 0; i < count; i++) cout << a[i].surname << " " << a[i].name << " " << a[i].patronymic << endl;
	of.open("output.txt");
	for (i = 0; i < count; i++)
	{
		if (i != 24)
			of << a[i].surname << " " << a[i].name << " " << a[i].patronymic << endl;
		else
			of << a[i].surname << " " << a[i].name << " " << a[i].patronymic;
	}
	of.close();
	system("pause");
}