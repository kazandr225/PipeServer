//код сервера
#define _CRT_SECURE_NO_WARNINGS
#define SIZE_BUFFER 140

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
char* itoa(int value, char* buffer, float radix);
double atof(const char* str);

int main()
{
	system("chcp 1251>nul");
	
	//запускаем консоль в фоновом режиме
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	HANDLE hNamedPipe;
	LPSTR lpszPipeName = L"\\\\.\\pipe\\MyPipe";
	DWORD size_buffer = SIZE_BUFFER;
	LPWSTR buffer = (CHAR*)calloc(size_buffer, sizeof(CHAR));
	char res[SIZE_BUFFER];
	char message[SIZE_BUFFER];
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
		Connected = ConnectNamedPipe(hNamedPipe, NULL); //Установка соединения клиента с каналом
		if (Connected)
		{
			//printf("\nКлиент успешно подключился\n");
				
			SuccessRead = ReadFile(hNamedPipe, buffer, size_buffer, &actual_readen, NULL);
				printf("\nКлиент пишет: \n");
				printf(buffer);
				printf("\n");
				
				//Переводим в число и считаем
				
				//char* Str = buffer;
				
				/*Num = atoi(Str);
				
				char string[25];
				itoa(res, string,10);*/

				/*char g;
				char c[50];
				g = atof(res);*/
				float Num = atof(buffer);

				if (Num = atof(buffer))
				{
					sprintf(message, "%g", Num * Num);
					//_itoa(Num, buffer, 10);
					buffer = &message;
					WriteFile(hNamedPipe, message, size_buffer, &actual_readen, NULL);
				}
				else
				{
					WriteFile(hNamedPipe, "Некорректное значение", size_buffer, &actual_readen, NULL);
				}
				//Отвечаем клиенту
				/*printf("\nВведите сообщение для клиента: \n");*/
				
				/*gets(message);
				buffer = &message;*/

				/*gets(res);
				buffer = &res;*/
				
				//WriteFile(hNamedPipe, buffer, size_buffer, &actual_readen, NULL);
				if (!SuccessRead)
				{
				printf("\nКлиент отключился от сервера\n");
				}
			CloseHandle(hNamedPipe); //закрываем канал
		}
	}
}
