#pragma once

struct stWAD
{
	int dword_00;
	int dword_04;
	int dword_08;
	int dword_0c;
	FILE *FileStream;
	char *dword_14;
	char *dword_18;
	void *Malloc1;
	int dword_20;
};


class WAD
{
public:
	int __cdecl WAD::ReadWad(char *FileName);
};
extern WAD wadload;
