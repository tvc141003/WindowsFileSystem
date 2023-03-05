#pragma once
#include<iostream>
#include"Object.h"


class IReader : public Object 
{
public:
	IReader() {};
	string toString() = 0;

public:
	virtual Object* Read(Object*) = 0;
	
};