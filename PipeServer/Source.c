//��� �������

#define SIZE_BUFFER 140

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
char* itoa(int value, char* string, int radix);

int vozv(int num, int res)
{
	res = num * num;
}

int main()
{
	system("chcp 1251>nul");
	
	HANDLE hNamedPipe;
	LPSTR lpszPipeName = L"\\\\.\\pipe\\MyPipe";
	DWORD size_buffer = SIZE_BUFFER;
	LPWSTR buffer = (CHAR*)calloc(size_buffer, sizeof(CHAR));
	char res[SIZE_BUFFER];
	//char message[SIZE_BUFFER];
	BOOL Connected;
	DWORD actual_readen;
	BOOL SuccessRead;

	while (TRUE)
	{
		
		
		hNamedPipe = CreateNamedPipe(
			lpszPipeName,
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			SIZE_BUFFER,
			SIZE_BUFFER,
			INFINITE,
			NULL);
		Connected = ConnectNamedPipe(hNamedPipe, NULL); //��������� ���������� ������� � �������
		if (Connected)
		{
			//printf("\n������ ������� �����������\n");
				
			SuccessRead = ReadFile(hNamedPipe, buffer, size_buffer, &actual_readen, NULL);
			if (SuccessRead)
			{
				printf("\n������ �����: \n");
				printf(buffer);
				printf("\n");
				
				//��������� � ����� � �������
				char* Str = buffer;
				int Num = 0;
				Num = atoi(Str);
				int res = Num * Num;
				char string[25];
				itoa(res, string,10);

				char g;
				char c[50];
				g = atof(res);

				//�������� �������
				printf("\n������� ��������� ��� �������: \n");
				
				/*gets(message);
				buffer = &message;*/

				gets(res);
				buffer = &res;
				WriteFile(hNamedPipe, buffer, size_buffer, &actual_readen, NULL);
			}
			else
			{
				printf("\n������ ���������� �� �������\n");
			}
			CloseHandle(hNamedPipe); //��������� �����
		}
	}
}
