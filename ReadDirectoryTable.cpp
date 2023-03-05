

#include "ReadDirectoryTable.h"
bool ReadDirectoryTable::isEndOfDirectory(string** sector)
{
   
        stringstream buffer;
        for (int i = SECTOR_ROW - 1; i >= SECTOR_ROW - 2; i--)
            for (int j = SECTOR_COLUMN - 1; j >= 0; j--)
                buffer << sector[i][j];
        string lastEntry = buffer.str();

        for (int i = 0; i < lastEntry.length(); i++)
            if (lastEntry[i] != '0') return false;

        return true;
    
}

Object* ReadDirectoryTable::Read(int point)
{

    string** directory = NULL;
    int numberOfSector = 0;
    while (true) {
        BYTE sector[512];
        int readPoint = (numberOfSector + point) * 512;
        string** sectors = ReadSector(L"\\\\.\\E:", readPoint, sector);

        //if table doesn't exiting -> create new table contain 1 sector;
        if (numberOfSector == 0) {
            directory = new string * [SECTOR_ROW];
            for (int i = 0; i < SECTOR_ROW; i++)
                directory[i] = new string[SECTOR_COLUMN];
            directory = sectors;
        }
        else {
            //directory table large than 1 sector
            //deep copy
            string** newDirectory = new string * [SECTOR_ROW * (numberOfSector + 1)];
            for (int i = 0; i < SECTOR_ROW * (numberOfSector + 1); i++)
                newDirectory[i] = new string[SECTOR_COLUMN];
            for (int i = 0; i < SECTOR_ROW * numberOfSector; i++)
                for (int j = 0; j < SECTOR_COLUMN; j++)
                    newDirectory[i][j] = directory[i][j];

            //swap pointer between 2 directory table and delete old directory table;
            string** temp = newDirectory;
            newDirectory = directory;
            directory = temp;

            for (int i = 0; i < SECTOR_ROW * numberOfSector; i++)
                delete[] newDirectory[i];
            delete[] newDirectory;

            //insert value into new directory table
            for (int i = SECTOR_ROW * numberOfSector; i < SECTOR_ROW * (numberOfSector + 1); i++)
                for (int j = 0; j < 16; j++) directory[i][j] = sectors[i - SECTOR_ROW * numberOfSector][j];
        }

        numberOfSector++;
        if (ReadDirectoryTable::isEndOfDirectory(sectors) == true) break;
    }
    cout << endl;
   /* for (int i = 0; i < SECTOR_ROW * numberOfSector; i++) {
        for (int j = 0; j < SECTOR_COLUMN; j++) cout << directory[i][j] << " ";
        cout << endl;
    }*/
    //add Entry

    RootDirectoryTable* directoryTable = new RootDirectoryTable;
    int indexEntry = 0;
    while (indexEntry < numberOfSector * SECTOR_ROW) {
        //get entry = 2 row in directory table
        string entryTable[2][SECTOR_COLUMN];
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < SECTOR_COLUMN; j++) {
                entryTable[i][j] = directory[indexEntry + i][j];
            }

        if (Utils::Int::convertHexToDecimal(entryTable[0][11]) == SUB_ENTRY && entryTable[0][0] != DELETED_ENTRY) {
            //sub entry
            int identify = Utils::Int::convertHexToDecimal(entryTable[0][0]);
            string name = "";
            stringstream buffer;
            string hexString = "";
            //5 char unicode
            for (int i = 1; i <= 10; i += 2) {
                buffer << entryTable[0][i];
            }
            hexString = hexString + buffer.str();
            buffer.str("");

            //2 char offset E -> F
            for (int i = 14; i <= 15; i++)
                buffer << entryTable[0][i];
            hexString = hexString + buffer.str();
            buffer.str("");

            //10 char offset 10->19
            for (int i = 0; i <= 9; i++)
                buffer << entryTable[1][i];
            hexString = hexString + buffer.str();
            buffer.str("");

            //last 5 char from offset 1C -> 1F
            for (int i = 12; i <= 15; i++)
                buffer << entryTable[1][i];
            hexString = hexString + buffer.str();
            buffer.str("");

            name = Utils::String::convertHexToString(hexString);

            Entry* entry = new SubEntry(identify, name);
            directoryTable->entrys().push_back(entry);
        }
        else {
            if (entryTable[0][0] != "00" && entryTable[0][0]!= DELETED_ENTRY) {
                // main entry
                string hexString = "";

                stringstream buffer;

                // read head name
                for (int i = 0; i <= 7; i++)
                {
                    buffer << entryTable[0][i];
                }
                hexString = buffer.str();
                string Headname = Utils::String::convertHexToString(hexString);
                buffer.str("");
                // tail name ;
                for (int i = 8; i <= 10; i++)
                {
                    buffer << entryTable[0][i];
                }
                hexString = buffer.str();
                string Tailname = Utils::String::convertHexToString(hexString);
                buffer.str("");
                // Status 

                int Status = Utils::Int::convertHexToDecimal(entryTable[0][11]);

                // startCluster
                buffer << entryTable[1][5] << entryTable[1][4];

                long startCluster = Utils::Int::convertHexToDecimal(buffer.str());

                buffer.str("");
                if (startCluster == 0)
                {
                    buffer << entryTable[1][11] << entryTable[1][10];
                    startCluster = Utils::Int::convertHexToDecimal(buffer.str());

                }
                //Size ;
                buffer.str("");
                long size = 0;

                for (int i = 15; i >= 12; i--)
                {
                    buffer << entryTable[1][i];

                }

                size = Utils::Int::convertHexToDecimal(buffer.str());
                Entry* entry = new MainEntry(Headname, Tailname, Status, startCluster, size);
                // entry->info();
                buffer.str("");
                directoryTable->entrys().push_back(entry);
            }
        }

        indexEntry = indexEntry + 2;
    }

    return directoryTable;
}