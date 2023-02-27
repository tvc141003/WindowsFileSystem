#include "CItem.h"

string CItem::toString() {
	return "CItem";
}

CItem::CItem() {
	name = "\\\\";
	prePath = "";
}

CItem::CItem(string prePath, string name) {
	this->prePath = prePath;
	this->name = name;
}