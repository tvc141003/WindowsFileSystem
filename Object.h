#pragma once
#include <string>
using std::string;

class Object {
public:
	virtual string toString() = 0;
};