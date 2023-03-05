#pragma once
#include "CItem.h"

class CFile : public CItem {
public:
	CFile();
	CFile(string, string);

public:
	string toString();

protected:
	string name;
	string prePath;
};