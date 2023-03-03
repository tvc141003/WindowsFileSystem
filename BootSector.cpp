#include "BootSector.h"
#include <iostream>
using std::cout, std::endl;

BootSector::BootSector() {
	this->_sector = NULL;
}

BootSector::BootSector(string**& sector) {
	this->_sector = sector;
}

BootSector::~BootSector() {
	delete this->_sector;
}

string BootSector::toString() {
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 16; j++) cout << this->_sector[i][j] << ' ';
		cout << endl;
	}
	return "BootSector";
}

string**& BootSector::sector() {
	return this->_sector;
}

void BootSector::setSector(string**& sector) {
	this->_sector = sector;
}