#include"BiosParameterBlock.h"
#include <iostream>
using std::cout, std::endl;
BiosParameterBlock::BiosParameterBlock() {
	this->_sector = NULL;

}
BiosParameterBlock::BiosParameterBlock(string**& sector)
{
	this->_sector = sector;
}

string BiosParameterBlock::toString()
{
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 16; j++)
			cout << this->_sector[i][j] << ' ';
		cout << endl;
	}
	return "BiosParameterBlock";
}
void BiosParameterBlock::setSector(string**& sector)
{
	this->_sector = sector;
}
string**& BiosParameterBlock::sector()
{
	
	return this->_sector;
}
