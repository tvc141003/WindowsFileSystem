#include"MFTEntry.h"

#include"Utils.h"

MFTEntry::MFTEntry()
{
	this->_byteBeginAttribute = 0;
	this->_byteOfEntry = 0;
	this->_flag = 0;
	this->_nextAttributeId = 0;
	this->_attributes = {};
	this->_isValid = false;
}

MFTEntry::MFTEntry(int byteBegin, int flag, int byteOfEntry, int nextId, vector<Attribute*>& attributes, bool valid, long long ref)
{
	this->_byteBeginAttribute = byteBegin;
	this->_byteOfEntry = byteOfEntry;
	this->_flag = flag;
	this->_nextAttributeId = nextId;
	this->_attributes = attributes;
	this->_isValid = valid;
	this->_ref = ref;
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

long long MFTEntry::ref() {
	return this->_ref;
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

bool MFTEntry::isValid() {
	return this->_isValid;
}

string MFTEntry::toString()
{
	stringstream builder;
	builder << "References: " << this->_ref << endl;
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

string MFTEntry::getName() {
	stringstream builder;
	for (int i = 0; i < this->_attributes.size(); i++) {
		if (this->_attributes[i]->id() == 0x30) {
			FileNameAttribute* fileName = dynamic_cast<FileNameAttribute*>(this->_attributes[i]);
			builder << fileName->content();
			break;
		}
	}

	string result = builder.str();
	return result;
}