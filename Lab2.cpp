#include <windows.h>
#include <iostream>
using namespace std;

struct employee
{
	char full_name[50];
	int depart_number;
	char job_post[30];
	int job_start_date;
};

void PrintFileInfo()
{
	printf_s("All information from file \"File_New.dat\" :\n");					

	LPCWSTR fn = L"File_New.dat";												

	HANDLE File = CreateFile(
		fn,																		
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	employee object;															
	DWORD n;																	

	while (ReadFile(File, &object, sizeof(object), &n, NULL) && n != 0)
	{
		printf_s("%s\n%d\n%s\n%d\n\n", object.full_name, object.depart_number, object.job_post, object.job_start_date);
	}

	CloseHandle(File);														
}

int main()
{
	PrintFileInfo();															

	printf_s("Now, enter the number of structure to be changed: ");			

	int structure_num = 0;														
	scanf_s("%d", &structure_num);												

	char buffer[1000];														

	sprintf_s(buffer, "%s %d", "Daughter.exe", structure_num);					

	STARTUPINFOA Daughter;
	ZeroMemory(&Daughter, sizeof(Daughter));									
	Daughter.cb = sizeof(Daughter);												
	PROCESS_INFORMATION Daughter_Info;
	ZeroMemory(&Daughter_Info, sizeof(Daughter_Info));							

	CreateProcessA(NULL,
		buffer,																	
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&Daughter,
		&Daughter_Info
	);

	printf_s("\nWaiting until process Daughter finishes his work...\n");		

	WaitForSingleObject(Daughter_Info.hProcess, INFINITE);						

	printf_s("\nProcess Dauther finished his work! File information has been changed.\n\n");

	PrintFileInfo();															

	CloseHandle(Daughter_Info.hProcess);										
	CloseHandle(Daughter_Info.hThread);											

	return 0;
}