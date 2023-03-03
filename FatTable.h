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
	int numberOfSector();

	void setFatTable(string**&);
	void setNumberOfSector(int);

public:
	string toString();

private:
	int _numberOfSector;
	string** _fatTable;
};