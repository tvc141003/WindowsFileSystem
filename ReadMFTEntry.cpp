#include "ReadMFTEntry.h"

string ReadMFTEntry::toString() {
	return "ReadMFTEntry";
}

/// <summary>
/// read entry header, add entry attribute after;
/// </summary>
/// <param name="point"></param>
/// <returns></returns>
Object* ReadMFTEntry::Read(long long point) {
    BYTE sector[512];
    string** str = new string * [64];
    for (int i = 0; i < 64; i++) {
        str[i] = new string[16];
    }

    string** temp = ReadSectorBigByte(HARD_DISK, point, sector);
    for (int i = 0; i < 32; i++) {
        str[i] = temp[i];
    }

    temp = ReadSectorBigByte(HARD_DISK, (point + 512), sector);
    for (int i = 0; i < 32; i++) {
        str[i + 32] = temp[i];
    }

 /*   for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 16; j++) cout << str[i][j] << ' ';
        cout << endl;
    }*/

    stringstream builder;

    //get byte number begin attribute;
    int byteBeginAttribute;
    builder << str[1][5] << str[1][4];
    byteBeginAttribute = Utils::Int::convertHexToDecimal(builder.str());
    builder.str("");
    
    //get flag
    int flag;
    builder << str[1][7] << str[1][6];
    flag = Utils::Int::convertHexToDecimal(builder.str());
    builder.str("");

    //get number byte of entry
    int byteOfEntry;
    for (int i = 11; i >= 8; i--) builder << str[1][i];
    byteOfEntry = Utils::Int::convertHexToDecimal(builder.str());
    builder.str("");

    //get next attibute entry
    int nextAttributeId;
    builder << str[2][9] << str[2][8];
    nextAttributeId = Utils::Int::convertHexToDecimal(builder.str());
    
    //get attributes
    vector<Attribute*> attributes = {};

    Object* entry = new MFTEntry(byteBeginAttribute, flag, byteOfEntry, nextAttributeId, attributes);
	return entry;
}