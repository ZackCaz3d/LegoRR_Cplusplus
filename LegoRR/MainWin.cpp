#include "stdafx.h"
#include "MainWin.h"
#include "WAD.h"
#include <io.h>
#include <windows.h>
#include <direct.h>

MainWin Main;

int __cdecl NotSure(const char *LRR_DATA);
int Get_Cd_Letter();
HKEY __cdecl Create_Or_Get_Regkey_Short(char *Type, LPCSTR lpValueName, int a4, LPBYTE lpData, DWORD cbData);
HKEY __cdecl Create_Or_Get_RegKey(HKEY hKey, char *Type, LPCSTR lpValueName, int a4, LPBYTE lpData, DWORD cbData);
char *__cdecl SetSubname(char *type, char *subkey);
FILE *__cdecl Validity_Check(char *a1, int CDINSIST, char *Type);



FILE *__cdecl MainWin::Validity_Check(char *a1, int CDINSIST, char *Type) {
	int EmptyWad; // ebx
	unsigned int i; // esi
	int Found_Cd; // eax
	intptr_t v6; // edi
	FILE *cd_key; // eax
	FILE *result; // eax
	bool HaveInvalidCD; // [esp+10h] [ebp-F24h]
	char WorkingDirectory[260]; // [esp+14h] [ebp-F20h] BYREF
	_finddata_t Buffer; // [esp+118h] [ebp-E1Ch] BYREF
	char LRR_Data_Path[260]; // [esp+230h] [ebp-D04h] BYREF
	char Caption[6]; // [esp+334h] [ebp-C00h] BYREF
	char v14[1016]; // [esp+33Ah] [ebp-BFAh] BYREF
	__int16 v15; // [esp+732h] [ebp-802h]
	char FileName[1024]; // [esp+734h] [ebp-800h] BYREF
	char Text[1024]; // [esp+B34h] [ebp-400h] BYREF
	

	EmptyWad = 0;
	HaveInvalidCD = 0;
	_getcwd(WorkingDirectory, 260);
	if (WorkingDirectory[strlen(WorkingDirectory) - 1] == '\\')
		WorkingDirectory[strlen(WorkingDirectory) - 1] = 0;
	sprintf(Main.Local_Data_Folder, "%s\\%s", WorkingDirectory, "Data");
	for (i = 0; i < 0xA; ++i)
	{
		sprintf((char *)&Buffer, "%s%i.wad", a1, i);
		if (wadload.ReadWad((char *)&Buffer) != -1)
			EmptyWad = 1;
	}
	_getcwd(LRR_Data_Path, 260);
	strcat(LRR_Data_Path, "\\Data");
	NotSure(LRR_Data_Path);
	Found_Cd = Get_Cd_Letter();
	while (!Found_Cd)
	{
		if (!CDINSIST)
			break;
		strcpy(Caption, "Error");
		memset(v14, 0, sizeof(v14));
		v15 = 0;
		if (Main.Create_Or_Get_Regkey_Short(Type, "CDMissing", 0, (LPBYTE)Text, 0x400u))
		{
			Main.Create_Or_Get_Regkey_Short(Type, "SetupError", 0, (LPBYTE)Caption, 0x400u);
			if (MessageBoxA(0, Text, Caption, 1u) != 2)
				continue;
		}
		exit(0);
		Found_Cd = Get_Cd_Letter();
	}
	if (!Found_Cd && !EmptyWad)
	{
		HaveInvalidCD = 1;
		v6 =_findfirst("*.*", &Buffer);
		if (v6 != -1)
		{
			while ((Buffer.attrib & 16) == 0 || _strcmpi(Buffer.name, "Data"))
			{
				if (_findnext(v6, &Buffer))
					goto LABEL_21;
			}
			HaveInvalidCD = 0;
		LABEL_21:
			_findclose((intptr_t)v6);
		}
	}
	if (CDINSIST)
	{
		sprintf(FileName, "%s\\%s", "Data", "cd.key");
		cd_key = fopen(FileName, "r");
		if (cd_key)
		{
			fclose(cd_key);
			HaveInvalidCD = 1;
		}
	}
	if (HaveInvalidCD)
	{
		strcpy(Caption, "Error");
		memset(v14, 0, sizeof(v14));
		v15 = 0;
		if (Main.Create_Or_Get_Regkey_Short(Type, "DataMissing", 0, (LPBYTE)Text, 0x400u))
		{
			Main.Create_Or_Get_Regkey_Short(Type, "SetupError", 0, (LPBYTE)Caption, 0x400u);
			MessageBoxA(0, Text, Caption, 0);
		}
		exit(0);
	}
	_mkdir("Data");
	sprintf(FileName, "%s\\%s", "Data", "delme.dat");
	result = fopen(FileName, "r");
	if (result)
	{
		fclose(result);
		_chmod(FileName, 128);
		result = (FILE *)remove(FileName);
	}
	return result;
}
int __cdecl NotSure(const char *LRR_DATA)
{
	int v1; // kr04_4
	int result; // eax

	if (!LRR_DATA || (v1 = strlen(LRR_DATA) + 1, v1 - 1 > 1024) || v1 == 1)
	{
		result = 0;
		Main.FoundLocalData = 0;
		memset(&Main.Coppied_LRR_DATA_LOCAL, 0, 0x400u);
	}
	else
	{
		strcpy(Main.Coppied_LRR_DATA_LOCAL, LRR_DATA);
		result = 1;
		Main.FoundLocalData = 1;
	}
	return result;
}
int Get_Cd_Letter()
{
	char CD_Drive_Letter; // bl
	FILE *LRRCdPointer; // eax
	char v3; // [esp+8h] [ebp-10Ch]
	char RootPathName[264]; // [esp+Ch] [ebp-108h] BYREF

	CD_Drive_Letter = 'C';
	strcpy(RootPathName, "A:\\");
	while (1)
	{
		RootPathName[0] = CD_Drive_Letter;
		if (GetDriveTypeA(RootPathName) == 5)
		{
			sprintf(&RootPathName[4], "%c:\\%s\\%s", CD_Drive_Letter, "Data", "cd.key");
			LRRCdPointer = fopen(&RootPathName[4], "r");
			if (LRRCdPointer)
				break;
		}
		CD_Drive_Letter = ++CD_Drive_Letter;
		if (CD_Drive_Letter > 'Z')
			return 0;
	}
	fclose(LRRCdPointer);
	Main.LRR_CD_Letter[0] = CD_Drive_Letter;
	return 1;
}
HKEY MainWin::Create_Or_Get_Regkey_Short(char *Type, LPCSTR lpValueName, int a4, LPBYTE lpData, DWORD cbData)
{
	return Create_Or_Get_RegKey(HKEY_LOCAL_MACHINE, Type, lpValueName, a4, lpData, cbData);
}
void MainWin::Error_Handle(char *Format, ...)
{
	CHAR OutputString[1024]; // [esp+0h] [ebp-400h] BYREF
	va_list ArgList; // [esp+408h] [ebp+8h] BYREF

	va_start(ArgList, Format);
	vsprintf(OutputString, Format, ArgList);
	OutputDebugStringA(OutputString);
}
HKEY __cdecl Create_Or_Get_RegKey(HKEY hKey, char *Type, LPCSTR lpValueName, int a4, LPBYTE lpData, DWORD cbData)
{
	char *Subkeyz; // esi
	HKEY result; // eax
	HKEY v8; // esi
	HKEY phkResult; // [esp+4h] [ebp-68h] BYREF
	CHAR SubKey[100]; // [esp+8h] [ebp-64h] BYREF

	Subkeyz = SetSubname(Type, SubKey);
	if (SubKey[0])
	{
		RegCreateKeyA(hKey, SubKey, &phkResult);
		result = phkResult;
		if (phkResult)
		{
			v8 = Create_Or_Get_RegKey(phkResult, Subkeyz, lpValueName, a4, lpData, cbData);
			RegCloseKey(phkResult);
			result = v8;
		}
	}
	else
	{
		Type = 0;
		if (!a4 || a4 == 1)
			result = (HKEY)(RegQueryValueExA(hKey, lpValueName, 0, (LPDWORD)&Type, lpData, &cbData) == 0);
		else
			result = 0;
	}
	return result;
}
char *__cdecl SetSubname(char *type, char *subkey)
{
	char *ForSubkeyPointer; // edx
	char *result; // eax
	char i; // cl

	ForSubkeyPointer = subkey;
	result = type;
	*subkey = 0;
	for (i = *type; *result; i = *result)
	{
		if (i == '\\')
			break;
		++result;
		*ForSubkeyPointer++ = i;
	}
	if (*result == '\\')
		++result;
	*ForSubkeyPointer = 0;
	return result;
}
