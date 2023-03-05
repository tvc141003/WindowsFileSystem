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
	CFolder(RootDirectoryTable*);
	vector<CItem* > Item();
	int startCluster();
	string name();
	void setName(string );
	void setStartCluster(int );
protected:
	vector<CItem* > _item;

};
