#include"CFile.h"
using std::endl;
CFile::CFile()
{
	this->_name = "";
	this->_size = 0;
	this->_startCluster = 0;
}
CFile::CFile(string name, int startCluster)
{
	this->_name = name;
	this->_startCluster = startCluster;

}

CFile::CFile(string name, int startCluster, int size) {
	this->_name = name;
	this->_startCluster = startCluster;
	this->_size = size;
}

string CFile::toString()
{
	return "";
}

int CFile::startCluster()
{
	return this->_startCluster;

}
string CFile::name()
{
	return this->_name;

}

int CFile::size() {
	return this->_size;
}

void CFile::setSize(int size) {
	this->_size = size;
}

void CFile::setName(string name)
{
	this->_name = name;
}
void CFile::setStartCluster(int cluster)
{
	this->_startCluster = cluster;
}
void CFile::show(int index)
{
	cout << this->info()<<endl;
	cout << "==============================================================" << endl;
	vector <string> names = Utils::String::split(this->_name, ".");
	string tailName = "";
	for (int i = 0; i < names[names.size() - 1].length(); i++)
		if (int(names[names.size() - 1][i]) != 0) tailName = tailName + names[names.size() - 1][i];
	if (tailName != "txt") {

		
		cout << "SYSTEM: DON'T SUPPORT FORMAT " << names[names.size()-1];
		return;
	}
	int cluster = this->_startCluster;
	BootSector* bootSector = getBootSector();
	IValueMapper* mapper = new BootSectorMapper;
	map<string, int> bootSectorMapper = mapper->mapper(bootSector);
	delete mapper;

	ReadFatTable* reader = new ReadFatTable;
	FatTable* fatTable = dynamic_cast<FatTable*>(reader->Read(0));
	mapper = new FatTableMapper;
	map<string, int> fatMapper = mapper->mapper(fatTable);
	delete mapper;

	int size = 0;

	if (this->size() == 0) {
		cout << "SYSTEM: FILE EMPTY" << endl;
		return;
	}
	
	string indexCluster = Utils::String::convertIntToString(cluster);
	do {
		int startSector = (bootSectorMapper["Sb"] + bootSectorMapper["Nf"] * bootSectorMapper["Sf"] + (stoi(indexCluster) - 2) * bootSectorMapper["Sc"]);
		BYTE sector[512];

		for (int i = 0; i < bootSectorMapper["Sc"]; i++) {
			int retCode = 0;
			DWORD bytesRead;
			HANDLE device = NULL;

			device = CreateFile(HARD_DISK,    // Drive to open
				GENERIC_READ,           // Access mode
				FILE_SHARE_READ | FILE_SHARE_WRITE,        // Share Mode
				NULL,                   // Security Descriptor
				OPEN_EXISTING,          // How to create
				0,                      // File attributes
				NULL);                  // Handle to template

			if (device == INVALID_HANDLE_VALUE) // Open Error
			{
				printf("CreateFile: %u\n", GetLastError());
				return;
			}

			SetFilePointer(device, (startSector + i) * 512, NULL, FILE_BEGIN);//Set a Point to Read

			if (!ReadFile(device, sector, 512, &bytesRead, NULL))
			{
				printf("ReadFile: %u\n", GetLastError());
			}
			else
			{
				for (int i = 0; i < 512; i++) {
					if (size < this->size()) {
						cout << sector[i];
					}
					size++;
				}
			}
		}
		if (fatMapper[indexCluster] != EOF) indexCluster = Utils::String::convertIntToString(fatMapper[indexCluster]);
	} while (fatMapper[indexCluster] != EOF);

}
string CFile::type()
{
	return "CFile";
}

string CFile::info() {
	
	vector<int> sectors = {};
	int cluster = this->_startCluster;
	BootSector* bootSector = getBootSector();
	IValueMapper* mapper = new BootSectorMapper;
	map<string, int> bootSectorMapper = mapper->mapper(bootSector);
	delete mapper;

	ReadFatTable* reader = new ReadFatTable;
	FatTable* fatTable = dynamic_cast<FatTable*>(reader->Read(0));
	mapper = new FatTableMapper;
	map<string, int> fatMapper = mapper->mapper(fatTable);
	delete mapper;

	string indexCluster = Utils::String::convertIntToString(this->_startCluster);
	do {
		int startSector = (bootSectorMapper["Sb"] + bootSectorMapper["Nf"] * bootSectorMapper["Sf"] + (stoi(indexCluster) - 2) * bootSectorMapper["Sc"]);

		for (int i = 0; i < bootSectorMapper["Sc"]; i++) {
			sectors.push_back(startSector + i);
		}

		if (fatMapper[indexCluster] != EOF) indexCluster = Utils::String::convertIntToString(fatMapper[indexCluster]);
	} while (stoi(indexCluster) < 2 && fatMapper[indexCluster] != EOF);

	stringstream builder;
	builder << "Name" << ' ' << this->_name << endl;
	builder << "Start Cluster" << ' ' << this->_startCluster << endl;
	builder << "Data Size" << ' ' << this->_size << endl;
	builder << "Sectors: ";
	for (auto sector : sectors) builder << sector << " ";
	builder << endl;
	string result = builder.str();
	return result;
}