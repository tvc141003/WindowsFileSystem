#include "TreeFolder.h"

string TreeFolder::toString() {
	return "TreeFolder";
}

void TreeFolder::build(vector<MFTEntry*> entrys, int index, vector<long long>& backTrack, vector<CFolder*>& Parent) {
	if (index == entrys.size()) return;

	BYTE sector[512];
	string** sectors = ReadSector(HARD_DISK, 0, sector);
	BiosParameterBlock* BPB = new BiosParameterBlock(sectors);
	BiosParameterBlockMapper* mapper = new BiosParameterBlockMapper;
	map<string, int> mp = mapper->mapper(BPB);

	vector<CItem*> items = {};

	
	long long startCluster = entrys[index]->ref() / 512 / mp["Sc"];
	string name;
	string data;
	int size;
	long long fileRef;
	bool isFolder = true;

	

	for (Attribute* attr : entrys[index]->attributes()) {

		if (attr->id() == 0x30) {
			FileNameAttribute* fileName = dynamic_cast<FileNameAttribute*>(attr);
			name = Utils::String::convertHexToString(fileName->content());
			fileRef = fileName->fileRef();
		}
		else if (attr->id() == 0x80) {
			DataAttribute* dataAttr = dynamic_cast<DataAttribute*>(attr);
			size = dataAttr->sizeContent();
			data = dataAttr->content();

			isFolder = false;
		}
	}
	//for (int i = 0; i < backTrack.size(); i++) cout << backTrack[i] << ' ';
	//cout << endl;
	for (int i = 0; i < backTrack.size(); i++) {
		if (backTrack[i] == fileRef) {
			backTrack.pop_back();
			Parent.pop_back();
			build(entrys, index, backTrack, Parent);
			return;
		}
	}
	/*cout << name << ' ' << parent->name() << ' ' << fileRef << ' ';
	for (int i = 0; i < backTrack.size(); i++) cout << backTrack[i] << ' ';
	cout << endl;*/

	delete BPB;
	delete mapper;
	//cout << fileRef << " "  << isFolder << endl;
	if (fileRef != backTrack[backTrack.size() - 1]) {
		if (isFolder == true) {
			CFolder* subFolder = new CFolder(name, startCluster, {});
			Parent[Parent.size() - 1]->Item().push_back(subFolder);
			
			Parent.push_back(subFolder);
			backTrack.push_back(fileRef);

			build(entrys, index + 1, backTrack, Parent);
		}
		else {
			CFile* file = new CFile(name, startCluster, size, data);
			Parent[Parent.size() - 1 ]->Item().push_back(file);

			build(entrys, index + 1, backTrack, Parent);
		}
	}
	else {
		backTrack.pop_back();
		Parent.pop_back();

		build(entrys, index, backTrack, Parent);
		return;
	}

		/*if (parent != fileRef) continue;
		isEmpty = true;
		if (isFolder == true) {
			cout << fileRef << " " << name << endl;
			CFolder* subFolder = dynamic_cast<CFolder*>(build(entrys, fileRef, startCluster, name));
			if (subFolder != NULL) items.push_back(subFolder);
		}
		else {
			CFile* file = new CFile(name, startCluster, size, data);
			items.push_back(file);
		}
	}*/

	
	return;
}