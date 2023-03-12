#pragma once
#include <vector>
using std::vector;

#include "Object.h"
#include "MFTEntry.h"

class MFTTable :public Object {
public:
	MFTTable();
	MFTTable(vector<MFTEntry*>&);

public:
	vector<MFTEntry*>& entrys();
	void setEntrys(vector<MFTEntry*>&);

public:
	string toString();

private:
	vector <MFTEntry*> _entrys;
};