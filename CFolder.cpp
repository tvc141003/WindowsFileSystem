
#include"CFolder.h"
#include"CFile.h"
#include"ReadDirectoryTable.h"
#include"SubEntry.h"
#include"MainEntry.h"

CFolder::CFolder() {

}

CFolder::CFolder(RootDirectoryTable* rdet)
{
	_RDET.entrys() = rdet->entrys();
	vector<Entry* > vtEntry = _RDET.entrys();
	int i = 4;
	while (i < vtEntry.size()  )
	{
		int j = i;
		while (vtEntry[j]->type() != "Main Entry")
		{
			j++;
		}
		MainEntry* EntryTemp = dynamic_cast<MainEntry*>(vtEntry[j]);
		if (((1 << 5) & EntryTemp->status()) != 0) // file 
		{
			string name = "";
			stringstream builder;
			if (EntryTemp->headName()[EntryTemp->headName().size() - 2] != '~')
			{
				builder << EntryTemp->headName();
			}

			int t = j - 1; 
			while (vtEntry[t]->type() != "Main Entry" && t >3)
			{
				SubEntry* subEntryTemp = dynamic_cast<SubEntry*>(vtEntry[t]);
				builder << subEntryTemp->name();
				t--;
			}
			name = builder.str() + EntryTemp->tailName();

			int startCluster = EntryTemp->startCluster();

			CItem* file = new CFile(name,startCluster);
			this->_item.push_back(file);

		}
		else if (((1 << 4) & EntryTemp->status()) != 0 )
		{
			string name = "";
			stringstream builder;
			if (EntryTemp->headName()[EntryTemp->headName().size() - 2] != '~')
			{
				builder << EntryTemp->headName();
			}

			int t = j - 1;
			while ( t >3  && vtEntry[t]->type() != "Main Entry")
			{
				SubEntry* subEntryTemp = dynamic_cast<SubEntry*>(vtEntry[t]);
				builder << subEntryTemp->name();
				t--;
			}
			name = builder.str() + EntryTemp->tailName();

			int startCluster = EntryTemp->startCluster();
		//	cout << "Start cluster " << name << " = " << startCluster << endl;
			BootSector* bootSector = getBootSector();
			IValueMapper* mapper = new BootSectorMapper;

			map<string, int> bootSectorMapper = mapper->mapper(bootSector);

			int indexSector = bootSectorMapper["Sb"] + bootSectorMapper["Sf"]*bootSectorMapper["Nf"] + (EntryTemp->startCluster()-2)*bootSectorMapper["Sc"];
		//	cout << "IndexSector " << name << " = " << indexSector << endl;
			ReadDirectoryTable ReadRDET; 
			RootDirectoryTable* RDET = dynamic_cast<RootDirectoryTable* >(ReadRDET.Read(indexSector));
			
		//	RootDirectoryTable* RDET = new RootDirectoryTable();
			CItem* folder = new CFolder(RDET);
			folder->setName(name);
			folder->setStartCluster(EntryTemp->startCluster());

			this->_item.push_back(folder);
		}
		i = j + 1 ;
	}


}
string CFolder::toString()
{
	return "Cfolder";

}
vector<CItem* > CFolder::Item()
{
	return this->_item;

}

int CFolder::startCluster()
{
	return _startCluster;

}
string CFolder::name()
{
	return this->_name;

}

void CFolder::setName(string name)
{
	this->_name = name;

}
void CFolder::setStartCluster(int startCluster)
{
	this->_startCluster = startCluster;
}