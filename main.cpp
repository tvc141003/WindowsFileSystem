#include "ReadDirectoryTable.h"
#include "IValueMapper.h"
#include "FatTableMapper.h"
#include "BootSector.h"
#include"FatTable.h" 
#include "CFolder.h"
#include"Conio.h"
using std::string, std::cin;
void program(CItem* item,CItem* preFolder)
{
    
    item->show();
    char key;
    key = _getch();
    if (key == ESC)
    {
        system("cls");
        program(preFolder, preFolder->preItem());
    }
    cout << " -------------- " << endl;
    if (item->type() == "CFolder")
    {
        string i;
        cout << "Input i =  ";
        getline(cin, i);
        CFolder* folder = dynamic_cast<CFolder*>(item);
        system("cls");
        program(folder->Item()[stoi(i)],item);
    }
   
}
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

    CFolder* folder = new CFolder(dynamic_cast<RootDirectoryTable*> (directory),1,NULL); // Disk
    folder->setName("Disk");
    //cout << folder->name();
    program(folder,folder->preItem());
   
  
    /* folder->show();
    cout << "------------" << endl;
    cout << "Nhap i = "; 
    string i;
    getline(cin, i);
    CItem* item = folder->Item()[stoi(i)];
    system("cls");
    item->show();*/

  /*  for (int i = 0; i < folder.Item().size(); i++)
    {
        cout << folder.Item()[i]->name() << endl;
        folder.Item()[i]->show() ;
        cout << endl;
        cout << "----------" << endl;
    }*/
   // int indexSector = bootSectorMapper["Sb"] + bootSectorMapper["Sf"] * bootSectorMapper["Nf"] + (folder.Item()[1]->startCluster() - 2) * bootSectorMapper["Sc"];
   // DirectoryTable* directory2 = dynamic_cast<DirectoryTable*> (reader->Read(indexSector));
 
   // CFolder folder2(dynamic_cast<RootDirectoryTable*> (directory2),0);
   // cout << folder2.Item().size();
 
    return 0;
}