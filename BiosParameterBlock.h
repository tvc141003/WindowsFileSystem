#pragma once
#include "Object.h"

class BiosParameterBlock : public Object
{
public:
	BiosParameterBlock();
	BiosParameterBlock(string**&);
public:
	string**& sector();
	void setSector(string**&);
public: 
	string toString();
private:
	string** _sector;
};