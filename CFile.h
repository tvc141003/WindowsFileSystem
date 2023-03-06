#pragma once
#include"CItem.h"
#include<iostream>
using std::cout;
class CFile : public CItem
{
public:
	string toString();
	CFile();
	int startCluster();
	CFile(string , int s, CItem*);
	string name(); 
	void setName(string);
	void setStartCluster(int);
	void show();
	string type();
};