#include"DataAttribute.h"


DataAttribute::DataAttribute() : Attribute()
{
	_sizeContent = 0; 
	_beginOffset = 0; 
	_content = "";
}

DataAttribute::DataAttribute(int id, int size, int nonResident, int nameLength, int positionName, int flags, int identify, int contentSize, int beginOffset,string content) : Attribute(id, size, nonResident, nameLength, positionName, flags, identify)
{
	this->_sizeContent = contentSize;
	this->_beginOffset = beginOffset;
	this->_content = content; 
}


int DataAttribute::sizeContent() {
	return this->_sizeContent;

}

string DataAttribute::content()
{
	return _content;

}

void DataAttribute::setSizeContent(int sizeContent)
{
	this->_sizeContent = sizeContent;
}
void DataAttribute::setContent(string content)
{
	this->_content = content; 
}
int DataAttribute::beginOffset()
{
	return this->_beginOffset;

}

void DataAttribute::setBeginOffset(int beginOffset)
{
	this->_beginOffset = beginOffset; 
}

void DataAttribute::initContent()
{

}
string DataAttribute::toString()
{
	stringstream builder;
	builder << "Size Content: " << this->_sizeContent << endl;
	builder << "Content : " << Utils::String::convertHexToString(this->_content) << endl;
	return Attribute::toString() + builder.str();

}