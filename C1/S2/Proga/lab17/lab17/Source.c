#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <math.h>
#define UP 72		//������ �����
#define RIGHT 77	//������ ������
#define DOWN 80		//������ ����
#define LEFT 75		//������ �����
#define PLUS 43		//������ ����
#define MINUS 45	//������ �����
#define ESC 27		//������ ������

const int xmax = 799; // ������ ������
const int ymax = 599; // ������ ������
// ��������� ��������� ����
int x_0 = 300; 
int y_0 = 250;

double f(double x) // ������� ������ ������� ���� ���������
{
	return (x - 3) * cos(x) - 1;
}
void background(HDC hdc, int k, HPEN pendots, HPEN penaxes, HPEN pendiv) // ��������� ������� � ����
{
	if (x_0 <= xmax && y_0 <= ymax) // ����� 0 ����� ������ ���������
	{
		TextOut(hdc, x_0 + 3, y_0 + 5, "0", 1);
	}
	int i = x_0 + k;
	while (i <= xmax)
	{
		int b = (y_0 <= ymax && y_0 >= 0);
		if (i <= xmax)
		{
			if (b) // ����� - ����� �������
			{
				char s[10];
				_itoa(((i - x_0) / k), s, 10);
				TextOut(hdc, i, y_0 + 5, s, strlen(s));
			}
			SelectObject(hdc, pendots); // ��������� ������������ ����� ��������
			MoveToEx(hdc, i, 0, NULL);
			LineTo(hdc, i, ymax);
			if (b) // ����� - �������
			{
				SelectObject(hdc, pendiv);
				MoveToEx(hdc, i, y_0 + 3, NULL);
				LineTo(hdc, i, y_0 - 4);
			}
		}
		i += k;
	}
	i = x_0 - k;
	while (i >= 0)
	{
		int b = (y_0 <= ymax && y_0 >= 0);
		if (i <= xmax)
		{
			if (b) // ����� - ����� �������
			{
				char s[10];
				_itoa(((i - x_0) / k), s, 10);
				TextOut(hdc, i, y_0 + 5, s, strlen(s));
			}
			SelectObject(hdc, pendots); // ��������� ������������ ����� ��������
			MoveToEx(hdc, i, 0, NULL);
			LineTo(hdc, i, ymax);
			if (b)
			{
				SelectObject(hdc, pendiv);  // ����� - �������
				MoveToEx(hdc, i, y_0 + 3, NULL);
				LineTo(hdc, i, y_0 - 4);
			}
		}
		i -= k;
	}
	i = y_0 + k;
	while (i <= ymax)
	{
		int b = (x_0 <= xmax && x_0 >= 0);
		if (i <= ymax)
		{
			if (b) // ����� - ����� �������
			{
				char s[10];
				_itoa(-((i - y_0) / k), s, 10);
				TextOut(hdc, x_0 + 2, i, s, strlen(s));
			}
			SelectObject(hdc, pendots); // ��������� �������������� ����� ��������
			MoveToEx(hdc, 0, i, NULL);
			LineTo(hdc, xmax, i);
			if (b)
			{
				SelectObject(hdc, pendiv);  // ����� - �������
				MoveToEx(hdc, x_0 + 3, i, NULL);
				LineTo(hdc, x_0 - 4, i);
			}
		}
		i += k;
	}
	i = y_0 - k;
	while (i >= 0)
	{
		int b = (x_0 <= xmax && x_0 >= 0);
		if (i <= ymax)
		{
			if (b) // ����� - ����� �������
			{
				char s[10];
				_itoa(-((i - y_0) / k), s, 10);
				TextOut(hdc, x_0 + 2, i, s, strlen(s));
			}
			SelectObject(hdc, pendots); // ��������� �������������� ����� ��������
			MoveToEx(hdc, 0, i, NULL);
			LineTo(hdc, xmax, i);
			if (b)
			{
				SelectObject(hdc, pendiv);  // ����� - �������
				MoveToEx(hdc, x_0 + 3, i, NULL);
				LineTo(hdc, x_0 - 4, i);
			}
		}
		i -= k;
	}
	SelectObject(hdc, penaxes);
	if (x_0 <= xmax && x_0 >= 0) // ������������ ���
	{
		MoveToEx(hdc, x_0, 0, NULL); 
		LineTo(hdc, x_0, ymax);
		MoveToEx(hdc, x_0 - 5, 5, NULL);
		LineTo(hdc, x_0, 0);
		LineTo(hdc, x_0 + 5, 5);
		TextOut(hdc, x_0 - 18, 1, "y", 1);

	}
	if (y_0 <= ymax && y_0 >= 0) // �������������� ���
	{
		MoveToEx(hdc, 0, y_0, NULL);
		LineTo(hdc, xmax, y_0);
		MoveToEx(hdc, xmax - 5, y_0 - 5, NULL);
		LineTo(hdc, xmax, y_0);
		LineTo(hdc, xmax - 5, y_0 + 5);
		TextOut(hdc, xmax - 10, y_0 - 22, "x", 1);
	}
}

