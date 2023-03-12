#pragma once
#include "IValueMapper.h"

class BiosParameterBlockMapper : public IValueMapper
{
public:
	string toString();
	map <string, int> mapper(Object*);
};
