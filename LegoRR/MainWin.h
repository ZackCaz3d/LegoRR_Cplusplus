#include <Windows.h>

#pragma once

class MainWin {
public:
	char Local_Data_Folder[260];
	int FoundLocalData;
	char Coppied_LRR_DATA_LOCAL[1024];
	char LRR_CD_Letter[];
	FILE *__cdecl MainWin::Validity_Check(char *a1, int CDINSIST, char *Type);
	HKEY MainWin::Create_Or_Get_Regkey_Short(char *Type, LPCSTR lpValueName, int a4, LPBYTE lpData, DWORD cbData);
	void MainWin::Error_Handle(char *Format, ...);
};
extern MainWin Main;

