#pragma once
#include <vector>
using std::vector;

#include "DirectoryTable.h"
#include "Entry.h"

class RootDirectoryTable : public DirectoryTable {
public:
	RootDirectoryTable();
	RootDirectoryTable(vector<Entry*>);

public:
	vector<Entry*>& entrys();
	void setEntry(vector<Entry*>);

public:
	string toString();
	void child();
	string type();

private:
	vector <Entry*> _entrys;
};