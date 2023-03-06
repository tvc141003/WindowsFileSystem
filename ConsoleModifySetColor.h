#pragma once
#include <string>
#include <Windows.h>
using std::string;

#include "ConsoleModify.h"
#include "ConsoleColor.h"

class ConsoleModifySetColor : public ConsoleModify {
public:
	ConsoleModifySetColor() {}

public:
	string toString();
	void modify(Object*);
};