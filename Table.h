#pragma once
#include<iostream>
#include"Object.h"
using namespace std;

class Table : public Object // 32x16
{
private:
	int** table;
public:
	
	string toString();

	
	Table();
	Table(int**&);

	int**& getTable();
};