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

    /*for (int i = 0; i < 64; i++) {
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
    builder.str("");

    //check if entry valid.
    bool isValid;
    for (int i = 0; i <= 3; i++) {
        builder << str[0][i];
    }
    //cout << ((Utils::String::convertHexToString(builder.str()) == "FILE") ? true : false) << endl;
    isValid = Utils::String::convertHexToString(builder.str()) == "FILE" ? true : false;

    if (isValid == false) {
        vector<Attribute*> attributes = {};
        MFTEntry* entry = new MFTEntry(byteBeginAttribute, flag, byteOfEntry, nextAttributeId, attributes, isValid);
        return entry;
    }

    //get attributes
    vector<Attribute*> attributes = {};
    long long startAttribute = byteBeginAttribute;
    while (startAttribute < 1024) {
        stringstream buffer;

        //get type of attribute;
        int typeID;
        for (int i = startAttribute + 3; i >= startAttribute; i--) {
            int row = i / 16;
            int column = i % 16;

            buffer << str[row][column];
        }
        typeID = Utils::Int::convertHexToDecimal(buffer.str());
        buffer.str("");

        if (typeID == END_OF_MFT_ENTRY) break;

        int size;
        for (int i = startAttribute + 7; i >= startAttribute + 4; i--) {
            int row = i / 16;
            int column = i % 16;

            buffer << str[row][column];
        }
        size = Utils::Int::convertHexToDecimal(buffer.str());
        buffer.str("");

        int resident;
        for (int i = startAttribute + 8; i >= startAttribute + 8; i--) {
            int row = i / 16;
            int column = i % 16;

            buffer << str[row][column];
        }
        resident = Utils::Int::convertHexToDecimal(buffer.str());
        buffer.str("");

        int nameLength;
        for (int i = startAttribute + 9; i >= startAttribute + 9; i--) {
            int row = i / 16;
            int column = i % 16;

            buffer << str[row][column];
        }
        nameLength = Utils::Int::convertHexToDecimal(buffer.str());
        buffer.str("");

        int positionName;
        for (int i = startAttribute + 11; i >= startAttribute + 10; i--) {
            int row = i / 16;
            int column = i % 16;

            buffer << str[row][column];
        }
        positionName = Utils::Int::convertHexToDecimal(buffer.str());
        buffer.str("");

        int flags;
        for (int i = startAttribute + 13; i >= startAttribute + 12; i--) {
            int row = i / 16;
            int column = i % 16;

            buffer << str[row][column];
        }
        flags = Utils::Int::convertHexToDecimal(buffer.str());
        buffer.str("");

        int identify;
        for (int i = startAttribute + 15; i >= startAttribute + 14; i--) {
            int row = i / 16;
            int column = i % 16;

            buffer << str[row][column];
        }
        identify = Utils::Int::convertHexToDecimal(buffer.str());
        buffer.str("");

      //  Attribute* attribute = new Attribute(typeID, size, resident, nameLength, positionName, flags, identify);

        for (int i = startAttribute + 19; i >= startAttribute + 16; i--) {
            int row = i / 16;
            int column = i % 16;

            buffer << str[row][column];
        }
        int sizeContent = Utils::Int::convertHexToDecimal(buffer.str());
        buffer.str("");
        
        for (int i = startAttribute + 21; i >= startAttribute + 20; i--) {
            int row = i / 16;
            int column = i % 16;

            buffer << str[row][column];
        }
        int beginOffset = Utils::Int::convertHexToDecimal(buffer.str());
        buffer.str("");

        if (typeID == FILE_NAME_ATTRIBUTE)
        {
            long long fileRef;
            for (int i = beginOffset + startAttribute + 7; i >= beginOffset + startAttribute; i--) {
                int row = i / 16;
                int column = i % 16;

                buffer << str[row][column];
            }
            
            fileRef = Utils::LongLong::convertHexToDecimal(buffer.str());
            buffer.str("");

            string content = "";
            for (int i = beginOffset + startAttribute + 66; i <= startAttribute + beginOffset + sizeContent; i++) {
                int row = i / 16;
                int column = i % 16;

                buffer << str[row][column];
            }
            content = buffer.str();
            FileNameAttribute* fileNameAttr = new FileNameAttribute(typeID, size, resident, nameLength, positionName, flags, identify, sizeContent, beginOffset, fileRef, content);
            attributes.push_back(fileNameAttr);
        }
        else if (typeID == DATA_ATTRIBUTE)
        {
            string content = "";
            for (int i = beginOffset + startAttribute; i <= startAttribute + beginOffset + sizeContent; i++) {
                int row = i / 16;
                int column = i % 16;

                buffer << str[row][column];
            }
            content = buffer.str();
            DataAttribute* dataAttr = new DataAttribute(typeID, size, resident, nameLength, positionName, flags, identify, sizeContent, beginOffset, content);
            //dataAttr->initContent();
            attributes.push_back(dataAttr);
        }
        else {
            Attribute* attr = new Attribute(typeID, size, resident, nameLength, positionName, flags, identify);
            attributes.push_back(attr);
        }
        
       


      //  attributes.push_back(attribute);

        startAttribute = startAttribute + size;
    }

    MFTEntry* entry = new MFTEntry(byteBeginAttribute, flag, byteOfEntry, nextAttributeId, attributes, isValid);
	return entry;
}