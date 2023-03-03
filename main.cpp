#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <iomanip>

#include "BootSector.h"
#include "IValueMapper.h"
#include "BootSectorMapper.h"
#include "FatTableMapper.h"
#include "Utils.h"
#include "FatTable.h"

using namespace std;

string ConvertByteToString(BYTE tempBuf)
{
    std::stringstream ss;

    int it = int(tempBuf);
    ss << std::hex << setw(2) << setfill('0') << it;

    string result;
    result = ss.str();
    return result;
}

bool isZeroLastByte(string** sectors) {
    stringstream buffer;
    for (int i = SECTOR_COLUMN-1; i >= SECTOR_COLUMN - 4; i--) 
        buffer << sectors[SECTOR_ROW - 1][i];
    string lastByte = buffer.str();
    
    return lastByte == "00000000" ? true : false;
}


string** ReadSector(LPCWSTR drive, int readPoint, BYTE sector[512])
{
    int retCode = 0;
    DWORD bytesRead;
    HANDLE device = NULL;

    device = CreateFile(
        drive,    // Drive to open
        GENERIC_READ,           // Access mode
        FILE_SHARE_READ | FILE_SHARE_WRITE,        // Share Mode
        NULL,                   // Security Descriptor
        OPEN_EXISTING,          // How to create
        0,                      // File attributes
        NULL);                  // Handle to template

    if (device == INVALID_HANDLE_VALUE) // Open Error
    {
        printf("CreateFile: %u\n", GetLastError());
        return NULL;
    }

    SetFilePointer(device, readPoint, NULL, FILE_CURRENT);//Set a Point to Read

    if (!ReadFile(device, sector, 512, &bytesRead, NULL))
    {
        printf("ReadFile: %u\n", GetLastError());
        return NULL;
    }
    else
    {
        printf("Success!\n");
        //push sector to array 32*16 = 512 byte;
        string** sectors = new string * [SECTOR_ROW];
        for (int i = 0; i < SECTOR_ROW; i++)
            sectors[i] = new string[SECTOR_COLUMN];
        int sectorsRow = 0;
        int sectorsColumn = 0;
        for (int i = 0; i < 512; i++)
        {
            //new row after enough 16 column
            if (0 == i % 16 && i != 0)
            {
                sectorsRow++;
                sectorsColumn = 0;
            }

            BYTE b = sector[i];
            sectors[sectorsRow][sectorsColumn] = ConvertByteToString(b);
            sectorsColumn++;
        }

        CloseHandle(device);
        return sectors;
    }

    return NULL;
}

BootSector* getBootSector() {
    BYTE sector[512];
    string** sectors = ReadSector(L"\\\\.\\G:", 0, sector);
    BootSector* bootSector = new BootSector(sectors);

    return bootSector;
}

FatTable* getFatTable() {
    BootSector* bootSector = getBootSector();
    IValueMapper* mapper = new BootSectorMapper;

    map<string, int> bootSectorMapper = mapper->mapper(bootSector);

    string** fatSector = NULL;
    int numberOfSector = 0;
    while (true) {
        cout << 1 << endl;
        BYTE sector[512];
        int readPoint = (bootSectorMapper["Sb"] + numberOfSector) * 512;
        string** sectors = ReadSector(L"\\\\.\\G:", readPoint, sector);
        
        //if table doesn't exiting -> create new table contain 1 sector;
        if (numberOfSector == 0) {
            fatSector = new string * [SECTOR_ROW];
            for (int i = 0; i < SECTOR_ROW; i++)
                fatSector[i] = new string[SECTOR_COLUMN];
            fatSector = sectors;
        }
        else {
            //fat table large than 1 sector
            //deep copy
            string** newFatSector = new string * [SECTOR_ROW * (numberOfSector + 1)];
            for (int i = 0; i < SECTOR_ROW * (numberOfSector + 1); i++)
                newFatSector[i] = new string[SECTOR_COLUMN];
            for (int i = 0; i < SECTOR_ROW * numberOfSector; i++)
                for (int j = 0; j < SECTOR_COLUMN; j++)
                    newFatSector[i][j] = fatSector[i][j];

            //swap pointer between 2 fat table and delete old fat table;
            string** temp = newFatSector;
            newFatSector = fatSector;
            fatSector = temp;

            for (int i = 0; i < SECTOR_ROW * numberOfSector; i++)
                delete[] newFatSector[i];
            delete[] newFatSector;

            //insert value into new fat table
            for (int i = SECTOR_ROW * numberOfSector; i < SECTOR_ROW * (numberOfSector + 1); i++)
                for (int j = 0; j < 16; j++) fatSector[i][j] = sectors[i - SECTOR_ROW * numberOfSector][j];
        }
        
        numberOfSector++;
        if (isZeroLastByte(sectors) == true) break;
    }

    FatTable* fatTable = new FatTable(numberOfSector, fatSector);
    return fatTable;
}

int main(int argc, char** argv)
{   
    BootSector* bootSector = getBootSector();
    bootSector->toString();

    IValueMapper* mapper = new BootSectorMapper;
    map<string, int> mpbootSector = mapper->mapper(bootSector);
    cout << mpbootSector["Sc"] << endl;
    cout << mpbootSector["Sb"] << endl;
    cout << mpbootSector["Nf"] << endl;
    cout << mpbootSector["Sv"] << endl;
    cout << mpbootSector["Sf"] << endl;
    cout << mpbootSector["ClusterBeginRDET"] << endl;

    FatTable* fatTable = getFatTable();
    cout << endl;
    fatTable->toString();

    delete mapper;
    mapper = new FatTableMapper;
    map<string, int> mpFatTable = mapper->mapper(fatTable);
    cout << endl << endl;
    for (int i = 0; i < 32 * 4 * 5; i++)
        cout << i << ' ' << mpFatTable[Utils::String::convertIntToString(i)] << endl;

    return 0;
}