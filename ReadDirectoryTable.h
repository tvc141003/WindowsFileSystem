 #pragma once
#include <iomanip>
#include <Windows.h>

#include"Reader.h"
#include"BootSector.h"
#include"FatTable.h"
#include"Utils.h"
#include"SubEntry.h"
#include"MainEntry.h"
#include"DirectoryTable.h"
#include"IValueMapper.h"
#include"BootSectorMapper.h"
#include"RootDirectoryTable.h"
using std::stringstream, std::setw, std::setfill, std::byte;

#include"System.h"
class ReadDirectoryTable : public Reader
{
public:
	//Object* Read(int);
    ReadDirectoryTable()
    {

    }
    static  bool isEndOfDirectory(string** sector);
    Object* Read( long long );

};

//string ConvertByteToString(BYTE tempBuf);
//bool isEndOfFatTable(string** sectors);
//bool isEndOfDirectory(string** sector);
//string** ReadSector(LPCWSTR drive, int readPoint, BYTE sector[512]);
//BootSector* getBootSector();
//FatTable* getFatTable();
