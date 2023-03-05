#include"CFile.h"

CFile::CFile()
{

}
CFile::CFile(string name, int startCluster)
{
	this->_name = name;
	this->_startCluster = startCluster;

}
string CFile::toString()
{
	return "";
}

int CFile::startCluster()
{
	return this->_startCluster;

}
string CFile::name()
{
	return this->_name;

}
void CFile::setName(string name)
{
	this->_name = name;
}
void CFile::setStartCluster(int cluster)
{
	this->_startCluster = cluster;
}