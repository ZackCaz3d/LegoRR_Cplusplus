// Testers.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "MainWin.h"
#include "HandleRun.h"
#include "Files.h"
#include <iostream>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <direct.h>
#include <Windows.h>
#include "ReadCFG.h"

using namespace std;

char *JoinWithColons(char *a1, char *a2, ...);
void PrintFloats(int n, ...);
std::string get_working_path();
int SetStranges();

int __stdcall HandleRun::WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	float a3;
	float a4;
	float a5;
	int NOSOUND = 0;
	int CDINSIST = 0;
	char Name[128];
	LPSTR CommandLineA;
	CHAR CommandLineAPTR;
	char *i;
	char *j;
	char LegoRR[256];
	char *LegoRRPTR;
	char LegoRR0;
	char *LegoRRTemp;
	char *exe_name_poitner;
	char Data[1024];
	char ARGS[1024];
	char HALMessage[1024];
	Thingy *thingtest;
	char *Main_ToolTipRGB;
	if (!"Lego Rock Raiders"
		|| (sprintf(Name, "%s Mutex", "Lego Rock Raiders"), CreateMutexA(0, 1, Name), GetLastError() != 183))
	{
		CommandLineA = GetCommandLineA();
		CommandLineAPTR = *CommandLineA;
		for (i = CommandLineA; CommandLineAPTR; ++CommandLineA)
		{
			if (CommandLineAPTR == '\\')
				i = CommandLineA + 1;
			CommandLineAPTR = CommandLineA[1];
		}
		strcpy(LegoRR, i);
		LegoRRPTR = LegoRR;
		if (LegoRR[0])
		{
			do
			{
				if (*LegoRRPTR == '"')
					*LegoRRPTR = 0;                              // String Cut
			} while (*++LegoRRPTR);
		}
		LegoRR0 = LegoRR[0];
		LegoRRTemp = LegoRR;
		for (j = LegoRR; LegoRR0; ++LegoRRTemp)
		{
			if (LegoRR0 == '.')
				j = LegoRRTemp + 1;
			LegoRR0 = LegoRRTemp[1];
		}
		if (j != LegoRR)
		{
			_strupr(j);
			exe_name_poitner = strstr(LegoRR, ".EXE");
			if (exe_name_poitner)
				*exe_name_poitner = 0;                  // String Cut
		}
		cout << LegoRR;
		if (Main.Create_Or_Get_Regkey_Short("SOFTWARE\\LEGO Media\\Games\\Rock Raiders", "StandardParameters", 0, (LPBYTE)Data, 1024))
			sprintf(ARGS, "%s %s", lpCmdLine, Data);
		else
			sprintf(ARGS, "%s", lpCmdLine);
		if (!Main.Create_Or_Get_Regkey_Short("SOFTWARE\\LEGO Media\\Games\\Rock Raiders", "NoHALMessage", 0,	(LPBYTE)HALMessage,	1024))
			sprintf(HALMessage, "No DirectX 3D accelerator could be found.");
		Main.Validity_Check(LegoRR, 1, "SOFTWARE\\LEGO Media\\Games\\Rock Raiders");
		SetStranges();
		handleRun.Global_LegoCFG = wrap.ReadCFG("Lego.cfg");
		if (handleRun.Global_LegoCFG) {
			Main_ToolTipRGB = JoinWithColons(LegoRR, "Main", "ToolTipRGB", 0);
			if (!CFGLOADER.CheckIfValueValid(Global_LegoCFG, Main_ToolTipRGB, &a3, &a4, &a5))
			{
				a5 = 0.32549021;
				a4 = 0.32549021;
				a3 = 0.32549021;
			}
			free(Main_ToolTipRGB);
		}
		return 0;
	}
}
char *JoinWithColons(char *a1, char *a2, ...)
{
	char *Main; // edx
	va_list ToolTipSRGB; // ebx
	const char *v4; // esi
	unsigned int v5; // edx
	char *v6; // edi
	char *v7; // edi
	const char *v8; // esi
	char v9; // cl
	char *val;
	int i;
	va_list va; // [esp+18h] [ebp+Ch] BYREF
	char *LEGORR = (char*)malloc(sizeof(char) * 256);
	va_start(va, a2);
	Main = a2;
	va_copy(ToolTipSRGB, va);
	strcpy(LEGORR, a1);
	if (a2)
	{
		do
		{
			//ToolTipSRGB += 4;
			strcat(LEGORR, "::");
			v4 = Main;
			v5 = strlen(Main) + 1;
			v6 = &LEGORR[strlen(LEGORR)];
			memcpy(v6, v4, 4 * (v5 >> 2));
			v8 = &v4[4 * (v5 >> 2)];
			v7 = &v6[4 * (v5 >> 2)];
			v9 = v5;
			Main = va_arg(ToolTipSRGB, char *);
			memcpy(v7, v8, v9 & 3);
		} while (Main);
	}
	return LEGORR;
}
void PrintFloats(int n, ...)
{
	int i;
	double val;
	printf("Printing floats:");
	va_list vl;
	va_start(vl, n);
	for (i = 0; i<n; i++)
	{
		val = va_arg(vl, double);
		printf(" [%.2f]", val);
	}
	va_end(vl);
	printf("\n");
}
std::string get_working_path()
{
	char temp[260];
	return (_getcwd(temp, sizeof(temp)) ? std::string(temp) : std::string(""));
}
int HandleRun::SetStranges()
{
	int result; // eax

	result = 0;
	memset(handleRun.StrangeMemset, 0, sizeof(handleRun.StrangeMemset));
	handleRun.Strange1 = 0;
	handleRun.Strange2 = 0;
	handleRun.Strange3 = 1;
	return result;
}