#include "HandleRun.h"
#pragma once

struct MemoryFile
{
	int ID;
	int Position;
	int unk3;
};

union FileWrapperFile
{
	FILE *realFile;
	MemoryFile *memFile;
};

struct FileWrapper
{
	int Filesystem;
	FileWrapperFile File;
};


enum FileType
{
	Real = 0x1,
	Memory = 0x0,
};


void *__cdecl Wrapper(char *FileName, size_t *FileNamePointer, int a3);
FileWrapper *__cdecl File_Open(char *FileName, char *Mode);
int __cdecl ReadIntoPointer(void *Buffer, size_t ElementSize, size_t ElementCount, FileWrapper *File);
int __cdecl File_Tell(FileWrapper *a1);
char *__cdecl GetFullPath(char *FileName);
int __cdecl GetFileSystem(FileWrapper *a1);
int __cdecl File_Seek(FileWrapper *a1, int Offset, int Origin);
struct FileWrapper *__cdecl Mallocs(int a1);
char *__cdecl Compare_Strings(char *String1, char *String2);
int __cdecl JoinNameWithCDLetter(char *Buffer, char *a2);
char *__cdecl Convert_To_LocalPath(char *FullPath);
int __cdecl File_Close(FileWrapper *Block);
void __cdecl Close(FileWrapper *Block);
int __cdecl sub_4800F0(char *FullPath, char *Mode);

class FileWrappers {
public:
	void *__cdecl FileWrappers::Wrapper(char *FileName, size_t *FileNamePointer, int a3);
	void *FileWrappers::StrangeMath();
	Thingy *FileWrappers::ReadCFG(char *FileName);
};
extern FileWrappers wrap;