#include <windows.h>
#include <stdio.h>
#include <psapi.h>
#include <clocale>
struct ProcessInfo
{
	DWORD Id;
	WCHAR Name[MAX_PATH];
	WCHAR User[MAX_PATH];
	WCHAR Domain[MAX_PATH];
	DWORD State;
	DWORDLONG WorkingSetSize;
	DOUBLE TimePercent;
};

struct TimeInfo
{
	FILETIME kerTimeProc = { 0,0 };
	FILETIME userTimeProc = { 0,0 };
	FILETIME kerTimeSys = { 0,0 };
	FILETIME userTimeSys = { 0,0 };
};
void CutPath(WCHAR path[], DWORD size)
{
	DWORD length = wcslen(path);
	DWORD pos = 0;
	DWORD count = length;
	for (int i = length ; i >= 0; i--)
	{
		if (path[i] == '\\')
		{
			count = length - i;
			pos = i ;
			break;
		}
	}
	if (pos != 0)
	{
		for (DWORD i = 0; i < count; i++)
		{
			path[i] = path[pos + i + 1];
		}
	}
	if (count > size)
	{
		path[size] = '\0';
		path[size - 1] = path[size - 2] = path[size - 3] = '.';
	}
}
void GetProcessInfo(DWORD processID, ProcessInfo* current)
{
	WCHAR szProcessName[MAX_PATH] = L"-";
	WCHAR szProcessUserName[MAX_PATH] = L"-";
	WCHAR szProcessUserDomain[MAX_PATH] = L"-";
	WCHAR Buffer[MAX_PATH] = L"-";
	DWORD state = 0;
	DWORDLONG workingSetSize = 0;
	PROCESS_MEMORY_COUNTERS pmc;
	current->Id = processID;
	current->State = state;
	current->WorkingSetSize = workingSetSize;
	wcscpy_s(current->Name, Buffer);
	wcscpy_s(current->User, szProcessUserName);
	wcscpy_s(current->Domain, szProcessUserDomain);
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
		FALSE, processID);
	if (hProcess != NULL)
	{
		GetExitCodeProcess(	hProcess, &state);
		DWORD size = MAX_PATH;
		QueryFullProcessImageName(hProcess, 0, Buffer, &size);
		HANDLE tokenHandle;
		if (OpenProcessToken(hProcess, TOKEN_READ, &tokenHandle))
		{
			PTOKEN_USER user = NULL;
			DWORD length = 0;
			GetTokenInformation(tokenHandle, TokenUser, user, length, &length);
			user = (PTOKEN_USER)GlobalAlloc(GPTR, length);
			if (user)
			{
				if (GetTokenInformation(tokenHandle, TokenUser, user, length, &length))
				{
					SID_NAME_USE sidType;
					DWORD size = MAX_PATH;
					LookupAccountSid(NULL, user->User.Sid,
						szProcessUserName, &size,
						szProcessUserDomain, &size, &sidType);
				}
			}
			if (user)
				GlobalFree(user);
			CloseHandle(tokenHandle);
		}
		if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
		{
			workingSetSize = pmc.WorkingSetSize;
		}
		current->Id = processID;
		current->State = state;
		current->WorkingSetSize = workingSetSize;
		wcscpy_s(current->Name, Buffer);
		wcscpy_s(current->User, szProcessUserName);
		wcscpy_s(current->Domain, szProcessUserDomain);
		CloseHandle(hProcess);
	}
}
void PrintProcesses(ProcessInfo* processes, DWORD count)
{
	wprintf(L"+---------------+---------------------------------------+---------------+---------------+---------------+-----------+-----------+\n");
	wprintf(L"| %-13s | %-37s | %-13s | %-13s | %-13s | %-9s | %-9s |\n",
			L"Id", L"Name", L"User", L"Domain", L"State", L"Memory%", L"Time%");
	wprintf(L"+---------------+---------------------------------------+---------------+---------------+---------------+-----------+-----------+\n");
	WCHAR name[MAX_PATH];
	WCHAR state[MAX_PATH] = L"NOT ACTIVE";

	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);

	if (!GlobalMemoryStatusEx(&statex))
		return;
	DWORDLONG tph = statex.ullTotalPhys;
	for (DWORD i = 0; i < count; i++)
	{
		wcscpy_s(name, processes[i].Name);
		CutPath(name, 37);
		if (processes[i].State == 259)
		{
			wcscpy_s(state, L"STILL ACTIVE");
		}
		if (wcscmp(name, L"-"))
		{
			wprintf(L"| %13u | %-37s | %-13s | %-13s | %-13s | %8.3lf%% | %8.3lf%% |\n",
					processes[i].Id, name, processes[i].User, 
					processes[i].Domain, state, processes[i].WorkingSetSize * 100.0 /tph,
					processes[i].TimePercent);
		}
	}
	wprintf(L"+---------------+---------------------------------------+---------------+---------------+---------------+-----------+-----------+\n");
}
void GetTime(DWORD processID, TimeInfo* timeInfo)
{
	FILETIME idleTimeSys;
	FILETIME kernelTimeSys;
	FILETIME userTimeSys;

	FILETIME creationTimeProc;
	FILETIME exitTimeProc;
	FILETIME kernelTimeProc;
	FILETIME userTimeProc;
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
	if (hProcess != NULL)
	{
		GetProcessTimes(hProcess, &creationTimeProc, &exitTimeProc, &kernelTimeProc, &userTimeProc);
		GetSystemTimes(&idleTimeSys, &kernelTimeSys, &userTimeSys);
		timeInfo->kerTimeSys = kernelTimeSys;
		timeInfo->userTimeSys = userTimeSys;
		timeInfo->kerTimeProc = kernelTimeProc;
		timeInfo->kerTimeProc = userTimeProc;
	}
}
ULONGLONG operator -(const FILETIME& ftA, const FILETIME& ftB)
{
	LARGE_INTEGER a, b;

	a.LowPart = ftA.dwLowDateTime;
	a.HighPart = ftA.dwHighDateTime;

	b.LowPart = ftB.dwLowDateTime;
	b.HighPart = ftB.dwHighDateTime;
	return a.QuadPart - b.QuadPart;
}

