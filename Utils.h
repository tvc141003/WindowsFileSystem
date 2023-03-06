#pragma once
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include<iomanip>
#include"Windows.h"
using std::stringstream;
using std::cout, std::endl;
using std::map;
using std::string;
using std::setw;
using std::setfill;
#define ESC 27
#define EOF 0x0fffffff
#define SUB_ENTRY 0x0f
#define SECTOR_ROW 32
#define SECTOR_COLUMN 16
#define DELETED_ENTRY "e5"
namespace Utils {
	class Int {
	public:
		static long convertHexToDecimal (string hex) {
			map<char,long> hexToDec = {
				{'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
				{'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
				{'a', 10}, {'b', 11}, {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15}
			};
			int index = 0;
			long  decimal = 0;

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

		static string convertHexToString(string hex) {
			int len = hex.length();
			string newString = "";
			for (int i = 0; i < len; i += 2)
			{
				string byte = hex.substr(i, 2);
				char chr = (char)(int)strtol(byte.c_str(), NULL, 16);
				newString.push_back(chr);
			}

			return newString;

		}

		static string ConvertByteToString(BYTE tempBuf)
		{
			stringstream ss;

			int it = int(tempBuf);
			ss << std::hex << setw(2) << setfill('0') << it;

			string result;
			result = ss.str();
			return result;
		}

	};
}