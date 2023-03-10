#pragma once
#include"Attribute.h"

class DataAttribute : public Attribute
{
public:
	DataAttribute();
	DataAttribute(int, int, int, int, int, int, int, int, int,string);

public:
	int sizeContent();
	string content();
	int beginOffset();
	void setBeginOffset(int);
	void setSizeContent(int);
	void setContent(string);
	string toString(); 
	void initContent(); 
private:
	int _sizeContent;
	int _beginOffset;
	string _content; 
};