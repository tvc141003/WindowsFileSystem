#include"FileNameAttribute.h"

FileNameAttribute::FileNameAttribute() : Attribute()
{
	this->_beginOffset = 0;
	this->_fileRef = 0;
	this->_contentSize = 0; 
}

FileNameAttribute::FileNameAttribute(int id, int size, int nonResident, int nameLength, int positionName, int flags, int identify,int sizeContent, int startOffset, long long fileRef, string content ) : Attribute(id, size, nonResident, nameLength, positionName, flags, identify)
{
	this->_contentSize = sizeContent;
	this->_beginOffset = startOffset;
	this->_fileRef = fileRef;
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

long long FileNameAttribute::fileRef() {
	return this->_fileRef;
}

void FileNameAttribute::setFileRef(long long fileRef) {
	this->_fileRef = fileRef;
}

string FileNameAttribute::content() {
	return this->_content;
}

string FileNameAttribute::toString() 
{
	stringstream builder;
	builder << "Begin Offset: " << _beginOffset << endl;
	builder << "Content's Size: " << _contentSize << endl;
	builder << "File References: " << this->_fileRef << endl;
	builder << "Content: " << Utils::String::convertHexToString(this->_content) << endl;
	return Attribute::toString() + builder.str();

}