#include "CItem.h"

string CItem::toString() {
	return "CItem";
}

CItem::CItem() {

}

CItem::CItem(string prePath, string name) {
	
}

CItem* CItem::preItem()
{
	return this->_preItem;

}