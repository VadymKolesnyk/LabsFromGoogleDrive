#include <windows.h>
#include <conio.h>
#include <iostream>
#include <time.h>
#include <tchar.h>
#include <process.h>


const int amount = 5;

HANDLE folks[amount];

HANDLE left(int current)
{
	return folks[current];
}
HANDLE right(int current)
{
	return folks[(current + 1) % amount];
}
DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
	int phil_id = *(int*)lpParam;
	srand(phil_id);
	DWORD l, r;
	while (true)
	{
		l = WaitForSingleObject(left(phil_id), 0);
		if (l == WAIT_OBJECT_0)
		{
			r = WaitForSingleObject(right(phil_id), 0);
			if (r == WAIT_OBJECT_0)
			{
				printf("[%5d.%03d]\tPhilosopher %d is eating\n", clock() / 1000, clock()%1000, phil_id);

				Sleep(rand()%5000 + 1000);

				printf("[%5d.%03d]\tPhilosopher %d stopped eating\n", clock() / 1000, clock() % 1000, phil_id);

				SetEvent(right(phil_id));
			}
			SetEvent(left(phil_id));
			Sleep(1000);
		}
	}
	return 0;
}
void main()
{
	DWORD dwThreadId[amount], dwThrdParam[amount];
	HANDLE hThread[amount];
	for (int i = 0; i < amount; i++)
	{
		folks[i] = CreateEvent(NULL, FALSE, TRUE, L"folk" + i);
		if (folks[i] == NULL)
		{
			printf("ERROR");
			return;
		}
	}
	for (int i = 0; i < amount; i++)
	{
		dwThrdParam[i] = i;
		hThread[i] = CreateThread(NULL, 0, ThreadFunc, &dwThrdParam[i], 0, 	&dwThreadId[i]);
		if (hThread[i] == NULL)
		{
			printf("ERROR");
			return;
		}
	}
	_getch();

	for(HANDLE t : hThread)
		CloseHandle(t);
	for (HANDLE t : folks)
		CloseHandle(t);
	return;
}