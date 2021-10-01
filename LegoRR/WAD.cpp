#include "stdafx.h"
#include "WAD.h"
#include <stdlib.h>  
#include <stdio.h>
#include <string>
#include "MainWin.h"

using std::string;

int __cdecl sub_48B760(FILE *Stream, char* a2);
WAD wadload;

int __cdecl WAD::ReadWad(char *FileName)
{
	int v1; // ebp
	stWAD *WADs = new stWAD;
	FILE *v3; // esi
	stWAD *v5; // eax
	stWAD *v6; // eax
	char *v7; // edi
	stWAD *v8; // eax
	char *v9; // edi
	void *v10; // esi
	stWAD *v11; // eax
	int v12; // ebp
	FILE *v13; // edi
	void *v14; // esi
	stWAD *v15; // eax
	int n; // esi
	stWAD *v17; // eax
	stWAD *v18; // eax
	int ii; // esi
	stWAD *WADs0; // eax
	stWAD *WADs1; // eax
	stWAD *WADs2; // eax
	void *WADs3; // esi
	int j; // esi
	stWAD *WADs5; // eax
	stWAD *WADs6; // eax
	int k; // esi
	stWAD *WADs8; // eax
	stWAD *WADs9; // eax
	stWAD *v30; // eax
	size_t v31; // esi
	int l; // esi
	stWAD *v33; // eax
	stWAD *v34; // eax
	int m; // esi
	stWAD *v36; // eax
	stWAD *v37; // eax
	stWAD *v38; // eax
	stWAD *v39; // eax
	stWAD *v40; // eax
	int i; // edi
	stWAD *v42; // eax
	stWAD *v43; // eax
	stWAD *v44; // eax
	size_t v45; // [esp-8h] [ebp-1024h]
	FILE *Stream; // [esp+10h] [ebp-100Ch]
	unsigned int v47; // [esp+14h] [ebp-1008h]
	unsigned int v48; // [esp+14h] [ebp-1008h]
	char Buffer[4]; // [esp+18h] [ebp-1004h] BYREF
	char v50[4096]; // [esp+1Ch] [ebp-1000h] BYREF

	v1 = 0;

	if (WADs == (stWAD *)-1)
		return -1;
	v3 = fopen(FileName, "rb");
	Stream = v3;
	WADs->FileStream = v3;
	if (!v3)
		return -1;
	WADs->dword_04 = 1;
	if (fread(Buffer, 1u, 4u, v3) != 4)
	{
	NOTVALIDWAD:
		fclose(v3);
		return -1;
	}
	if (memcmp(Buffer, "WWAD", 4))
	{
	LABEL_6:
		fclose(Stream);
		return -1;
	}
	v3 = Stream;
	v5 = WADs;
	if (fread(&v5->dword_20, 1u, 4u, Stream) != 4)
		goto NOTVALIDWAD;
	v6 = WADs;
	//v7 = (char *)malloc(4 * v6->dword_20);
	//WADs->dword_18 = v7;
	v8 = WADs;
	//v9 = (char *)malloc(4 * v8->dword_20);
	//WADs->dword_14 = v9;
	int size = v6->dword_20;
	WADs->dword_18.clear();
	WADs->dword_18.reserve(size);
	WADs->dword_14.clear();
	WADs->dword_14.reserve(size);
	if (!WADs->dword_18.empty() || !WADs->dword_14.empty())
	{
		fclose(Stream);
		if (!WADs->dword_14.empty())
		{
			WADs->dword_14.clear();
		}
		return -1;
	}
	v47 = 4 * WADs->dword_20;
	//memset(WADs->dword_18, 1, v47);
	v48 = 4 * WADs->dword_20;
	//memset(WADs->dword_14, 0, v48);

	//*&WADs->dword_18 = new string[size];
	if (WADs->dword_20 > 0)
	{

		while (sub_48B760(v3, v50))
		{
			//v10 = malloc(strlen(v50) + 1);
			//((char *)*&WADs->dword_18)[v1] = (char)v10;
			//memset(WADs->dword_18, 1, strlen(v50) + 1);
			WADs->dword_18.insert(WADs->dword_18.begin() + v1, v50);
			//strcpy(((char **)&WADs->dword_18)[v1], v50);
			v11 = WADs;
			//char potato = (*&v11->dword_18)[v1++];
			v1++;
			//Main.Error_Handle("%s\n", (*&v11->dword_18)[v1++]);
			if (v1 >= WADs->dword_20)
				goto LABEL_15;
			v3 = Stream;
		}
		if (!WADs->dword_18.empty())
		{
			for (i = 0; i < WADs->dword_20; ++i)
			{
				if (WADs->dword_18[i].c_str())
				{
					WADs->dword_18.erase(WADs->dword_18.begin() + i);
				}
			}
		}
		if (!WADs->dword_14.empty())
		{
			WADs->dword_14.clear();
		}
		goto NOTVALIDWAD;
	}
LABEL_15:
	v12 = 0;
	if (WADs->dword_20 <= 0)
	{
	LABEL_31:
		WADs2 = WADs;
		WADs3 = malloc(16 * WADs2->dword_20);
		WADs->Malloc1 = WADs3;
		if (!WADs->Malloc1)
		{
			if (!WADs->dword_14.empty())
			{
				for (j = 0; j < WADs->dword_20; ++j)
				{
					if (WADs->dword_18[j].c_str())
					{
						WADs5 = WADs;
						free(*(void **)&WADs5->dword_18[4 * j]);
					}
				}
				WADs6 = WADs;
				WADs6->dword_18.clear();
			}
			if (!WADs->dword_14.empty())
			{
				for (k = 0; k < WADs->dword_20; ++k)
				{
					if (WADs->dword_14[k].c_str())
					{
						WADs->dword_14.erase(WADs->dword_14.begin() + k);
					}
				}
				WADs->dword_14.clear();
			}
			goto LABEL_6;
		}
		v13 = Stream;
		v45 = 16 * WADs->dword_20;
		v30 = WADs;
		v31 = fread(v30->Malloc1, 1u, v45, Stream);
		if (v31 == 16 * WADs->dword_20)
			return (int)WADs;
		if (!WADs->dword_14.empty())
		{
			for (l = 0; l < WADs->dword_20; ++l)
			{
				if (!WADs->dword_18[l].empty())
				{
					v33 = WADs;
					v33->dword_18.erase(v33->dword_18.begin() + l);
				}
			}
			v34 = WADs;
			v34->dword_18.clear();
		}
		if (!WADs->dword_14.empty())
		{
			for (m = 0; m < WADs->dword_20; ++m)
			{
				if (WADs->dword_14[m].c_str())
				{
					v36 = WADs;
					free(*(void **)&v36->dword_14[4 * m]);
				}
			}
			WADs->dword_14.clear();
		}
		if (WADs->Malloc1)
		{
			v38 = WADs;
			free(v38->Malloc1);
		}
	LABEL_60:
		fclose(v13);
		return -1;
	}
	while (1)
	{
		v13 = Stream;
		if (!sub_48B760(Stream, v50))
			break;
		WADs->dword_14.insert(WADs->dword_14.begin() + v12, v50);
		//v14 = malloc(strlen(v50) + 1);
		//*&WADs->dword_14[4 * v12] = (char)v14;
		//strcpy(*(char **)&WADs->dword_14[4 * v12], v50);
		//v15 = WADs;
		//Main.Error_Handle("%s\n", *(const char **)&v15->dword_14[4 * v12++]);
		v12++;
		if (v12 >= WADs->dword_20)
			goto LABEL_31;
	}
	if (!WADs->dword_14.empty())
	{
		for (n = 0; n < WADs->dword_20; ++n)
		{
			if ((*&WADs->dword_18[n]).c_str())
			{
				v17 = WADs;
				free(*(void **)&v17->dword_18[4 * n]);
			}
		}
		v18 = WADs;
		v18->dword_18.clear();
	}
	if (WADs->dword_14.empty())
		goto LABEL_60;
	for (ii = 0; ii < WADs->dword_20; ++ii)
	{
		if (WADs->dword_14[ii].c_str())
		{
			WADs0 = WADs;
			free(*(void **)&WADs0->dword_14[4 * ii]);
		}
	}
	WADs->dword_14.clear();
	fclose(Stream);
	return -1;
}
int __cdecl sub_48B760(FILE *Stream, char* a2)
{
	char i; // al

	for (i = fgetc(Stream); i; i = fgetc(Stream))
		*a2++ = i;
	*a2 = 0;
	return 1;
}