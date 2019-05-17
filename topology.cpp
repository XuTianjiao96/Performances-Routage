#include "topology.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include <cstdlib>

using namespace std;

Topology::Topology() {}

Topology::~Topology() {}

/**
 * Méthode qui prend en entrée un fichier qui correspond
 * à une topologie et stocke les données de ce dernier en mémoire.
 */
int Topology::loadData(char *path) 
{
	hostCount = 0;
	switchCount = 0;

	ifstream topologyFile(path);
	string line;

        if ( topologyFile.is_open() ) 
	{
		while( topologyFile.good() ) 
		{
			string line;
			getline(topologyFile , line);

			if( line.empty() || (line.at(0) == '#') ) continue;
			
			if ( line.substr(0,3).compare(HOST_TYPENAME) == 0 ) 
			{
				HOST  *host = new HOST;
				size_t namepos = line.rfind('\t') + 2;
				host->name = line.substr(namepos, line.length() - namepos - 1);

				getline(topologyFile , line);

				host->srcPort = atoi(line.substr(1,line.find(']') - 1).c_str());

				int tokenPos1 = line.find('"');
				int tokenPos2 = line.rfind('"');

				host->dstName = line.substr(tokenPos1 +1, tokenPos2 - tokenPos1 -1);
				host->dstPort = atoi(line.substr(tokenPos2 + 2, line.rfind(']') - tokenPos2 - 2).c_str());

				hostCount++;
				hostList.push_back(host);
			}
			else if (line.substr(0, 6).compare(SWITCH_TYPENAME) == 0)
			{
				SWITCH *switchnode = new SWITCH;
				
				size_t namepos = line.rfind('\t');
				switchnode->name = line.substr(namepos  + 2, line.length() - namepos - 3);
				
				switchnode->portCount = atoi(line.substr(7, namepos - 7).c_str());

				for (int i = 0; i < switchnode->portCount; i++)
				{
					getline(topologyFile , line); 
					int srcport = atoi(line.substr(1, line.find(']') - 1).c_str());
					switchnode->srcPort.push_back(srcport);
					int tokenPos1 = line.find('"') ;
					int tokenPos2 = line.rfind('"') ;
					string dstname = line.substr(tokenPos1 + 1, tokenPos2 - tokenPos1 - 1);
					switchnode->dstName.push_back(dstname);
					int dstport = atoi(line.substr(tokenPos2 + 2, line.length() - tokenPos2 -3).c_str());
					switchnode->dstPort.push_back(dstport);
				}
				switchCount++;
				switchList.push_back(switchnode);
			}
		}
		topologyFile.close();
	}
	else 
	{
		cout << "Unable to open topology file : " << path << endl;
		return hostCount + switchCount;
	}

}

/**
 * Méthode d'affichage de la topologie stocké en mémoire.
 */
void Topology::printData()
{
	int i;
	for ( i = 0 ; i < getHostCount() ; i++)
	{
		struct hostNode *host = getHostById(i);
		cout << HOST_TYPENAME << "\t" << host->name << " " << host->srcPort << "\t" << host->dstName << " " << host->dstPort << endl;
	}

	for (i = 0; i < getSwitchCount() ; i++ )
	{
		struct switchNode *swnode = getSwitchById(i);
		cout << SWITCH_TYPENAME <<"\t"<< swnode->name <<"\t"<< swnode->portCount<<endl;
		for (int j = 0; j < swnode->portCount; j++)
		{
			cout << "[" << swnode->srcPort[j] << "] "<< swnode->dstName[j] << " [" << swnode->dstPort[j] << "]" << endl;
		}
	}
} 

/**
 * Méthode qui retourne tous les noeuds voisins d'un commutateur dans la topologie.
 */
struct switchNode * Topology::getSwitchByName(string name)
{
	struct switchNode *item = NULL;

	for (int i = 0; i < getSwitchCount(); i++)
	{
		struct switchNode *it = getSwitchById(i);

		if (string(it->name).compare(name) == 0)
		{
			item = it;
			break;
		}
	}

	return item;
}

