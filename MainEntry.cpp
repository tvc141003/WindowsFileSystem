#include "MainEntry.h"

MainEntry::MainEntry() {
	this->_headName = "";
	this->_tailName = "";
	this->_status = 192; //bit 6 and bit 7 = 1, other = 0;
	this->_startCluster = 0;
	this->_size = 0;
}

MainEntry::MainEntry(string headName, string tailName, int status, int startCluster, int size) {
	this->_headName = headName;
	this->_tailName = tailName;
	this->_status = status;
	this->_startCluster = startCluster;
	this->_size = size;
}

string MainEntry::headName() {
	return this->_headName;
}

string MainEntry::tailName() {
	return this->_tailName;
}

int MainEntry::status() {
	return this->_status;
}

int MainEntry::startCluster() {
	return this->_startCluster;
}

int MainEntry::size() {
	return this->_size;
}

void MainEntry::setHeadName(string headName) {
	this->_headName = headName;
}

void MainEntry::setTailName(string tailName) {
	this->_tailName = tailName;
}

void MainEntry::setStatus(int status) {
	this->_status = status;
}

void MainEntry::setStartCluster(int startCluster) {
	this->_startCluster = startCluster;
}

void MainEntry::setSize(int size) {
	this->_size = size;
}

string MainEntry::toString() {
	return "MainEntry";
}

string MainEntry::type() {
	return "Main Entry";
}

/// <summary>
/// update after done entry;
/// </summary>
/// <returns></returns>
string MainEntry::info() {
	return "";
}