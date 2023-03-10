#pragma once
#include <vector>

#include "Entry.h"
#include "Attribute.h"
#include "FileNameAttribute.h"
#include "DataAttribute.h"

using std::vector;

class MFTEntry : public Entry
{
public:
	MFTEntry();
	MFTEntry(int, int, int, int, vector<Attribute*>&, bool);

public:
	int byteBeginAttribute();
	int flag();
	int byteOfEntry();
	int nextAttributeId();
	vector<Attribute*>& attributes();

	void setByteBeginAttribute(int);
	void setFlag(int);
	void setByteOfEntry(int);
	void setNextAttributeId(int);
	void setAttributes(vector<Attribute*>&);

public:
	string toString();
	bool isValid();
	string info() {
		return "";
	};
	string type() { return ""; };


private:
	int _byteBeginAttribute;
	int _flag;
	int _byteOfEntry;
	int _nextAttributeId;
	vector<Attribute*> _attributes;
	bool _isValid;
};