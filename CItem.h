#pragma once
#include "DataStruct.h"

class CItem : public DataStruct {
public:
	CItem();
	CItem(string, string);

public:
	string toString() = 0;

protected:
	string name;
	string prePath;

};