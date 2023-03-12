#pragma once
#include <sstream>
using std::stringstream;

#include "Reader.h"
#include "MFTEntry.h"
#include "System.h"
#include "Utils.h"

class ReadMFTEntry :public Reader {
public:
	string toString();
	Object* Read(long long);
};