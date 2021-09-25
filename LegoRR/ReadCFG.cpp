#include "stdafx.h"
#include "ReadCFG.h"
#include "HandleRun.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

ReadCFG CFGLOADER;

int __cdecl sub_477700(char *Block, char *String, char *Colons);
vector<string> explode(const string& str, const char& ch);

Thingy *ReadCFG::P1(Thingy *LegoCFG, char *Path)
{
	int Depth_Variables; // eax
	Thingy *v3; // ebx
	int v4; // ebp
	BOOL v5; // eax
	size_t v6; // esi
	char *v7; // edx
	char i; // cl
	int v9; // ebp
	BOOL v10; // esi
	Thingy *j; // edi
	size_t v12; // edx
	char *v13; // ecx
	char k; // al
	Thingy *v16; // [esp+10h] [ebp-1A4h]
	int v17; // [esp+14h] [ebp-1A0h]
	int v18; // [esp+18h] [ebp-19Ch]
	char *Block; // [esp+20h] [ebp-194h]
	char *String1; // [esp+24h] [ebp-190h] BYREF

	v16 = 0;
	Block = (char *)malloc(strlen(Path) + 1);
	strcpy(Block, Path);
	std::string blockstring(Block);
	String1 = Block;
	Depth_Variables = sub_477700(Block, (char *)&String1, "::");
	std::vector<std::string> splits = explode(blockstring, '::');
	cout << splits[0].c_str();
	cout << (splits[0].c_str());
	cout << (splits[1].c_str());
	cout << (splits[2].c_str());
	v3 = LegoCFG;
	v4 = Depth_Variables;
	v17 = Depth_Variables;
	if (LegoCFG)
	{
		v18 = Depth_Variables - 1;
		while (1)
		{
			if (v3->Depth == v18)
			{
				v5 = 0;
				if (v4 == 1)
				{
					v6 = 0;
					v7 = v3->Item;
					for (i = *v7; i; ++v7)
					{
						if (i == 42)
							break;
						i = v7[1];
						++v6;
					}
					if (*v7 == 42)
						v5 = _strnicmp(String1, v3->Item, v6) == 0;
				}
				if (v5 || !_strcmpi((splits[v4-1].c_str()), v3->Item))
				{
					v9 = v18;
					v10 = 0;
					for (j = v3; j; j = j->Previous)
					{
						if (j->Depth == v9 - 1)
						{
							if (v9 == 1)
							{
								v12 = 0;
								v13 = j->Item;
								for (k = *v13; k; ++v13)
								{
									if (k == 42)
										break;
									k = v13[1];
									++v12;
								}
								if (*v13 == 42)
									v10 = _strnicmp(String1, j->Item, v12) == 0;
								v3 = LegoCFG;
							}
							if (!v10 && _strcmpi((splits[v9 - 1].c_str()), j->Item))
								break;
							--v9;
						}
					}
					if (!v9)
					{
						v16 = v3;
						if (!v10)
							break;
					}
					v4 = v17;
				}
			}
			LegoCFG = v3->TwoAhead;
			if (!LegoCFG)
				break;
			v3 = v3->TwoAhead;
		}
	}
	free(Block);
	return v16;
}
int __cdecl sub_477700(char *Block, char *String, char *Colons)
{
	char *v3Block; // esi
	int ColonLen; // ebx
	int v6; // ebp
	char *v7; // edi

	v3Block = Block;
	ColonLen = strlen(Colons);
	if (!*Block)
		return 0;
	v6 = 1;
	String = Block;
	
	if (*Block)
	{
		v7 = String + 4;
		do
		{
			if (!strncmp(Colons, v3Block, ColonLen))
			{
				*v3Block = 0;
				v7 = &v3Block[ColonLen];
				++v6;
				v7 += 4;
			}
		} while (*++v3Block);
	}
	return v6;
}
vector<string> explode(const string& str, const char& ch) {
	string next;
	vector<string> result;

	// For each character in the string
	for (string::const_iterator it = str.begin(); it != str.end(); it++) {
		// If we've hit the terminal character
		if (*it == ch) {
			// If we have some characters accumulated
			if (!next.empty()) {
				// Add them to the result vector
				result.push_back(next);
				next.clear();
			}
		}
		else {
			// Accumulate the next character into the sequence
			next += *it;
		}
	}
	if (!next.empty())
		result.push_back(next);
	return result;
}