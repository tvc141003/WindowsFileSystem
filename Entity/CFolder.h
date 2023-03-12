
#pragma once
#include <vector>
#include "DataStruct.h"
#include "CItem.h" 
#include "RootDirectoryTable.h"
#include "ConsoleColor.h"
#include "Colors.h"
#include "ConsoleModify.h"
#include "ConsoleModifySetColor.h"


class CFolder : public CItem {
public:
	CFolder();
	CFolder(string, int);
	CFolder(string, int, vector<CItem*>);

	~CFolder();

public:
	string toString();
	//CFolder(RootDirectoryTable*);
	vector<CItem*>& Item();
	int startCluster();
	string name();
	void setName(string );
	void setStartCluster(int );
	void show(int); 
	string type();
	string info();
	void showNTFS(int);

public:
	void init();

protected:
	vector<CItem* > _item;
};
