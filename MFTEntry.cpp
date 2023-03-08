#include"MFTEntry.h"

#include"Utils.h"

MFTEntry::MFTEntry()
{
	this->_entry = NULL;
}
MFTEntry::MFTEntry(string**& entry)
{
	this->_entry = entry;
}


string**& MFTEntry::getEntry()
{
	return this->_entry;
}

void MFTEntry::setEntry(string** & entry)
{
	this->_entry = entry;
}

string MFTEntry::toString()
{
	stringstream builder;
	for (int i = 0; i < MFT_ROW; i++)
	{
		for (int j = 0; j < MFT_COLUMN; j++)
			builder << _entry[i][j]<<" ";
		builder << endl;
	}
	return builder.str();
}