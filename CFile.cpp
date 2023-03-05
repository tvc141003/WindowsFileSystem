#include "CFile.h"

CFile::CFile() : CItem() {
	//do nothing
}

CFile::CFile(string name, string prePath) : CItem(name, prePath) {
	//Do nothing
}

string CFile::toString() {
	return "CFile";
}