#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <math.h>
#define UP 72		//кнопка вверх
#define RIGHT 77	//кнопка вправо
#define DOWN 80		//кнопка вниз
#define LEFT 75		//кнопка влево
#define PLUS 43		//кнопка плюс
#define MINUS 45	//кнопка минус
#define ESC 27		//кнопка эскейп

const int xmax = 799; // ширина экрана
const int ymax = 599; // высота экрана
// начальное положение осей
int x_0 = 300; 
int y_0 = 250;

double f(double x) // функция график которой надо построить
{
	return (x - 3) * cos(x) - 1;
}
void background(HDC hdc, int k, HPEN pendots, HPEN penaxes, HPEN pendiv) // рисование полотна и осей
{
	if (x_0 <= xmax && y_0 <= ymax) // цифра 0 возле начала координат
	{
		TextOut(hdc, x_0 + 3, y_0 + 5, "0", 1);
	}
	int i = x_0 + k;
	while (i <= xmax)
	{
		int b = (y_0 <= ymax && y_0 >= 0);
		if (i <= xmax)
		{
			if (b) // цифра - номер деления
			{
				char s[10];
				_itoa(((i - x_0) / k), s, 10);
				TextOut(hdc, i, y_0 + 5, s, strlen(s));
			}
			SelectObject(hdc, pendots); // рисование вертикальных линий клеточек
			MoveToEx(hdc, i, 0, NULL);
			LineTo(hdc, i, ymax);
			if (b) // штрих - деление
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
			if (b) // цифра - номер деления
			{
				char s[10];
				_itoa(((i - x_0) / k), s, 10);
				TextOut(hdc, i, y_0 + 5, s, strlen(s));
			}
			SelectObject(hdc, pendots); // рисование вертикальных линий клеточек
			MoveToEx(hdc, i, 0, NULL);
			LineTo(hdc, i, ymax);
			if (b)
			{
				SelectObject(hdc, pendiv);  // штрих - деление
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
			if (b) // цифра - номер деления
			{
				char s[10];
				_itoa(-((i - y_0) / k), s, 10);
				TextOut(hdc, x_0 + 2, i, s, strlen(s));
			}
			SelectObject(hdc, pendots); // рисование горизонтальных линий клеточек
			MoveToEx(hdc, 0, i, NULL);
			LineTo(hdc, xmax, i);
			if (b)
			{
				SelectObject(hdc, pendiv);  // штрих - деление
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
			if (b) // цифра - номер деления
			{
				char s[10];
				_itoa(-((i - y_0) / k), s, 10);
				TextOut(hdc, x_0 + 2, i, s, strlen(s));
			}
			SelectObject(hdc, pendots); // рисование горизонтальных линий клеточек
			MoveToEx(hdc, 0, i, NULL);
			LineTo(hdc, xmax, i);
			if (b)
			{
				SelectObject(hdc, pendiv);  // штрих - деление
				MoveToEx(hdc, x_0 + 3, i, NULL);
				LineTo(hdc, x_0 - 4, i);
			}
		}
		i -= k;
	}
	SelectObject(hdc, penaxes);
	if (x_0 <= xmax && x_0 >= 0) // вертикальная ось
	{
		MoveToEx(hdc, x_0, 0, NULL); 
		LineTo(hdc, x_0, ymax);
		MoveToEx(hdc, x_0 - 5, 5, NULL);
		LineTo(hdc, x_0, 0);
		LineTo(hdc, x_0 + 5, 5);
		TextOut(hdc, x_0 - 18, 1, "y", 1);

	}
	if (y_0 <= ymax && y_0 >= 0) // горизонтальная ось
	{
		MoveToEx(hdc, 0, y_0, NULL);
		LineTo(hdc, xmax, y_0);
		MoveToEx(hdc, xmax - 5, y_0 - 5, NULL);
		LineTo(hdc, xmax, y_0);
		LineTo(hdc, xmax - 5, y_0 + 5);
		TextOut(hdc, xmax - 10, y_0 - 22, "x", 1);
	}
}

double rx(int x, int k) // переход из экранного х в реальный
{
	return ((double)(x - x_0) / k);
}
int sy(double y, int k) // переход из реального у в экранный
{
	return (int)(-y * k + y_0);
}
void draw(HDC hdc, int k, HPEN pengraph) // построение графика численным методом с помощью линий
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
		if (y > ymax && temp.y > ymax) // Если перо за границей экрана просто двигаем его, а не рисуем линию
		{
			MoveToEx(hdc, i, y, NULL);
		}
		else
		{
			LineTo(hdc, i, y);
		}
	}
	SelectObject(hdc, CreatePen(PS_NULL, 2, RGB(0, 0, 0))); // переход в пустое перо и переход в левый верхний угол
	LineTo(hdc, 0, 0);
}
int main()
{

	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo); 
	system("color f0");// настройка консольного окна
	SetConsoleTitle("Lab17");
	HWND hwnd = GetConsoleWindow();
	MoveWindow(hwnd, 300, 50, xmax + 34, ymax + 25, 1);
	HDC hdc = GetDC(GetConsoleWindow());
	HPEN pengraph = CreatePen(PS_SOLID, 2, RGB(0xFF, 0, 0));
	HPEN pendots = CreatePen(PS_DOT, 1, RGB(0xA9, 0xA9, 0xA9));
	HPEN penaxes = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HPEN pendiv = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	SetConsoleOutputCP(1251); // вывод инструкции
	printf("Построение графика y = (x - 3)cos(x) - 1.\n");
	printf("Управление:\n");
	printf("Стрелка вверх - промотать полотно вверх\n");
	printf("Стрелка вниз - промотать полотно вниз\n");
	printf("Стрелка влево - промотать полотно влево\n");
	printf("Стрелка вправо - промотать полотно вправо\n");
	printf("Плюс - увеличить масштаб\n");
	printf("Минус - уменьшить масштаб\n");
	printf("Эскейп - выход\n");
	system("pause");
	system("cls");
	int k = 30;
	background(hdc, k, pendots, penaxes, pendiv); // постноение начального полотна
	draw(hdc, k, pengraph); // постноение начального графика
	int key = 1; // нажатая клавиша
	while (key != ESC)
	{
		if (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			case DOWN: // перемещение оси х вверх
				Rectangle(hdc, 0, 0, xmax + 25, ymax + 50);
				y_0 -= 5;
				background(hdc, k, pendots, penaxes, pendiv);
				draw(hdc, k, pengraph);
				break;
			case RIGHT: // перемещение оси у влево
				Rectangle(hdc, 0, 0, xmax + 25, ymax + 50);
				x_0 -= 5;
				background(hdc, k, pendots, penaxes, pendiv);
				draw(hdc, k, pengraph);
				break;
			case LEFT: // перемещение оси у вправо
				Rectangle(hdc, 0, 0, xmax + 25, ymax + 50);
				x_0 += 5;
				background(hdc, k, pendots, penaxes, pendiv);
				draw(hdc, k, pengraph);
				break;
			case UP: // перемещение оси х вниз
				Rectangle(hdc, 0, 0, xmax + 25, ymax + 50);
				y_0 += 5;
				background(hdc, k, pendots, penaxes, pendiv);
				draw(hdc, k, pengraph);
				break;
			case PLUS: // увеличить масштаб относительно центра экрана
				Rectangle(hdc, 0, 0, xmax + 25, ymax + 50);
				if (k < 100)
				{
					x_0 = x_0 + (int)(3 * (x_0 - (double)(xmax) / 2) / k); // движение осей так, чтоб изменение размера было относительно центра
					y_0 = y_0 + (int)(3 * (y_0 - (double)(ymax) / 2) / k);
					k += 3;
				}
				background(hdc, k, pendots, penaxes, pendiv);
				draw(hdc, k, pengraph);
				break;
			case MINUS: // уменьшить масштаб относительно центра экрана
				Rectangle(hdc, 0, 0, xmax + 25, ymax + 50);
				if (k > 10)
				{
					x_0 = x_0 - (int)(3 * (x_0 - (double)(xmax) / 2) / k); // движение осей так, чтоб изменение размера было относительно центра
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