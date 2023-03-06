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
	virtual void show() = 0; 
	virtual string type() = 0; 
	 CItem* preItem()  ;

protected:
	int _startCluster;
	string _name;
	CItem* _preItem;
};