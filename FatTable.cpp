#include "FatTable.h"
#include <iostream>
using std::cout, std::endl;
#include "Utils.h"
FatTable::FatTable() {
	this->_numberOfSector = 0;
	this->_fatTable = NULL;
}

FatTable::FatTable(string**& fatTable) {
	this->_numberOfSector = 1;
	this->_fatTable = fatTable;
}

FatTable::FatTable(int numberOfSector, string**& fatTable) {
	this->_numberOfSector = numberOfSector;
	this->_fatTable = fatTable;
}

FatTable::~FatTable() {
	delete this->_fatTable;
}

string FatTable::toString() {
	for (int i = 0; i < 32*this->_numberOfSector; i++) {
		for (int j = 0; j < 16; j++) cout << this->_fatTable[i][j] << ' ';
		cout << endl;
	}
	return "FatTable";
}

string**& FatTable::fatTable() {
	return this->_fatTable;
}

int FatTable::numberOfSector() {
	return this->_numberOfSector;
}

void FatTable::setNumberOfSector(int numberOfSector) {
	this->_numberOfSector = numberOfSector;
}

void FatTable::setFatTable(string**& fatTable) {
	this->_fatTable = fatTable;
}
 bool FatTable::isEndOfFatTable(string** sectors)
{
	 stringstream buffer;
	 for (int i = SECTOR_COLUMN - 1; i >= SECTOR_COLUMN - 4; i--)
		 buffer << sectors[SECTOR_ROW - 1][i];
	 string lastByte = buffer.str();

	 return lastByte == "00000000" ? true : false;
}