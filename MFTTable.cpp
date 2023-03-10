#include "MFTTable.h"

MFTTable::MFTTable() {
	this->_entrys = {};
}

MFTTable::MFTTable(vector<MFTEntry*>& entrys) {
	this->_entrys = entrys;
}

vector<MFTEntry*>& MFTTable::entrys() {
	return this->_entrys;
}

void MFTTable::setEntrys(vector<MFTEntry*>& entrys) {
	this->_entrys = entrys;
}

string MFTTable::toString() {
	stringstream builder;
	for (auto entry : this->_entrys) {
		builder << entry->toString() << endl;
	}
	builder << endl;
	string result = builder.str();
	return result;
}