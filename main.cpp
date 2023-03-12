#include "ReadDirectoryTable.h"
#include "IValueMapper.h"
#include "FatTableMapper.h"
#include "BootSector.h"
#include "FatTable.h" 
#include "CFolder.h"
#include "Conio.h"
#include "CFile.h"
#include "BiosParameterBlock.h"
#include "BiosParameterBlockMapper.h"
#include "MFTEntry.h"
#include "ReadMFTEntry.h"
#include "MFTTable.h"
#include "TreeFolder.h"
#include <stack>

using std::string, std::cin, std::stack;

void program(CItem* item)
{
    if (item->type() == "CFolder") {
        CFolder* folder = dynamic_cast<CFolder*>(item);
        int index = 2;
        while (true) {
            system("cls");
          
            folder->show(index);
            unsigned char key = _getch();
            if (int(key) == ARROW) {
                unsigned char arrow = _getch();
                switch (arrow) {
                case static_cast<int>(UP): {
                    int newSelect = max(index - 1, 2);
                    index = newSelect;
                    break;
                }

                case static_cast<int>(DOWN): {
                    int newSelect = min(index + 1, folder->Item().size()-1);
                    index = newSelect;
                    break;
                }
                }
            }
            else {
                switch (key) {
                case static_cast<int>(ENTER):
                    if (folder->Item()[index]->type() == "CFile") {
                        CItem* file = folder->Item()[index];
                        program(file);
                    }
                    else {
                        CFolder* subFolder = dynamic_cast<CFolder*>(folder->Item()[index]);
                        subFolder->init();
                        program(subFolder);
                    }
                    break;

                case static_cast<int>(ESC):
                    return;
                }
            }
        }
    }
    else { 
        CFile* file = dynamic_cast<CFile*>(item);
        while (true) {
            system("cls");
            file->show(2);
            unsigned char key = _getch();

            switch (key) {
            case static_cast<int>(ESC):
                return;
            }
            
        }
    }
  
}

void programNTFS(CItem* item) {
    if (item->type() == "CFolder") {
        CFolder* folder = dynamic_cast<CFolder*>(item);
        int index = 0;
        while (true) {
            system("cls");

            folder->showNTFS(index);
            unsigned char key = _getch();
            if (int(key) == ARROW) {
                unsigned char arrow = _getch();
                switch (arrow) {
                case static_cast<int>(UP): {
                    int newSelect = max(index - 1, 0);
                    index = newSelect;
                    break;
                }

                case static_cast<int>(DOWN): {
                    int newSelect = min(index + 1, folder->Item().size() - 1);
                    index = newSelect;
                    break;
                }
                }
            }
            else {
                switch (key) {
                case static_cast<int>(ENTER):
                    if (folder->Item()[index]->type() == "CFile") {
                        CItem* file = folder->Item()[index];
                        programNTFS(file);
                    }
                    else {
                        CFolder* subFolder = dynamic_cast<CFolder*>(folder->Item()[index]);
                        programNTFS(subFolder);
                    }
                    break;

                case static_cast<int>(ESC):
                    return;
                }
            }
        }
    }
    else {
        CFile* file = dynamic_cast<CFile*>(item);
        while (true) {
            system("cls");
            file->showNTFS(0);
            unsigned char key = _getch();

            switch (key) {
            case static_cast<int>(ESC):
                return;
            }

        }
    }
}

int main(int argc, char** argv)
{
   // cout << " 1";
    /*BootSector* bootSector = getBootSector();
    IValueMapper* mapper = new BootSectorMapper;
    map<string, int> bootSectorMapper = mapper->mapper(bootSector);*/
    //int point = bootSectorMapper["Sb"] + bootSectorMapper["Nf"] * bootSectorMapper["Sf"]; 
  //  ReadDirectoryTable* reader = new ReadDirectoryTable();
  //  DirectoryTable* directory = dynamic_cast<DirectoryTable*> (reader->Read(point));
  ////  directory->child();
  //  RootDirectoryTable* RDET = dynamic_cast<RootDirectoryTable*> (directory);
  //  MainEntry* mainEntry = dynamic_cast<MainEntry*>(RDET->entrys()[0]);
  //  int startCluster = bootSectorMapper["ClusterBeginRDET"];
  //  string name = mainEntry->headName();
  //  CFolder* folder = new CFolder(name, startCluster); // Disk
  //  folder->init();
  //  //cout << folder->name();
  //  program(folder);
  //  return 0;
    

    //NFTS time
    BYTE sector[512];
    string** sectors = ReadSector(HARD_DISK, 0, sector);
    /*for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 16; j++) cout << sectors[i][j] << " ";
        cout << endl;
    }*/
    BiosParameterBlock* BPB = new BiosParameterBlock(sectors);
    BiosParameterBlockMapper* mapper = new BiosParameterBlockMapper;
    map<string, int> mp =  mapper->mapper(BPB);
   /* for (auto i : mp)
    {
        cout << i.first << " " << i.second<<endl;
    }*/
    long long start = mp["ClusterBeginMFT"] * mp["Sc"];
    MFTTable* NTFSMFTtable = new MFTTable(); 
    int count = 0;
    while (true) {
        long long readPoint = start;
        Reader* reader = new ReadMFTEntry;

        MFTEntry* entry = dynamic_cast<MFTEntry*>(reader->Read(readPoint * 512));
        //if (entry->isValid() == false) break;
        if (entry != NULL)
            NTFSMFTtable->entrys().push_back(entry);
        start += 2;
        count++;
        if (count > 100) break;
    }

    //cout << NTFSMFTtable->toString();
    vector<MFTEntry*> TreeMFT = {};
    bool endOfSystemEntry = false;
    for (MFTEntry* entry : NTFSMFTtable->entrys()) {
        if (Utils::String::convertHexToString(entry->getName()) == "IndexerVolumeGuid") {
            endOfSystemEntry = true;
        } 
        else if (endOfSystemEntry == false) continue;
        else {
            TreeMFT.push_back(entry);
        }
    }
    

    TreeFolder* builder = new TreeFolder;
    CFolder* folderSystem = new CFolder("System", mp["ClusterBeginMFT"], {});
    vector <long long> backTrack;
    vector <CFolder*> folderParent;

    folderParent.push_back(folderSystem);
    backTrack.push_back(-1);
    builder->build(TreeMFT, 0, backTrack, folderParent);

    programNTFS(folderSystem);
    
   // BPB->toString();
}