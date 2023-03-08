#pragma once
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include "Windows.h"

using std::vector;
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
#define DELETED_ENTRY 0xe5
#define EMPTY_ENTRY 0x00
#define EMPTY_BYTE 0x20
#define EOB 0xff
#define HARD_DISK L"\\\\.\\E:"
#define ENTER 13
#define ARROW 224
#define UP 72
#define DOWN 80

namespace Utils {
	class Int {
	public:
		static int convertHexToDecimal (string hex) {
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

	class LongLong {
	public:
		static long long convertHexToDecimal(string hex) {
			map<char, long long> hexToDec = {
				{'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
				{'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
				{'a', 10}, {'b', 11}, {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15}
			};
			long long index = 0;
			long long decimal = 0;

			for (int i = hex.length() - 1; i >= 0; i--) {
				decimal = decimal + hexToDec[hex[i]] * int(pow(16, index));
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
				if (Utils::Int::convertHexToDecimal(byte) == EOB) continue;
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

		static vector<string> split(string haystack, string needle) {
			vector<string> result;
			int startPos = 0;
			size_t foundPos = haystack.find(needle, startPos);

			while (foundPos != string::npos) {
				int count = foundPos - startPos;
				string token = haystack.substr(startPos, count);
				result.push_back(token);

				startPos = foundPos + needle.length();
				foundPos = haystack.find(needle, startPos);
			}

			// The remaining
			string token = haystack.substr(startPos, haystack.length() - startPos);
			result.push_back(token);

			return result;
		}

		static string toLower(string origin) {
			string result = "";
			for (int i = 0; i < origin.length(); i++) result += tolower(origin[i]);

			return result;
		}

		static string splice(string origin) {
			string result = "";

			bool isTrue = true;
			for (int i = origin.length() - 1; i >= 0; i--) {
				if (origin[i] == ' ' && isTrue == true) continue;
				else {
					isTrue = false;
					result = origin[i] + result;
				}
			}

			return result;
		}

	

	};
}