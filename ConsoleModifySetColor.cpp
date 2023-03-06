#include "ConsoleModifySetColor.h"

string ConsoleModifySetColor::toString() {
	return "ConsoleModifySetColor";
}

void ConsoleModifySetColor::modify(Object* color) {
	ConsoleColor* setColor = dynamic_cast<ConsoleColor*>(color);

	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, setColor->consoleColor());
}