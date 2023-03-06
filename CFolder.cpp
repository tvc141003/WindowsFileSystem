
#include"CFolder.h"
#include"CFile.h"
#include"ReadDirectoryTable.h"
#include"SubEntry.h"
#include"MainEntry.h"

CFolder::CFolder() {
	this->_name = "";
	this->_item = {};
	this->_startCluster = -1;
}

CFolder::CFolder(string name, int startCluster) {
	this->_name = name;
	this->_startCluster = startCluster;
	this->_item = {};
}


void CFolder::init() {
	if (!this->_item.empty()) return;
	BootSector* bootSector = getBootSector();
	IValueMapper* mapper = new BootSectorMapper;

	map<string, int> bootSectorMapper = mapper->mapper(bootSector);

	int indexSector = bootSectorMapper["Sb"] + bootSectorMapper["Sf"] * bootSectorMapper["Nf"] + (this->startCluster() - 2) * bootSectorMapper["Sc"];
	//	cout << "IndexSector " << name << " = " << indexSector << endl;
	ReadDirectoryTable ReadRDET;
	RootDirectoryTable* RDET = dynamic_cast<RootDirectoryTable*>(ReadRDET.Read(indexSector));
	//	cout << "x ";
	vector<Entry* > vtEntry = RDET->entrys();

	//cout << vtEntry.size(); 
	int i = 0;
	while (i < vtEntry.size())
	{
		int j = i;
		bool isSubEntry = false;
		while (vtEntry[j]->type() != "Main Entry")
		{
			j++;
			isSubEntry = true;
		}
		MainEntry* EntryTemp = dynamic_cast<MainEntry*>(vtEntry[j]);
		if (((1 << 5) & EntryTemp->status()) != 0) // file 
		{
			string name = "";
			stringstream builder;
			if (EntryTemp->headName().size() > 2 && EntryTemp->headName()[EntryTemp->headName().size() - 2] != '~')
			{
				builder << EntryTemp->headName();
			}
			else if (EntryTemp->headName().size() <= 2) {
				builder << EntryTemp->headName();
			}

			int t = j - 1;
			while (t >= 0 && vtEntry[t]->type() != "Main Entry")
			{
				SubEntry* subEntryTemp = dynamic_cast<SubEntry*>(vtEntry[t]);
				builder << subEntryTemp->name();
				t--;
			}
			name = builder.str();
			if (!isSubEntry) {
				string tail = Utils::String::toLower(EntryTemp->tailName());
				name = name + '.' + tail;
			}
			
			int startCluster = EntryTemp->startCluster();
			int size = EntryTemp->size();
			CItem* file = new CFile(name, startCluster, size);
			this->_item.push_back(file);

		}
		else
		{
			string name = "";
			stringstream builder;
			if (EntryTemp->headName().size() > 2 && EntryTemp->headName()[EntryTemp->headName().size() - 2] != '~')
			{
				builder << EntryTemp->headName();
			}
			else if (EntryTemp->headName().size() <= 2)  {
				builder << EntryTemp->headName();
			}

			int t = j - 1;
			while (t >= 0 && vtEntry[t]->type() != "Main Entry")
			{
				SubEntry* subEntryTemp = dynamic_cast<SubEntry*>(vtEntry[t]);
				builder << subEntryTemp->name();
				t--;
			}
			name = builder.str();
			if (!isSubEntry)
				name = name + EntryTemp->tailName();

			int startCluster = EntryTemp->startCluster();
			//	cout << "Start cluster " << name << " = " << startCluster << endl;
			BootSector* bootSector = getBootSector();
			IValueMapper* mapper = new BootSectorMapper;

			map<string, int> bootSectorMapper = mapper->mapper(bootSector);

			int indexSector = bootSectorMapper["Sb"] + bootSectorMapper["Sf"] * bootSectorMapper["Nf"] + (EntryTemp->startCluster() - 2) * bootSectorMapper["Sc"];
			//	cout << "IndexSector " << name << " = " << indexSector << endl;
			ReadDirectoryTable ReadRDET;
			RootDirectoryTable* RDET = NULL;

			//	RootDirectoryTable* RDET = new RootDirectoryTable();
			CItem* folder = new CFolder();
			folder->setName(name);
			folder->setStartCluster(EntryTemp->startCluster());

			this->_item.push_back(folder);
		}
		i = j + 1;
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
string CFolder::type() { return "CFolder"; }
void CFolder::setName(string name)
{
	this->_name = name;

}
void CFolder::setStartCluster(int startCluster)
{
	this->_startCluster = startCluster;
}
void CFolder::show(int index)
{
	
	cout << this->_item[0]->info();
	cout << this->_item[1]->info();
	cout << "========================================================" << endl;
	for (int i = 2; i < this->Item().size(); i++)
	{
		if (i == index) {
			ConsoleColor* color = new ConsoleColor(static_cast<int>(Colors::YELLOW), static_cast<int>(Colors::BLACK));
			ConsoleModifySetColor* setColor = new ConsoleModifySetColor;
			setColor->modify(color);
			cout << this->Item()[i]->name() << endl;
			color->setDefault();
			setColor->modify(color);
		}
		else {
			cout << this->Item()[i]->name() << endl;
		}
	}
}

string CFolder::info() {
	stringstream builder;

	builder << "Name: " << this->_name << endl;
	builder << "Start Cluster: " << this->_startCluster << endl;

	string result = builder.str();
	return result;
}

CFolder::~CFolder() {
	for (auto item : this->_item) delete item;
	this->_item = {};
}