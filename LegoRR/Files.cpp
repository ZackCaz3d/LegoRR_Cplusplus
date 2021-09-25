#include "stdafx.h"
#include "Files.h"
#include "MainWin.h"
#include "HandleRun.h"
#include <windows.h>

FileWrappers wrap;

struct StrangeCFG
{
	char *FileBuffer;
	char *UnknownChar1;
	char *UnknownChar2;
	int Unknown3;
	int Unknown4;
	int Unknown5;
	int Unknown6;
	int Unknown7;
};


void *__cdecl FileWrappers::Wrapper(char *FileName, size_t *FileLengthPointer, int a3) {
	char *Mode_R;
	FileWrapper *OpenedFile;
	FileWrapper *OpenedFileTemp;
	int ReadType;
	size_t ftell_pos;
	void *WholeFile; // ebx

	Mode_R = "rb";
	//if (!ReadType)
		//Mode_R = "r";
	OpenedFile = File_Open(FileName, Mode_R);
	OpenedFileTemp = OpenedFile;
	if (!OpenedFile)
		return 0;
	File_Seek(OpenedFile, 0, 2);
	ftell_pos = File_Tell(OpenedFileTemp);
	WholeFile = malloc(ftell_pos);
	if (!WholeFile)
	{
		File_Close(OpenedFileTemp);
		return 0;
	}
	File_Seek(OpenedFileTemp, 0, 0);
	ReadIntoPointer(WholeFile, 1u, ftell_pos, OpenedFileTemp);// Read WholeFile
	if (FileLengthPointer)
		*FileLengthPointer = ftell_pos;
	File_Close(OpenedFileTemp);
	return WholeFile;
}
FileWrapper *__cdecl File_Open(char *FileName, char *Mode) {
	
	int v3; // eax
	FILE *v6; // eax
	FILE *v7; // eax
	char *v8; // eax
	char CD_Path_File[260]; // [esp+10h] [ebp-104h] BYREF
	FileWrapper *FOPEN_Array;
	char *Full_File_Path;
	Full_File_Path = GetFullPath(FileName);
	v3 = 1;//sub_4800F0(&Full_File_Path, Mode);
	if (v3)
	{
		if (v3 != 1)
		{
			Main.Error_Handle(
				"%s(%i) : Error in call to %s\n",
				"C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c",
				330,
				"File_Open");
			free(Full_File_Path);
			return 0;
		}
		FOPEN_Array = Mallocs(1);
		
		if (!FOPEN_Array) {
			free(Full_File_Path);
			return 0;
		}
		v6 = fopen(Full_File_Path, Mode);
		FOPEN_Array->File.realFile = v6;
		if (v6)
		{
			free(Full_File_Path);
			return FOPEN_Array;
		}
		if (!Compare_Strings(Mode, "w"))
		{
			if (JoinNameWithCDLetter(CD_Path_File, FileName))
			{
				v7 = fopen(CD_Path_File, Mode);
				FOPEN_Array->File.realFile = v7;
				if (v7) {
					free(Full_File_Path);
					return FOPEN_Array;
				}
			}
		}
		//goto NOCD;
	}
	/**
	FOPEN_Array = Mallocs(0);
	if (FOPEN_Array)
	{
		v8 = Convert_To_LocalPath(Full_File_Path);
		if (sub_480160(FOPEN_Array->File.memFile, v8))
		{
			Convert_To_LocalPath(Full_File_Path);
			return FOPEN_Array;
		}
		Convert_To_LocalPath(Full_File_Path);
	NOCD:
		sub_480210(FOPEN_Array);
	}
	**/
	free(Full_File_Path);
	return 0;
}
int __cdecl ReadIntoPointer(void *Buffer, size_t ElementSize, size_t ElementCount, FileWrapper *Fi)
{
	int IsRealFile; // eax
	int result; // eax
	signed int v6; // eax
	MemoryFile *v7; // esi
	int v8; // edx
	signed int v9; // ebp

	IsRealFile = GetFileSystem(Fi);
	if (IsRealFile)
	{
		if (IsRealFile == 1)
		{
			result = fread(Buffer, ElementSize, ElementCount, Fi->File.realFile);
		}
		else
		{
			Main.Error_Handle(
				"%s(%i) : Unknown file system in call to %s",
				"C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c",
				395,
				"ReadIntoPointer");
			result = 0;
		}
	}
	else
	{
		Main.Error_Handle(
			"%s(%i) : Memory Call Not Implemented %s",
			"C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c",
			395,
			"ReadIntoPointer");
		/**
		v6 = GetMemFileLength(File->File.memFile->ID);
		v7 = File->File.memFile;
		v8 = v7->Position;
		if ((v8 + ElementSize * ElementCount) <= v6)
			v9 = ElementSize * ElementCount;
		else
			v9 = v6 - v8;
		memcpy(Buffer, (File->File.memFile->Position + sub_48C2F0(v7->ID)), v9);
		File->File.memFile->Position += v9;
		result = v9 / ElementSize;
		**/
	}
	return result;
}
int __cdecl File_Tell(FileWrapper *a1)
{
	int FileSystem; // eax

	FileSystem = GetFileSystem(a1);
	if (!FileSystem)
		return a1->File.memFile->Position;
	if (FileSystem == 1)
		return ftell(a1->File.realFile);
	Main.Error_Handle(
		"%s(%i) : Unknown file system in call to %s",
		"C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c",
		469,
		"File_Tell");
	return 0;
}
char *GetFullPath(char *FileName)
{
	const char *SnippedFileName; // eax
	char *result; // eax
	char Buffer[260]; // [esp+4h] [ebp-104h] BYREF
	char* FullPath = (char*)malloc(sizeof(char) * 264);

	SnippedFileName = FileName;
	if (!FileName)
		goto FAIL;
	if (*FileName == '\\')
		SnippedFileName = FileName + 1;
	sprintf(Buffer, "%s\\%s", Main.Local_Data_Folder, SnippedFileName);
	if (_fullpath(FullPath, Buffer, 260u) && !strncmp(FullPath, Main.Local_Data_Folder, strlen(Main.Local_Data_Folder)))
		result = FullPath;
	else
		FAIL:
	result = 0;
	return result;
}
int __cdecl GetFileSystem(FileWrapper *a1)
{
	return a1->Filesystem;
}
int __cdecl File_Seek(FileWrapper *a1, int Offset, int Origin)
{
	int FileSystem; // eax
	int *v5; // edi
	FileWrapperFile v6; // esi
	MemoryFile *memFile; // edi
	FileWrapperFile v8; // esi

	FileSystem = GetFileSystem(a1);
	if (FileSystem)
	{
		if (FileSystem == 1)
			return fseek(a1->File.realFile, Offset, Origin);
		Main.Error_Handle(
			"%s(%i) : Unknown file system in call to %s",
			"C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c",
			368,
			"File_Seek");
		return 0;
	}
	/**
	switch (Origin)
	{
	case 0:
		a1->File.memFile->Position = Offset;
		memFile = a1->File.memFile;
		if (memFile->Position > GetMemFileLength(memFile->ID))
			a1->File.memFile->Position = GetMemFileLength(memFile->ID);
		v8.memFile = a1->File;
		if (v8.memFile->Position < 0)
			v8.memFile->Position = 0;
		return 0;
	case 1:
		a1->File.memFile->Position += Offset;
		v5 = &a1->File.memFile->ID;
		if (v5[1] > GetMemFileLength(*v5))
			a1->File.memFile->Position = GetMemFileLength(*v5);
		v6.memFile = a1->File;
		if (v6.memFile->Position < 0)
		{
			v6.memFile->Position = 0;
			return 0;
		}
		return 0;
	case 2:
		a1->File.memFile->Position = Offset + GetMemFileLength(a1->File.memFile->ID);
		break;
	default:
		Error_Handle("Uknown seek mode (%i)", Origin);
		break;
	}
	return 0;
	**/
}
FileWrapper *Mallocs(int a1)
{
	FileWrapper *MallocSucceed; // eax
	FileWrapper *v3; // esi
	void *MallocMoreSucceed; // eax

	if (a1 == 1)
	{
		FileWrapper *result = (FileWrapper*)malloc(8);
		result->Filesystem = 1;
		return result;
	}
	if (!a1)
	{
		MallocSucceed = (FileWrapper*)malloc(8);
		v3 = MallocSucceed;
		if (MallocSucceed)
		{
			MallocSucceed->Filesystem = 0;
			MallocMoreSucceed = malloc(12);
			v3->File.memFile = (MemoryFile*)MallocMoreSucceed;
			if (MallocMoreSucceed)
				return v3;
			operator delete(v3);
		}
	}
	return 0;
}
char *__cdecl Compare_Strings(char *String1, char *String2)
{
	char *v2; // esi
	int v3; // kr04_4
	int v4; // kr08_4
	int v5; // edi

	v2 = String1;
	v3 = strlen(String1) + 1;
	v4 = strlen(String2) + 1;
	if (v3 == 1 || v4 == 1)
		return 0;
	v5 = 0;
	while (_strnicmp(v2, String2, v4 - 1))
	{
		++v5;
		++v2;
		if (v5 >= v3 - 1)
			return 0;
	}
	return v2;
}
int __cdecl JoinNameWithCDLetter(char *Buffer, char *a2)
{
	if (!Main.LRR_CD_Letter[0])
		return 0;
	sprintf(Buffer, "%c:\\%s\\%s", Main.LRR_CD_Letter[0], "Data", a2);
	return 1;
}
char *__cdecl Convert_To_LocalPath(char *FullPath)
{
	int FullPathLen; // kr04_4
	int LocalPathLen; // kr08_4
	int v3; // ecx
	int v4; // edi
	char *result; // eax
	char v6; // bl
	char ConvertedPath[1024];

	if (!Main.FoundLocalData)
		return FullPath;
	FullPathLen = strlen(FullPath) + 1;
	LocalPathLen = strlen(Main.Coppied_LRR_DATA_LOCAL) + 1;
	v3 = LocalPathLen - 1;
	v4 = LocalPathLen - 1;
	if (FullPathLen - 1 <= LocalPathLen - 1)
		return FullPath;
	v6 = FullPath[v3];
	FullPath[v3] = 0;                             // SNIP
	if (_strcmpi(FullPath, Main.Coppied_LRR_DATA_LOCAL))
	{
		FullPath[v4] = v6;
		result = FullPath;
	}
	else
	{
		sprintf(ConvertedPath, "%s", &FullPath[LocalPathLen]);
		FullPath[v4] = v6;
		result = ConvertedPath;
	}
	return result;
}
/**
int __cdecl Unknown1(int a1)
{
	return 36 * a1 + 5727488;
}
int __cdecl Unknown2(int a1, int a2)
{
	return *(*(Unknown1(a1) + 28) + 16 * a2 + 8);
}
int __cdecl GetMemFileLength(MemoryFile *a1)
{
	return Unknown2(dword_5766A8[4 * a1], dword_5766AC[4 * a1]);
}
**/
int __cdecl File_Close(FileWrapper *Block)
{
	int FileInt; // eax
	int result; // eax

	FileInt = GetFileSystem(Block);
	if (FileInt < 0 || FileInt > 1)
	{
		Main.Error_Handle(
			"%s(%i) : Unknown file system in call to %s",
			"C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c",
			431,
			"File_Close");
		result = 0;
	}
	else
	{
		Close(Block);
		result = 0;
	}
	return result;
}
void __cdecl Close(FileWrapper *Block)
{
	MemoryFile *MemFile; // eax

	if (Block)
	{
		if (GetFileSystem(Block) == 1)
		{
			if (Block->File.realFile)
			{
				fclose(Block->File.realFile);
				operator delete(Block);
				return;
			}
		}
		else
		{
			/**
			if (GetFileSystem(Block))
				return;
			MemFile = Block->File.memFile;
			if (MemFile)
			{
				sub_48C280(MemFile->ID);
				operator delete(Block->File.memFile);
			}
			**/
			Main.Error_Handle(
				"%s(%i) : MemFile Not Implimented %s",
				"C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c",
				368,
				"Close");
		}
		operator delete(Block);
	}
}
int __cdecl sub_4800F0(char *FullPath, char *Mode)
{
	char *v2; // eax
	int v4; // [esp-4h] [ebp-Ch]

	if (!FullPath || !Mode || !strlen(FullPath) || !strlen(Mode))
		return 2;
	if (*Mode == 'w' || *Mode == 'W')
		return 1;
	//v4 = dword_4ABF00;
	//v2 = Convert_To_LocalPath(FullPath);
	//return sub_48C010(v2, v4) == -1;
	return 1;
}

