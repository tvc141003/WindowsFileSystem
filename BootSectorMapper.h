#pragma once
#include "IValueMapper.h"

class BootSectorMapper :public IValueMapper {
public:
	string toString();
	map<string, int> mapper(Object*);
};