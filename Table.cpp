#include"Table.h"

string Table::toString()
{
	return "Table";

}

Table::Table() {
	this->table = NULL;
}

Table::Table(int**& pointer)
{
	this->table = pointer;
}
int**& Table::getTable()
{
	return this->table;
}