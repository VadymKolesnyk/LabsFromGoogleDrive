//1. ������ ����� ����, ������������� �����������, ������� ����� � �����
//2. ������ 2 ������� - �������� � �������� �����
//#include <stdafx.h>
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<math.h>
#include <string.h>
char str_esc[] = "����� �� ESC";
const double Pi = 3.141592;
using namespace std;
void draw(HWND hwnd, HDC hdc, int i1 = 100, int i2 = 60, int i3 = 180, int i4 = 160);
void grafp(HWND hwnd, HDC hdc, int i1 = 10, int i2 = 10, int i3 = 400, int i4 = 300);
void grafl(HWND hwnd, HDC hdc, int i1 = 10, int i2 = 10, int i3 = 400, int i4 = 300);
void setConsoleSize();
int main()
{
	char ch;
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	setConsoleSize();
	Sleep(100);
	draw(hwnd, hdc);
	int iKey = 1;
	while (iKey != 27) { // ��������,����� �� ESC
		if (_kbhit()) {
			iKey = _getch();
			//printf("%d", iKey);
			switch (iKey) {
				// ������ �����, �������� �� �������� ������������
			case 80:grafl(hwnd, hdc, 10, 10, 400, 300); break;
				// ������� ���� ����������� � �������� ������
			case 77: draw(hwnd, hdc, 10, 10, 400, 300); break;
				//������ ��������, ����'���� �� �������� ������������
			case 75: grafp(hwnd, hdc, 10, 10, 400, 300); break;
			case 72: draw(hwnd, hdc); break;
				// ������������ ������ �������������
			}
		}
	}
	system("pause");
	ReleaseDC(NULL, hdc);
	return 0;
}
void draw(HWND hwnd, HDC hdc, int i1, int i2, int i3, int i4) {
	Rectangle(hdc, i1, i2, i3, i4); //��������� ������������ � �������� ���������
	HPEN Pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	SelectObject(hdc, Pen);
	int er = 10;
	TextOutA(hdc, i1 + er, i4 + er, str_esc, strlen(str_esc));
	MoveToEx(hdc, i1, i2, NULL);
	LineTo(hdc, i3, i2);
	LineTo(hdc, i3, i4);
	LineTo(hdc, i1, i4);
	LineTo(hdc, i1, i2);
	DeleteObject(Pen);
};
void grafp(HWND hwnd, HDC hdc, int i1, int i2, int i3, int i4)
{
	double x, y;
	COLORREF penColor = RGB(0, 0, 255);
	// ������� ������ �������� �� �������
	int er = 10, middle = i2 + (i4 - i2) / 2, delta = i4 - middle - er;
	char str[] = "������ �������� �� �������";
	TextOutA(hdc, i3 + er, 4 * er, str, strlen(str));
	for (x = i1; x < i3 - er; x++) {
		y = sin(Pi*x / 50); SetPixel(hdc, i1 + (int)x, middle + (int)(delta*y), penColor);
	}
};
void grafl(HWND hwnd, HDC hdc, int i1, int i2, int i3, int i4)
{
	double x, y;
	int er = 10, middle = i2 + (i4 - i2) / 2, delta = i4 - middle - er;
	// ������� ������ �������� ��������
	char str[] = "������ �������� ��������"; 
	TextOutA(hdc, i3 + er, 4 * er, str,	strlen(str));
	HPEN Pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	SelectObject(hdc, Pen);
	MoveToEx(hdc, i1, middle, NULL);
	for (x = i1; x < i3 - er; x++) {
		y = sin(Pi*x / 50);
		LineTo(hdc, i1 + (int)x, middle + (int)(delta*y));
	};
	//SetPixel(hdc,i1+(int)x,middle+(int)(delta*y),penColor); }
};
void setConsoleSize()
{ //������ ��������� ���� ��� ���������
	const int colConsole = 80;
	const int rowConsole = 30;
	HANDLE hNdl = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT windowSize = { 0,0,colConsole - 1,rowConsole - 1 };
	SetConsoleWindowInfo(hNdl, TRUE, &windowSize);
	COORD bufferSize = { colConsole, rowConsole }; // ������� ������
	SetConsoleScreenBufferSize(hNdl, bufferSize);
}