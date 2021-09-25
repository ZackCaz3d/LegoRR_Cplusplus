#pragma once
#include "HandleRun.h"
class ReadCFG
{
public:
	char *ReadCFG::GetValueFromThingy(Thingy *LegoCFG, char *Path);
	int ReadCFG::CheckIfValueValid(Thingy *LegoCFG, char *Path, float *a3, float *a4, float *a5);
};

extern ReadCFG CFGLOADER;