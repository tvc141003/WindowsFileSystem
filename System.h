#pragma once
#include "ReadDirectoryTable.h"
#include "IValueMapper.h"
#include "FatTableMapper.h"
#include "BootSector.h"
#include"FatTable.h" 


inline string** ReadSector(LPCWSTR drive, int readPoint, BYTE sector[512])
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
      //  printf("Success!\n");
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
            sectors[sectorsRow][sectorsColumn] = Utils::String::ConvertByteToString(b);
            sectorsColumn++;
        }

        CloseHandle(device);
        return sectors;
    }

    return NULL;
}

inline BootSector* getBootSector() {
    BYTE sector[512];
    string** sectors = ReadSector(HARD_DISK, 0, sector);
    BootSector* bootSector = new BootSector(sectors);
    return bootSector;
}
