#include <windows.h>
#include <conio.h>
#include <iostream>
#include <time.h>
#include <tchar.h>
#include <process.h>


const int readersN = 15;
const int writersN = 3;
int count = 0;
int writers_is_queue = 0;
PCRITICAL_SECTION door;
PCRITICAL_SECTION baze;
PCRITICAL_SECTION queue;


DWORD WINAPI ReaderFunc(LPVOID lpParam)
{
	int reader_id = *(int*)lpParam;
	srand((time(NULL) + reader_id * 1000) * 100000);
	while (true)
	{
		Sleep(3000 + rand() % 10000);
		if (!writers_is_queue)
		{
			EnterCriticalSection(door);
			if (count++ == 0)
				EnterCriticalSection(baze);
			printf("[%5d.%03d]\tReader %2d is reading\t\t\tAmount of readers:%d\n", clock() / 1000, clock() % 1000, reader_id, count);
			LeaveCriticalSection(door);

			Sleep(rand() % 2000 + 1000);

			EnterCriticalSection(door);
			if (--count == 0)
				LeaveCriticalSection(baze);
			printf("[%5d.%03d]\tReader %2d stopped reading\t\tAmount of readers:%d\n", clock() / 1000, clock() % 1000, reader_id, count);
			LeaveCriticalSection(door);
		}

	}

	return 0;
}
DWORD WINAPI WriterFunc(LPVOID lpParam)
{
	int writer_id = *(int*)lpParam;
	srand((time(NULL) + writer_id * 1000) * 1000 + 100000);
	while (true)
	{
		Sleep(rand() % 40000 + 10000);

		EnterCriticalSection(queue);
		writers_is_queue++;
		printf("[%5d.%03d]\t\t\t\t\t\t\t\t\t\tWriter %2d is comming\t\t\tAmount of writers in queue:%d\n", clock() / 1000, clock() % 1000, writer_id, writers_is_queue);
		LeaveCriticalSection(queue);
		EnterCriticalSection(baze);
		EnterCriticalSection(queue);
		writers_is_queue--; 
		printf("[%5d.%03d]\t\t\t\t\t\t\t\t\t\tWriter %2d is writting\t\t\tAmount of writers in queue:%d\n", clock() / 1000, clock() % 1000, writer_id, writers_is_queue);
		LeaveCriticalSection(queue);

		Sleep(rand() % 5000 + 5000);

		printf("[%5d.%03d]\t\t\t\t\t\t\t\t\t\tWriter %2d stopped writting\n", clock() / 1000, clock() % 1000, writer_id);
		LeaveCriticalSection(baze);
	}
	return 0;
}
void main()
{
	door = new CRITICAL_SECTION();
	baze = new CRITICAL_SECTION();
	queue = new CRITICAL_SECTION();
	InitializeCriticalSection(door);
	InitializeCriticalSection(baze);
	InitializeCriticalSection(queue);

	DWORD readerParam[readersN], writerParam[writersN];
	HANDLE readerThreads[readersN];
	HANDLE writerThreads[writersN];
	for (int i = 0; i < readersN; i++)
	{
		readerParam[i] = i;
		readerThreads[i] = CreateThread(NULL, 0, ReaderFunc, &readerParam[i], 0, NULL);
		if (readerThreads[i] == NULL)
		{
			printf("ERROR");
			return;
		}
	}
	for (int i = 0; i < writersN; i++)
	{
		writerParam[i] = i + 1;
		writerThreads[i] = CreateThread(NULL, 0, WriterFunc, &writerParam[i], 0, NULL);
		if (writerThreads[i] == NULL)
		{
			printf("ERROR");
			return;
		}
	}
	_getch();
	for (HANDLE t : readerThreads)
		CloseHandle(t);
	for (HANDLE t : writerThreads)
		CloseHandle(t);
	DeleteCriticalSection(door);
	DeleteCriticalSection(baze);
	DeleteCriticalSection(queue);
}