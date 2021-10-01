#include <string>
#include <vector>
#pragma once
using std::string;
using std::vector;

struct stWAD
{
	int dword_00;
	int dword_04;
	int dword_08;
	int dword_0c;
	FILE *FileStream;
	std::vector<std::string> dword_14;
	std::vector<std::string> dword_18;
	void *Malloc1;
	int dword_20;
};


class WAD
{
public:
	int __cdecl WAD::ReadWad(char *FileName);
};
extern WAD wadload;
