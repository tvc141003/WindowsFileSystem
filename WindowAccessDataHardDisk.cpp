#include <windows.h>
using namespace std;
#include<iostream>
#include <stdio.h>
#include<sstream>
#include<string>

unsigned ConvertByteToString(BYTE tempBuf)
{
    std::stringstream ss;

    int it = int(tempBuf);
    ss << std::hex << it;

    unsigned result;
    ss >> result;

    return result;
}

int ReadSector(LPCWSTR  drive, int readPoint, BYTE sector[512])
{
    int retCode = 0;
    DWORD bytesRead;
    HANDLE device = NULL;

    device = CreateFile(drive,    // Drive to open
        GENERIC_READ,           // Access mode
        FILE_SHARE_READ | FILE_SHARE_WRITE,        // Share Mode
        NULL,                   // Security Descriptor
        OPEN_EXISTING,          // How to create
        0,                      // File attributes
        NULL);                  // Handle to template

    if (device == INVALID_HANDLE_VALUE) // Open Error
    {
        printf("CreateFile: %u\n", GetLastError());
        system("pause");
        return 1;
    }

    SetFilePointer(device, readPoint, NULL, FILE_BEGIN);//Set a Point to Read

    if (!ReadFile(device, sector, 512, &bytesRead, NULL))
    {
        printf("ReadFile: %u\n", GetLastError());
    }
    else
    {
        printf("Success!\n");
        for (int i = 0; i < 512; i++)
        {

            // create a row after every 16 
            // columns so that display 
            // looks good 
            if (0 == i % 16)
            {
                printf("\n");
            }
           
            BYTE b = sector[i];
          //  string rs = ConvertByteToString(b);
          //  cout << rs << " ";
            //printf("d ", isascii(b) ? int(b) : '1');
            cout << std::hex << ConvertByteToString(b)<<" ";

        }
        system("pause");
    }
}