void PrintMemoryInfo()
{
	SYSTEM_INFO sysInf;
	GetSystemInfo(&sysInf);
	wprintf(L"Number of processors:\t\t\t%u\n", sysInf.dwNumberOfProcessors);
	wprintf(L"The page size and the granularity:\t%u\n", sysInf.dwPageSize);
	MEMORYSTATUSEX statex;
	DWORDLONG DIV = 1024;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	wprintf(L"Percent of memory in use:\t\t%u %%\n", statex.dwMemoryLoad);
	wprintf(L"Total physical memory:\t\t\t%llu KB\n", statex.ullTotalPhys / DIV);
	wprintf(L"Free physical memory:\t\t\t%llu KB\n", statex.ullAvailPhys / DIV);
	wprintf(L"Total paging file:\t\t\t%llu KB\n", statex.ullTotalPageFile / DIV);
	wprintf(L"Free paging file:\t\t\t%llu KB\n", statex.ullAvailPageFile / DIV);
	wprintf(L"Total virtual memory:\t\t\t%llu KB\n", statex.ullTotalVirtual / DIV);
	wprintf(L"Free virtual memory:\t\t\t%llu KB\n", statex.ullAvailVirtual / DIV);
}

int main(int argc, char* argv[])
{
	LONG apdateTime = 60000;
	if (argc > 2)
	{
		wprintf(L"ARGUMENT ERROR\n");
		return -1;
	}
	if (argc == 2)
	{
		apdateTime = atol(argv[1]);
		if (apdateTime <= 0)
		{
			wprintf(L"ARGUMENT ERROR\n");
			return -2;
		}
	}
	setlocale(LC_ALL, "Russian");
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;
	while (true)
	{
		if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
			return 1;
		cProcesses = cbNeeded / sizeof(DWORD);
		ProcessInfo* Processes = new ProcessInfo[cProcesses];
		TimeInfo* OldTime = new TimeInfo[cProcesses];
		TimeInfo* NewTime = new TimeInfo[cProcesses];
		for (i = 0; i < cProcesses; i++)
		{
			GetProcessInfo(aProcesses[i], Processes + i);
			GetTime(aProcesses[i], OldTime + i);
		}
		Sleep(1000);
		for (i = 0; i < cProcesses; i++)
		{
			GetTime(aProcesses[i], NewTime + i);
		}
		for (i = 0; i < cProcesses; i++)
		{
			Processes[i].TimePercent = 100.0 * ((NewTime[i].kerTimeProc - OldTime[i].kerTimeProc) +
												(NewTime[i].userTimeProc - OldTime[i].userTimeProc)) /
												((NewTime[i].kerTimeSys - OldTime[i].kerTimeSys) +
												(NewTime[i].userTimeSys - OldTime[i].userTimeSys));
		}
		system("cls");
		PrintMemoryInfo();
		PrintProcesses(Processes, cProcesses);
		delete[] Processes;
		delete[] OldTime;
		delete[] NewTime;
		Sleep(apdateTime);
	}
	return 0;
}
