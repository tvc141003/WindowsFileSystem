
#pragma once
#include "DataStruct.h"
#include<vector>
#include"CItem.h" 
#include"RootDirectoryTable.h"


class CFolder : public CItem {
public:
	string toString();
	RootDirectoryTable _RDET;
	CFolder();
	//CFolder(RootDirectoryTable*);
	CFolder(RootDirectoryTable*, bool ,CItem* );
	vector<CItem* > Item();
	int startCluster();
	string name();
	void setName(string );
	void setStartCluster(int );
	void show(); 
	string type();
protected:
	vector<CItem* > _item;

};
