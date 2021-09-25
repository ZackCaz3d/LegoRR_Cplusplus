#include <Windows.h>
#pragma once
struct Thingy
{
	char *CFG;
	char *Item;
	char *Value;
	int Depth;
	int dword_10;
	Thingy *TwoAhead;
	Thingy *Previous;
	Thingy *Next;
};


class HandleRun {
public:
	int __stdcall HandleRun::WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
	int HandleRun::SetStranges();
	Thingy *Strange1;
	int Strange2;
	int Strange3;
	Thingy *StrangeMemset[32];
	Thingy *Global_LegoCFG;
};
extern HandleRun handleRun;