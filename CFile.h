#pragma once
#include "CItem.h"
#include "Utils.h"
#include "BootSector.h"
#include "BootSectorMapper.h"
#include "FatTable.h"
#include "FatTableMapper.h"
#include "ReadFatTable.h"
#include "IValueMapper.h"
#include "System.h"
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

using std::cout, std::stringstream;
class CFile : public CItem
{
public:
	CFile();
	CFile(string , int);
	CFile(string, int, int);
	CFile(string, int, int, string);

public:
	string name(); 
	int startCluster();
	int size();
	void setName(string);
	void setStartCluster(int);
	void setSize(int);

public:
	string toString();
	void show(int);
	string type();
	string info();
	void showNTFS(int);

private:
	int _size;
	string _content;
};