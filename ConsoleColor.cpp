#include "ConsoleColor.h"

ConsoleColor::ConsoleColor() {
	this->_consoleColor = 7;
}

ConsoleColor::ConsoleColor(const int textColor, const int backgroundColor) {
	this->_consoleColor = textColor + backgroundColor * 16;
}

int ConsoleColor::consoleColor() {
	return this->_consoleColor;
}

void ConsoleColor::setConsoleColor(const int textColor, const int backgroundColor) {
	this->_consoleColor = textColor + backgroundColor * 16;
}

void ConsoleColor::setDefault() {
	this->_consoleColor = 7;
}

string ConsoleColor::toString() {
	return "ConsoleColor";
}