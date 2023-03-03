#pragma once
#include "Object.h"

class FatTable :public Object {
public:
	FatTable();
	FatTable(string**&);
	FatTable(int, string**&);

	~FatTable();

public:
	string**& fatTable();
	void setFatTable(string**&);

public:
	string toString();

private:
	int _numberOfSector;
	string** _fatTable;
};