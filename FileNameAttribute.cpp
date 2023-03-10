#include"FileNameAttribute.h"

FileNameAttribute::FileNameAttribute() : Attribute()
{
	this->_beginOffset = 0; 
	this->_contentSize = 0; 
}

FileNameAttribute::FileNameAttribute(int id, int size, int nonResident, int nameLength, int positionName, int flags, int identify,int sizeContent, int startOffset, string content ) : Attribute(id, size, nonResident, nameLength, positionName, flags, identify)
{

	this->_contentSize = sizeContent;
	this->_beginOffset = startOffset;
	this->_content = content; 
}

void FileNameAttribute::setBeginOffset(int beginOffset)
{
	this->_beginOffset = beginOffset;
}

void FileNameAttribute::setContentSize(int contentSize)
{
	this->_contentSize = contentSize;
}

int FileNameAttribute::beginOffset()
{
	return this->_beginOffset;
}

int FileNameAttribute::contentSize()
{
	return this->_contentSize;
}


string FileNameAttribute::toString() 
{
	stringstream builder;
	builder << "Begin Offset: " << _beginOffset << endl;
	builder << "Content's Size: " << _contentSize << endl;
	builder << "Content: " << Utils::String::convertHexToString(this->_content) << endl;
	return Attribute::toString() + builder.str();

}