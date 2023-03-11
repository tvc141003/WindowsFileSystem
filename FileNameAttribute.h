#pragma once
#include"Attribute.h"

class FileNameAttribute : public Attribute
{
public:
	FileNameAttribute();
	FileNameAttribute(int, int, int, int, int, int, int, int, int, long long, string);

public:
	
	int contentSize();
	int beginOffset();
	long long fileRef();

	void setFileRef(long long);
	void setContentSize(int);
	void setBeginOffset(int);
	string toString();

private:
	
	int _contentSize;
	int _beginOffset;
	long long _fileRef;

	string _content; 
};