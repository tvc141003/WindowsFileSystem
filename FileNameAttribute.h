#pragma once
#include"Attribute.h"

class FileNameAttribute : public Attribute
{
public:
	FileNameAttribute();
	FileNameAttribute(int, int, int, int, int, int, int, int, int,string);

public:
	
	int contentSize();
	int beginOffset();

	void setContentSize(int);
	void setBeginOffset(int);
	string toString();

private:
	
	int _contentSize;
	int _beginOffset;

	string _content; 
};