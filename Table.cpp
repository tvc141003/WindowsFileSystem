#include"Table.h"

string Table::toString()
{
	return "Table";

}

Table::Table() {
	
};
Table::Table(int**& pointer)
{
	this->table = pointer;
}
int**& Table::getTable()
{
	return this->table;
}