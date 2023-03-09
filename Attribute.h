#pragma once
#include <sstream>
#include "Object.h"

using std::stringstream, std::endl;

class Attribute :public Object {
public:
	Attribute();
	Attribute(int, int, int, int, int, int, int);

public:
	int id();
	int size();
	int nonResident();
	int nameLength();
	int positionName();
	int flags();
	int identify();

	void setId(int);
	void setSize(int);
	void setNonResident(int);
	void setNameLength(int);
	void setPositionName(int);
	void setFlags(int);
	void setIdentify(int);

public:
	string toString();

private:
	int _id;
	int _size;
	int _nonResident;
	int _nameLength;
	int _positionName;
	int _flags;
	int _identify;
};