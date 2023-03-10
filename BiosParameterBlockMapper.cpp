#include"BiosParameterBlockMapper.h"

#include"BiosParameterBlock.h"

#include <sstream>
using std::stringstream;
string BiosParameterBlockMapper::toString()
{
	return "BiosParameterBlockMapper"; 

}


map<string, int> BiosParameterBlockMapper::mapper(Object* origin)
{
	BiosParameterBlock* BPB = dynamic_cast<BiosParameterBlock*> (origin);
	map<string, int> mp = {};

	stringstream buffer;
	string** sectors = BPB->sector();
	// sector per Cluster (0D,1)
	int sectorPerCluster = 0;
	buffer << sectors[0][13]; 
	sectorPerCluster = Utils::Int::convertHexToDecimal(buffer.str());
	mp.insert({ "Sc", sectorPerCluster });
	buffer.str("");
	// MFT's Start Cluster (30,8)

	int startClusterMFT = 0;
	for (int i = 7; i >= 0; i--)
	{
		buffer << sectors[3][i];
	 }
	startClusterMFT = Utils::Int::convertHexToDecimal(buffer.str());
	mp.insert({ "ClusterBeginMFT",startClusterMFT });
	buffer.str("");
	// Size MFT entry 
	int SizeMFTentry = 0; 
	buffer << sectors[4][0];
	SizeMFTentry = Utils::Int::convertHexToDecimal(buffer.str());
	mp.insert({ "SizeMFTentry",SizeMFTentry });
	buffer.str("");
	// num cluster of Index Buffer 
	
	int IndexBufferCluster = 0;
	buffer << sectors[4][4];
	IndexBufferCluster = Utils::Int::convertHexToDecimal(buffer.str());



	mp.insert({ "IndexBufferCluster" , IndexBufferCluster });

	buffer.str("");


	return mp;
}