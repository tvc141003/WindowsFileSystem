#include"CFile.h"
using std::endl;
CFile::CFile()
{

}
CFile::CFile(string name, int startCluster,CItem* preItem)
{
	this->_name = name;
	this->_startCluster = startCluster;
	_preItem = preItem;

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
void CFile::show()
{
	cout << this->name()<<endl;
	cout << "=====" << endl;
	cout << " content of file";
}
string CFile::type()
{
	return "CFile";
}