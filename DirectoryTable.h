#pragma once
#include "Object.h"

class DirectoryTable : public Object {
public:
	string toString() = 0;
	virtual void child() = 0;
	virtual string type() = 0;
};