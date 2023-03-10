#pragma once
#include"Object.h"

class Reader : public Object
{

public:
	string toString() { return ""; }
	 
	virtual Object* Read(long long) = 0 ;
};