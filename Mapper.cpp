#include"Mapper.h"

string Mapper::toString()
{
	return "Mapper";
}

Mapper::Mapper(map<string, int> mp)
{
	this->mp = mp;
}

map<string, int>& Mapper::getMap()
{
	return this->mp;

}
void Mapper::setMap(map<string, int> map)
{
	mp = map;
}