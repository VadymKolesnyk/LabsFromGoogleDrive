#include <fstream>
#include <string>
#include <iostream>
using namespace std;

int main()
{
	ifstream fi;
	string s;
	fi.open("input.txt"); // �������� �����
	if (!fi)
	{
		cout << "ERROR" << endl;
		system("pause");
		exit(1);
	}
	getline(fi, s); // ���������� ������� �� �����
	cout << "input.txt:" << endl;
	cout << s << endl;
	fi.close();
	int pos = s.find("  "); //����� ���� �������� ������ 
	while ((pos = s.find("  ", pos)) != -1)
		s.replace(pos, 2, " "); // ������ ���� ��� �������� �� ���� ������
	if (s[0] == ' ')
		s.erase(0, 1); // �������� ���������� �������
	if (s[s.length() - 1] == ' ')
		s.erase(s.length() - 1, 1); // �������� ��������� �������
	pos = s.find(" ");
	while ((pos = s.find(" ", pos + 1)) != -1) // ����� ���� ��� ������� ����� ����� 1 ������
		if (s[pos + 2] == ' ')
			s.replace(pos, 3, " "); // ������ ���� 3 �������� �� ������. �������� ����� �� 1 ����� 
	if (s[1] == ' ')
		s.erase(0, 2); // �������� ���������� �������������� �����
	if (s[s.length() - 2] == ' ')
		s.erase(s.length() - 2, 2); // �������� ��������� �������������
	ofstream fo;
	fo.open("output.txt"); // �������� �����
	if (!fo)
	{
		cout << "ERROR" << endl;
		system("pause");
		exit(1);
	}
	fo << s; // ������ ����� ������� � ����
	cout << endl << "output.txt:" << endl;
	cout << s << endl << endl;
	fo.close(); // �������� �����
	system("pause");
	return 0;
}