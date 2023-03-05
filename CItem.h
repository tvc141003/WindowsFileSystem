#pragma once
#include "DataStruct.h"

class CItem : public DataStruct {
public:
	CItem();
	CItem(string, string);

public:
	string toString() = 0;
	virtual int startCluster() = 0; 
	virtual string name() = 0;
	virtual void setName(string) = 0; 
	virtual void setStartCluster(int) = 0; 


protected:
	int _startCluster;
	string _name;
};