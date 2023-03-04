#pragma once
#include <sstream>
using std::stringstream;

#include "FatTable.h"
#include "IValueMapper.h"

class FatTableMapper :public IValueMapper {
public:
	string toString(); 
	map<string, int> mapper(Object*);
};