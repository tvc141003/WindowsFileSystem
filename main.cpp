#include "ReadDirectoryTable.h"
#include "IValueMapper.h"
#include "FatTableMapper.h"
#include "BootSector.h"
#include "FatTable.h" 
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
        return;

        //program(preFolder, preFolder->preItem());
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
{
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

    return 0;
}