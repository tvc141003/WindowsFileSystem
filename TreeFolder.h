#pragma once
#include <stack>
#include "Object.h"
#include "MFTEntry.h"
#include "CItem.h"
#include "CFolder.h"
#include "CFile.h"
#include "BiosParameterBlock.h"
#include "BiosParameterBlockMapper.h"
#include "System.h"
#include "FileNameAttribute.h"
#include "DataAttribute.h"

using std::stack;

class TreeFolder : public Object {
public:
	string toString();
	void build(vector<MFTEntry*>, int, vector<long long>&, vector<CFolder*>&);

};