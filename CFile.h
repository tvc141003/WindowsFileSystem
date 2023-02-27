#pragma once
#include "DataStruct.h"

class CFile : public DataStruct {
public:
	string toString();

protected:
	string path;
};