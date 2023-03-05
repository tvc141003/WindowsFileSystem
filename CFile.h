#pragma once
#include"CItem.h"
class CFile : public CItem
{
public:
	string toString();
	CFile();
	int startCluster();
	CFile(string , int s);
	string name(); 
	void setName(string);
	void setStartCluster(int);

};