void *FileWrappers::StrangeMath()
{
	int v0; // esi
	int v1; // edi
	void *result; // eax
	Thingy *VoidPointer; // edx
	Thingy *EndVoidPointer; // eax
	int v5; // ecx

	v0 = 1 << handleRun.Strange2;
	v1 = 1 << handleRun.Strange2;
	result = malloc(v1 * 32);
	handleRun.StrangeMemset[handleRun.Strange2] = (Thingy *)result;
	VoidPointer = handleRun.StrangeMemset[handleRun.Strange2];
	if (VoidPointer)
	{
		++handleRun.Strange2;
		if (v0 > 1)
		{
			EndVoidPointer = VoidPointer + 1;
			v5 = v0 - 1;
			do
			{
				EndVoidPointer[-1].Next = EndVoidPointer;
				++EndVoidPointer;
				--v5;
			} while (v5);
		}
		result = (void *)handleRun.Strange1;
		VoidPointer[v1 - 1].Next = (Thingy *)handleRun.Strange1;
		handleRun.Strange1 = VoidPointer;
	}
	return result;
	}
Thingy *__cdecl SetupThingy(Thingy *a1)
{
	Thingy *result; // eax
	int v2; // edx

	if (!handleRun.Strange1)
		wrap.StrangeMath();
	result = handleRun.Strange1;
	handleRun.Strange1 = handleRun.Strange1->Next;
	result->Next = result;
	result->Item = 0;
	result->Value = 0;
	result->TwoAhead = 0;
	if (a1)
	{
		a1->TwoAhead = result;
		result->Previous = a1;
		v2 = a1->Depth;
		result->CFG = 0;
		result->Depth = v2;
	}
	else
	{
		result->Depth = 0;
		result->Previous = 0;
	}
	return result;
}
Thingy *FileWrappers::ReadCFG(char *FileName)
{
	Thingy *LinkedListStart; // ebp
	int semi_NewLine; // ebx
	char *LegoCFG; // esi
	Thingy *Thingy; // eax
	int NameLength; // edi
	char *i; // edx
	char LegoCFG_PTR; // cl
	char *LegoCFG2; // esi
	int FilePosition; // edi
	int Depth; // ecx

	LinkedListStart = 0;
	semi_NewLine = 0;
	LegoCFG = (char *)wrap.Wrapper(FileName, (size_t *)&FileName, 1);
	if (LegoCFG)
	{
		Thingy = SetupThingy(0);
		LinkedListStart = Thingy;
		NameLength = 0;
		Thingy->CFG = LegoCFG;
		i = FileName;
		if (FileName)
		{
			do
			{
				LegoCFG_PTR = *LegoCFG;
				if (*LegoCFG == ';')
				{
					semi_NewLine = 1;
				}
				else if (LegoCFG_PTR == '\n')
				{
					semi_NewLine = 0;
				}
				if (semi_NewLine || LegoCFG_PTR == '\t' || LegoCFG_PTR == '\n' || LegoCFG_PTR == '\r' || LegoCFG_PTR == ' ')
				{
					*LegoCFG = 0;
					i = FileName;
				}
				++LegoCFG;
				++NameLength;
			} while (NameLength < (unsigned int)i);
		}
		LegoCFG2 = Thingy->CFG;
		FilePosition = 0;
		if (i)
		{
			while (!*LegoCFG2)
			{
				++LegoCFG2;
			CheckEnd:
				if (++FilePosition >= (int)i)
					return LinkedListStart;
			}
			if (*LegoCFG2 != '}' || LegoCFG2[1])
			{
				if (!Thingy->Item)
				{
					Thingy->Item = LegoCFG2;
					goto LABEL_25;
				}
				Thingy->Value = LegoCFG2;
				Thingy = SetupThingy(Thingy);
				if (*LegoCFG2 != '{' || LegoCFG2[1])
				{
				LABEL_25:
					for (i = FileName; FilePosition < (unsigned int)FileName; ++FilePosition)
					{
						if (!*LegoCFG2++)
							break;
					}
					goto CheckEnd;
				}
				Depth = Thingy->Depth + 1;
			}
			else
			{
				Depth = Thingy->Depth - 1;
			}
			Thingy->Depth = Depth;
			goto LABEL_25;
		}
	}
	return LinkedListStart;
}