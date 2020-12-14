#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <time.h>

using namespace std;

const int cSize = 10;
volatile int arr[cSize];

void thread_1()
{
	HANDLE hMutex;
	if ((hMutex = OpenMutex(SYNCHRONIZE, FALSE, L"Mutex")) == NULL)
	{
		int error = GetLastError();
		cerr << "There is an error while mutex opening (thread_1): " << error << endl;
		return;
	}

	WaitForSingleObject(hMutex, INFINITE);
	srand(time(NULL));
	rand();
	for (int i = 0; i < cSize; i++)
	{
		arr[i] = rand() * 300 / (RAND_MAX) -150;
	}
	cout << "Origin array: " << endl;
	for (int i = 0; i < cSize; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	ReleaseMutex(hMutex);
}

void thread_2()
{
	HANDLE hMutex;
	if ((hMutex = OpenMutex(SYNCHRONIZE, FALSE, L"Mutex")) == NULL)
	{
		int error = GetLastError();
		cerr << "There is an error while mutex opening (thread_2): " << error << endl;
		return;
	}
	WaitForSingleObject(hMutex, INFINITE);

	for (int i = 0; i < cSize; i++)
	{
		if ((arr[i] >= 10 and arr[i] <= 99) or (arr[i] >= -99 and arr[i] <= -10)) {
			arr[i] = 0;
		}
	}

	cout << "Changed array:" << endl;
	for (int i = 0; i < cSize; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	ReleaseMutex(hMutex);
}

int main()
{
	HANDLE hMutex;
	if ((hMutex = CreateMutex(NULL, FALSE, L"Mutex")) == NULL)
	{
		int error = GetLastError();
		cerr << "There is an error while mutex creating: " << error << endl;
		return error;
	}

	HANDLE  hThread[2];
	DWORD   IDThread_1, IDThread_2;

	if ((hThread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_1, NULL, 0, &IDThread_1)) == NULL)
	{
		int error = GetLastError();
		cerr << "There is an error while thread_1 creating: " << error << endl;
		CloseHandle(hMutex);
		return error;
	}

	if ((hThread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_2, NULL, 0, &IDThread_2)) == NULL)
	{
		int error = GetLastError();
		cerr << "There is an error while thread_2 creating: " << error << endl;
		TerminateThread(hThread[0], 0);
		CloseHandle(hThread[0]);
		CloseHandle(hMutex);
		return error;
	}

	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hMutex);
	return 0;
}
