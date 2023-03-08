#pragma once
#include"Entry.h"

class MFTEntry : public Entry
{
public:
	MFTEntry();
	MFTEntry(string**&);
public:
	string**& getEntry();
	void setEntry(string**&);
	string toString();
	string info() {
		return "";
	};
	string type() { return ""; };


private:
	string** _entry; // 1024 byte // 64x16 


};