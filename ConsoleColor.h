#pragma once
#include <string>
using std::string;

#include "Object.h"

class ConsoleColor :public Object {
public:
	ConsoleColor();
	ConsoleColor(const int, const int);

public:
	int consoleColor();
	void setConsoleColor(const int, const int);
	void setDefault();

public:
	string toString();

private:
	int _consoleColor;
};