double rx(int x, int k) // ������� �� ��������� � � ��������
{
	return ((double)(x - x_0) / k);
}
int sy(double y, int k) // ������� �� ��������� � � ��������
{
	return (int)(-y * k + y_0);
}
void draw(HDC hdc, int k, HPEN pengraph) // ���������� ������� ��������� ������� � ������� �����
{

	TextOut(hdc,1, 1,"y = (x - 3) * cos(x) - 1", 24);
	SelectObject(hdc, pengraph);
	int y;
	MoveToEx(hdc, 0, sy(f(rx(0,k)), k), NULL);
	for (int i = 0; i < xmax; i += 3)
	{
		y = sy(f(rx(i, k)), k);
		POINT temp;
		GetCurrentPositionEx(hdc, &temp);
		if (y > ymax && temp.y > ymax) // ���� ���� �� �������� ������ ������ ������� ���, � �� ������ �����
		{
			MoveToEx(hdc, i, y, NULL);
		}
		else
		{
			LineTo(hdc, i, y);
		}
	}
	SelectObject(hdc, CreatePen(PS_NULL, 2, RGB(0, 0, 0))); // ������� � ������ ���� � ������� � ����� ������� ����
	LineTo(hdc, 0, 0);
}
int main()
{

	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo); 
	system("color f0");// ��������� ����������� ����
	SetConsoleTitle("Lab17");
	HWND hwnd = GetConsoleWindow();
	MoveWindow(hwnd, 300, 50, xmax + 34, ymax + 25, 1);
	HDC hdc = GetDC(GetConsoleWindow());
	HPEN pengraph = CreatePen(PS_SOLID, 2, RGB(0xFF, 0, 0));
	HPEN pendots = CreatePen(PS_DOT, 1, RGB(0xA9, 0xA9, 0xA9));
	HPEN penaxes = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HPEN pendiv = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	SetConsoleOutputCP(1251); // ����� ����������
	printf("���������� ������� y = (x - 3)cos(x) - 1.\n");
	printf("����������:\n");
	printf("������� ����� - ��������� ������� �����\n");
	printf("������� ���� - ��������� ������� ����\n");
	printf("������� ����� - ��������� ������� �����\n");
	printf("������� ������ - ��������� ������� ������\n");
	printf("���� - ��������� �������\n");
	printf("����� - ��������� �������\n");
	printf("������ - �����\n");
	system("pause");
	system("cls");
	int k = 30;
	background(hdc, k, pendots, penaxes, pendiv); // ���������� ���������� �������
	draw(hdc, k, pengraph); // ���������� ���������� �������
	int key = 1; // ������� �������
	while (key != ESC)
	{
		if (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			case DOWN: // ����������� ��� � �����
				Rectangle(hdc, 0, 0, xmax + 25, ymax + 50);
				y_0 -= 5;
				background(hdc, k, pendots, penaxes, pendiv);
				draw(hdc, k, pengraph);
				break;
			case RIGHT: // ����������� ��� � �����
				Rectangle(hdc, 0, 0, xmax + 25, ymax + 50);
				x_0 -= 5;
				background(hdc, k, pendots, penaxes, pendiv);
				draw(hdc, k, pengraph);
				break;
			case LEFT: // ����������� ��� � ������
				Rectangle(hdc, 0, 0, xmax + 25, ymax + 50);
				x_0 += 5;
				background(hdc, k, pendots, penaxes, pendiv);
				draw(hdc, k, pengraph);
				break;
			case UP: // ����������� ��� � ����
				Rectangle(hdc, 0, 0, xmax + 25, ymax + 50);
				y_0 += 5;
				background(hdc, k, pendots, penaxes, pendiv);
				draw(hdc, k, pengraph);
				break;
			case PLUS: // ��������� ������� ������������ ������ ������
				Rectangle(hdc, 0, 0, xmax + 25, ymax + 50);
				if (k < 100)
				{
					x_0 = x_0 + (int)(3 * (x_0 - (double)(xmax) / 2) / k); // �������� ���� ���, ���� ��������� ������� ���� ������������ ������
					y_0 = y_0 + (int)(3 * (y_0 - (double)(ymax) / 2) / k);
					k += 3;
				}
				background(hdc, k, pendots, penaxes, pendiv);
				draw(hdc, k, pengraph);
				break;
			case MINUS: // ��������� ������� ������������ ������ ������
				Rectangle(hdc, 0, 0, xmax + 25, ymax + 50);
				if (k > 10)
				{
					x_0 = x_0 - (int)(3 * (x_0 - (double)(xmax) / 2) / k); // �������� ���� ���, ���� ��������� ������� ���� ������������ ������
					y_0 = y_0 - (int)(3 * (y_0 - (double)(ymax) / 2) / k);
					k -= 3;
				}
				background(hdc, k, pendots, penaxes, pendiv);
				draw(hdc, k, pengraph);
				break;
			}
		}
	}
	ReleaseDC(NULL, hdc);
	return 0;
}