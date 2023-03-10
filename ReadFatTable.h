#pragma once
#include"Reader.h"
#include"System.h"
class ReadFatTable : public Reader
{
public:
	string toString();
	ReadFatTable();
	Object* Read(long long );

};