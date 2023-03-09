#include"ReadFatTable.h"


ReadFatTable::ReadFatTable()
{

}
string ReadFatTable::toString()
{
	return "";
}

Object* ReadFatTable::Read(long long point)
{
    BootSector* bootSector = getBootSector();
    IValueMapper* mapper = new BootSectorMapper;

    map<string, int> bootSectorMapper = mapper->mapper(bootSector);

    string** fatSector = NULL;
    int numberOfSector = 0;
    while (true) {
        BYTE sector[512];
        int readPoint = (bootSectorMapper["Sb"] + numberOfSector) * 512;
        string** sectors = ReadSector(HARD_DISK, readPoint, sector);

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
        if (FatTable::isEndOfFatTable(sectors) == true) break;
    }

    FatTable* fatTable = new FatTable(numberOfSector, fatSector);
    return fatTable;
} // point = o for ReadFatTable



