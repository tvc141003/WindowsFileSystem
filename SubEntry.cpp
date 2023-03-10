#include "SubEntry.h"

SubEntry::SubEntry() {
	this->_identify = 0;
	this->_name = "";
}

SubEntry::SubEntry(int identify, string name) {
	this->_identify = identify;
	this->_name = name;
}

int SubEntry::identify() {
	return this->_identify;
}

string SubEntry::name() {
	return this->_name;
}

void SubEntry::setIdentify(int identify) {
	this->_identify = identify;
}

void SubEntry::setName(string name) {
	this->_name = name;
}

string SubEntry::toString() {
	return "SubEntry";
}

string SubEntry::type() {
	return "Sub Entry";
}

string SubEntry::info() {
	stringstream buffer;
	buffer << " sub entry" << endl;
	buffer << this->_identify << " ";
	buffer << this->_name << endl;
	buffer << "------------" << endl;
	string result = buffer.str();

	return result;
}