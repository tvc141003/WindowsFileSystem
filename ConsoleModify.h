#pragma once
#include "Object.h"

class ConsoleModify : public Object {
public:
	virtual void modify(Object*) = 0;
};