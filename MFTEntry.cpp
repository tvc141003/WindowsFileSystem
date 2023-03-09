#include"MFTEntry.h"

#include"Utils.h"

MFTEntry::MFTEntry()
{
	this->_byteBeginAttribute = 0;
	this->_byteOfEntry = 0;
	this->_flag = 0;
	this->_nextAttributeId = 0;
	this->_attributes = {};
}

MFTEntry::MFTEntry(int byteBegin, int flag, int byteOfEntry, int nextId, vector<Attribute*>& attributes)
{
	this->_byteBeginAttribute = byteBegin;
	this->_byteOfEntry = byteOfEntry;
	this->_flag = flag;
	this->_nextAttributeId = nextId;
	this->_attributes = attributes;
}


int MFTEntry::byteBeginAttribute() {
	return this->_byteBeginAttribute;
}

int MFTEntry::flag() {
	return this->_flag;
}

int MFTEntry::byteOfEntry() {
	return this->_byteOfEntry;
}

int MFTEntry::nextAttributeId() {
	return this->_nextAttributeId;
}

vector<Attribute*>& MFTEntry::attributes() {
	return this->_attributes;
}

void MFTEntry::setByteBeginAttribute(int byteBegin) {
	this->_byteBeginAttribute = byteBegin;
}

void MFTEntry::setFlag(int flag) {
	this->_flag = flag;
}

void MFTEntry::setByteOfEntry(int byteOfEntry) {
	this->_byteOfEntry = byteOfEntry;
}

void MFTEntry::setNextAttributeId(int nextId) {
	this->_nextAttributeId = nextId;
}

void MFTEntry::setAttributes(vector<Attribute*>& attributes) {
	this->_attributes = attributes;
}

string MFTEntry::toString()
{
	stringstream builder;
	builder << "byteBeginAttribute: " << this->_byteBeginAttribute << endl;
	builder << "flag: " << this->_flag << endl;
	builder << "byteOfEntry: " << this->_byteOfEntry << endl;
	builder << "nextAttributeId: " << this->_nextAttributeId << endl;
	for (auto attri : this->_attributes) {
		builder << attri->toString() << endl;
	}

	string result = builder.str();
	return result;
}