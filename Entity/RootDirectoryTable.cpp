#include <iostream>
using std::cout, std::endl;

#include "RootDirectoryTable.h"

RootDirectoryTable::RootDirectoryTable() {
	this->_entrys = {};
}

RootDirectoryTable::RootDirectoryTable(vector<Entry*> entrys) {
	this->_entrys = entrys;
}

vector<Entry*>& RootDirectoryTable::entrys() {
	return this->_entrys;
}

void RootDirectoryTable::setEntry(vector<Entry*> entrys) {
	this->_entrys = entrys;
}

string RootDirectoryTable::toString() {
	return "RootDirectoryTable";
}

/// <summary>
/// Code after done Entry
/// </summary>
void RootDirectoryTable::child() {
	for (int i = 0; i < this->entrys().size(); i++) {
		cout << this->entrys()[i]->info();
	}
}

string RootDirectoryTable::type() {
	return "RDET";
}