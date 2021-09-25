#include "stdafx.h"
#include "Start.h"
#include "HandleRun.h"
#include <Windows.h>
#include <mbctype.h>
#include <iostream>

using namespace std;

HandleRun handleRun;
int __initmbctable();

[[noreturn]] void main()
{
	LPSTR CommandLine;
	LPSTR CommandLineLoop;
	struct _STARTUPINFOA StartupInfo;
	int windowtype;
	HMODULE module;


	__initmbctable();
	CommandLine = GetCommandLineA();
	CommandLineLoop = CommandLine;
	if (*CommandLine == '"') {
		while (*++CommandLineLoop != '"' && *CommandLineLoop) 
		{
			if (_ismbblead(*CommandLineLoop))
				++CommandLineLoop;
		}
		if (*CommandLineLoop == '"')
			++CommandLineLoop;
	}else{
	  while (*CommandLineLoop > ' ')
		  ++CommandLineLoop;
	}
	while (*CommandLineLoop && *CommandLineLoop <= ' ')
		++CommandLineLoop;
	StartupInfo.dwFlags = 0;
	GetStartupInfoA(&StartupInfo);
	if ((StartupInfo.dwFlags & 1) != 0)
		windowtype = StartupInfo.wShowWindow;
	else
		windowtype = 10;
	module = GetModuleHandleA(0);
	handleRun.WinMain(module, 0, CommandLineLoop, windowtype);
}
int __initmbctable()
{
	return _setmbcp(-3);
}
