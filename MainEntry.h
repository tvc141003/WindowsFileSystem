#pragma once
#include "Entry.h"

class MainEntry :public Entry {
public:
	MainEntry();
	MainEntry(string, string, int, int, int);

public:
	string headName();
	string tailName();
	int status();
	int startCluster();
	int size();

	void setHeadName(string);
	void setTailName(string);
	void setStatus(int);
	void setStartCluster(int);
	void setSize(int);

public:
	string toString();
	string type();
	string info();

private:
	string _headName;
	string _tailName;
	int _status;
	int _startCluster;
	int _size;
};