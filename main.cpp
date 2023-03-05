#include "ReadDirectoryTable.h"
#include "IValueMapper.h"
#include "FatTableMapper.h"
#include "BootSector.h"
#include "FatTable.h" 
#include "CFolder.h"

int main(int argc, char** argv)
{/*
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
        cout << i << ' ' << mpFatTable[Utils::String::convertIntToString(i)] << endl;*/
   // ReadDirectoryTable* reader = new ReadDirectoryTable();
  /*  BootSector* bootSector = getBootSector();
   IValueMapper* mapper = new BootSectorMapper;
  int numberOfSector = 0; 
   map<string, int> bootSectorMapper = mapper->mapper(bootSector);*/
   BootSector* bootSector = getBootSector();
    IValueMapper* mapper = new BootSectorMapper;

    map<string, int> bootSectorMapper = mapper->mapper(bootSector);
    int point = bootSectorMapper["Sb"] + bootSectorMapper["Nf"] * bootSectorMapper["Sf"]; 
    ReadDirectoryTable* reader = new ReadDirectoryTable();

    DirectoryTable* directory = dynamic_cast<DirectoryTable*> (reader->Read(point));
  //  directory->child();

    CFolder folder(dynamic_cast<RootDirectoryTable*> (directory));
    for (int i = 0; i < folder.Item().size(); i++)
    {
        cout << folder.Item()[i]->name() << endl;
    }
    return 0;
}