#pragma once
#include <map>
#include "Object.h"
#include "Utils.h"
using std::map;

class IValueMapper : public Object {
public:
	string toString() = 0;
	virtual map<string, int> mapper(Object*) = 0;
};