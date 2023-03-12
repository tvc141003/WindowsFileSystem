#pragma once
#include "Object.h"

class BootSector :public Object {
public:
	BootSector();
	BootSector(string**&);
	~BootSector();

public:
	string**& sector();
	void setSector(string**&);

public:
	string toString();

private:
	string** _sector;
};