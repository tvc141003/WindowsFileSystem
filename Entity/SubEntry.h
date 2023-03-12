#pragma once
#include "Entry.h"

class SubEntry : public Entry {
public:
	SubEntry();
	SubEntry(int, string);

public:
	int identify();
	string name();

	void setIdentify(int);
	void setName(string);

public:
	string toString();
	string type();
	string info();

private:
	int _identify;
	string _name;
};