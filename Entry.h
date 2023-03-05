#pragma once
#include <sstream>
#include<iostream>
using std::stringstream, std::endl;
#include "Object.h"

class Entry : public Object {
public:
	string toString() = 0;
	virtual string info() = 0;
	virtual string type() = 0;
};