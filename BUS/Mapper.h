#pragma once
#include"Object.h"
#include<map>
using std::map;

class Mapper :public Object
{
private: 
	map <string, int> mp;
public: 
	string toString();

	Mapper(map<string, int>);
	map<string,int> & getMap();
	void setMap(map<string, int>);

};