#include <fstream>
#include <string>
#include <iostream>
using namespace std;

int main()
{
	ifstream fi;
	string s;
	fi.open("input.txt"); // открытие файла
	if (!fi)
	{
		cout << "ERROR" << endl;
		system("pause");
		exit(1);
	}
	getline(fi, s); // считывание строчки из файла
	cout << "input.txt:" << endl;
	cout << s << endl;
	fi.close();
	int pos = s.find("  "); //поиск двух пробелов подряд 
	while ((pos = s.find("  ", pos)) != -1)
		s.replace(pos, 2, " "); // замена всех пар пробелов на один пробел
	if (s[0] == ' ')
		s.erase(0, 1); // удаление начального пробела
	if (s[s.length() - 1] == ' ')
		s.erase(s.length() - 1, 1); // удаление конечного пробела
	pos = s.find(" ");
	while ((pos = s.find(" ", pos + 1)) != -1) // поиск мест где пробелы стоят через 1 символ
		if (s[pos + 2] == ' ')
			s.replace(pos, 3, " "); // замена этих 3 символов на пробел. Удаление слова из 1 буквы 
	if (s[1] == ' ')
		s.erase(0, 2); // удаление начального однобуквенного слова
	if (s[s.length() - 2] == ' ')
		s.erase(s.length() - 2, 2); // удаление конечного однобувенного
	ofstream fo;
	fo.open("output.txt"); // открытие файла
	if (!fo)
	{
		cout << "ERROR" << endl;
		system("pause");
		exit(1);
	}
	fo << s; // запись новой строчки в файл
	cout << endl << "output.txt:" << endl;
	cout << s << endl << endl;
	fo.close(); // закрытие файла
	system("pause");
	return 0;
}