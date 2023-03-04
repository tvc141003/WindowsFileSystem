#include <sstream>
using std::stringstream;

#include "BootSectorMapper.h"
#include "BootSector.h"

string BootSectorMapper::toString() {
	return "BootSectorMapper";
}

map<string, int> BootSectorMapper::mapper(Object* origin) {
	BootSector* bootSector = dynamic_cast<BootSector*>(origin);
	map<string, int> mp = {};

	stringstream buffer;
	string** sectors = bootSector->sector();

	//get number sector per cluster (Sc);
	buffer << sectors[0][13];
	int sectorPerCluster = Utils::Int::convertHexToDecimal(buffer.str());
	mp.insert({ "Sc", sectorPerCluster });
	buffer.str("");

	//get number sector of boot sector (Sb);
	for (int i = 15; i >= 14; i--)
		buffer << sectors[0][i];
	int sectorOfBootSector = Utils::Int::convertHexToDecimal(buffer.str());
	mp.insert({ "Sb", sectorOfBootSector });
	buffer.str("");

	//get amount of fat table (Nf)
	buffer << sectors[1][0];
	int amountFatTable = Utils::Int::convertHexToDecimal(buffer.str());
	mp.insert({ "Nf", amountFatTable });
	buffer.str("");

	//get size volume (Sv)
	for (int i = 3; i >= 0; i--)
		buffer << sectors[2][i];
	int sizeVolume = Utils::Int::convertHexToDecimal(buffer.str());
	mp.insert({ "Sv", sizeVolume });
	buffer.str("");

	//get size fat table (Sf)
	for (int i = 7; i >= 4; i--)
		buffer << sectors[2][i];
	int sizeFatTable = Utils::Int::convertHexToDecimal(buffer.str());
	mp.insert({ "Sf", sizeFatTable });
	buffer.str("");

	//get cluster begin RDET
	for (int i = 15; i >= 12; i--)
		buffer << sectors[2][i];
	int clusterBeginRDET = Utils::Int::convertHexToDecimal(buffer.str());
	mp.insert({ "ClusterBeginRDET", clusterBeginRDET });
	buffer.str("");

	return mp;
}