#pragma once
#include <string>
#include <map>
#include <iostream>
#include <sstream>
using std::stringstream;
using std::cout, std::endl;
using std::map;
using std::string;

#define EOF 0x0fffffff
#define SUB_ENTRY 0x0f
#define SECTOR_ROW 32
#define SECTOR_COLUMN 16

namespace Utils {
	class Int {
	public:
		static int convertHexToDecimal (string hex) {
			map<char, int> hexToDec = {
				{'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
				{'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
				{'a', 10}, {'b', 11}, {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15}
			};
			int index = 0;
			int decimal = 0;

			for (int i = hex.length() - 1; i >= 0; i--) {
				decimal = decimal + hexToDec[hex[i]]*int(pow(16, index));
				index++;
			}

			return decimal;
		}
	};
	class String {
	public:
		static string convertIntToString(int num) {
			stringstream buffer;
			buffer << num;
			string str = buffer.str();
			return str;
		}
	};
}