#include <Windows.h>
#include <iostream>

using namespace std;

int cntr1 = 0, cntr2 = 0, cntr3 = 0;
HANDLE hTh01, hTh02, hTh03;

DWORD WINAPI thread01()
{
	while (true)
	{
		cntr1++;
		Sleep(150);
	}

	return 0;
}

DWORD WINAPI thread02()
{
	while (true)
	{
		cntr2++;
		Sleep(350);
	}

	return 0;
}

DWORD WINAPI thread03()
{
	while (true)
	{
		cntr3++;
		Sleep(650);
	}

	return 0;
}



int main()
{
	int k1 = 0, k2 = 0, k3 = 0;
	DWORD IDThread01, IDThread02, IDThread03;

	hTh01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread01, NULL, 0, &IDThread01);
	if (hTh01 == NULL)
	{
		int err = GetLastError();
		cout << "There is an error while hTh1 thread creating: " << err << endl;
		return err;
	}

	hTh02 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread02, NULL, 0, &IDThread02);
	if (hTh02 == NULL)
	{
		int err = GetLastError();
		cout << "There is an error while hTh2 thread creating: " << err << endl;
		return err;
	}

	hTh03 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread03, NULL, 0, &IDThread03);
	if (hTh03  == NULL)
	{
		int err = GetLastError();
		cout << "There is an error while hTh3 thread creating: " << err << endl;
		return err;
	}

	char ch;
	do {
		cout << "Press 'q' to terminate threads" << endl;
		cout << "Press 's' to terminate max thread" << endl;
		cin >> ch;

		switch (ch)
		{
		case 's':
			if (k1 == 1 && k2 == 1 && k3 == 1)
			{
				cout << "All threads were terminated" << endl;
				system("pause");
				return 0;
			}
			if (cntr1 >= cntr2 && cntr1 >= cntr3)
			{
				TerminateThread(hTh01, 0);
				CloseHandle(hTh01);
				cout << "Thread01 was terminated" << endl;
				k1 = 1;
				cntr1 = 0;
			}
			else if (cntr2 >= cntr1 && cntr2 >= cntr3)
			{
				TerminateThread(hTh02, 0);
				CloseHandle(hTh02);
				cout << "Thread02 was terminated" << endl;
				k2 = 1;
				cntr2 = 0;
			}
			else
			{
				TerminateThread(hTh03, 0);
				CloseHandle(hTh03);
				cout << "Thread03 was terminated" << endl;
				k3 = 1;
				cntr3 = 0;
			}
			break;
		default:
			break;
		}
	} while (ch != 'q');


	if (k1 == 0)
	{
		TerminateThread(hTh01, 0);
		CloseHandle(hTh01);
		cout << "Thread01 was terminated" << endl;
	}
	if (k2 == 0)
	{
		TerminateThread(hTh02, 0);
		CloseHandle(hTh02);
		cout << "Thread02 was terminated" << endl;
	}
	if (k3 == 0)
	{
		TerminateThread(hTh03, 0);
		CloseHandle(hTh03);
		cout << "Thread03 was terminated" << endl;
	}

	system("pause");
	return 0;
}
