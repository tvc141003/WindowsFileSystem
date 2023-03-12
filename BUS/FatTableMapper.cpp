#include "FatTableMapper.h"

string FatTableMapper::toString() {
	return "FatTableMapper";
}

map<string, int> FatTableMapper::mapper(Object* origin) {
	FatTable* fatTable = dynamic_cast<FatTable*>(origin);
	map<string, int> mp = {};

	stringstream buffer;
	int index = 0;
	for (int i = 0; i < fatTable->numberOfSector(); i++) {
		//each sector with size 32*16;
		//read forward
		int row = 0 + SECTOR_ROW*i;
		while (row < (i + 1) * SECTOR_ROW) {
			int col = 3;
			while (col < SECTOR_COLUMN) {
				for (int j = col; j >= col - 3; j--) {
					buffer << fatTable->fatTable()[row][j];
				}
				mp.insert({ Utils::String::convertIntToString(index), Utils::Int::convertHexToDecimal(buffer.str())});
				buffer.str("");
				index++;

				col = col + 4;
			}
			row++;
		}
	}
	return mp;
}