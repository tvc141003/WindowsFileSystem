#include "FatTable.h"
#include <iostream>
using std::cout, std::endl;

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

void FatTable::setFatTable(string**& fatTable) {
	this->_fatTable = fatTable;
}