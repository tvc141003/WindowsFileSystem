#include "Attribute.h"

Attribute::Attribute() {
	this->_id = 0;
	this->_size = 0;
	this->_nonResident = 0;
	this->_nameLength = 0;
	this->_positionName = 0;
	this->_flags = 0;
	this->_identify = 0;
}

Attribute::Attribute(int id, int size, int nonResident, int nameLength, int positionName, int flags, int identify) {
	this->_id = id;
	this->_size = size;
	this->_nonResident = nonResident;
	this->_nameLength = nameLength;
	this->_positionName = positionName;
	this->_flags = flags;
	this->_identify = identify;
}

int Attribute::id() {
	return this->_id;
}

int Attribute::size() {
	return this->_size;
}

int Attribute::nonResident() {
	return this->_nonResident;
}

int Attribute::nameLength() {
	return this->_nameLength;
}

int Attribute::positionName() {
	return this->_positionName;
}

int Attribute::flags() {
	return this->_flags;
}

int Attribute::identify() {
	return this->_identify;
}

void Attribute::setId(int id) {
	this->_id = id;
}

void Attribute::setSize(int size) {
	this->_size = size;
}

void Attribute::setNonResident(int nonResident) {
	this->_nonResident = nonResident;
}

void Attribute::setNameLength(int nameLength) {
	this->_nameLength = nameLength;
}

void Attribute::setPositionName(int positionName) {
	this->_positionName = positionName;
}

void Attribute::setFlags(int flags) {
	this->_flags = flags;
}

void Attribute::setIdentify(int identify) {
	this->_identify = identify;
}

string Attribute::toString() {
	stringstream builder;

	builder << "Id: " << this->_id << endl;
	builder << "Size: " << this->_size << endl;
	builder << "Is non resident: " << this->_nonResident << endl;
	builder << "Name Size: " << this->_nameLength << endl;
	builder << "Position Name: " << this->_positionName << endl;
	builder << "Flags: " << this->_flags << endl;
	builder << "Identify: " << this->_identify << endl;

	string result = builder.str();
	return result;
}