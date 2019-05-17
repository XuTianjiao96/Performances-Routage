#include "routing.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include <cstdlib>

using namespace std;

Routing::Routing() {}

Routing::~Routing() {}

/**
 * Méthode qui prend en entrée un fichier qui correspond
 * aux tables de routage et stocke les données de ce dernier en mémoire.
 */
int Routing::loadData(char *path) 
{
	itemCount = 0;
	
	ifstream routingFile(path);
	string line;

        if ( routingFile.is_open() ) 
	{
		cout << "Veuillez patienter pendant le chargement des données..." << endl;
		while( routingFile.good() ) 
		{
			string line;
			ROUTE *item = new ROUTE;
			getline(routingFile , line);

			if (line.empty()) continue;

			if (line.find(START_CONDITION) == 0) getline(routingFile, line); 
	
			if (line.find(TABLE_HDR_MAGIC) == 0)
			{
				size_t nPos = line.rfind("guid ");

				item->slid  = atoi(line.substr(nPos - 3 , 2).c_str());
				item->guid  = strtol(line.substr(nPos + 5, 18).c_str(), NULL, 16);
				item->name  = line.substr(nPos + 25, line.length() - nPos - 27);

				getline(routingFile, line); 
				getline(routingFile, line); 
				
				for (int i = 0; ; i++)
				{
					getline(routingFile, line);
					int p = line.find(END_CONDITION);
					if ( p != string::npos ) 
					{
						item->subitems = atoi(line.substr(0, p - 1).c_str());
						break;
					}

					int lid = strtol(line.substr(0, 6).c_str(), NULL, 16);
					int outport = atoi(line.substr(7,3).c_str());
					item->lid.push_back(lid);
					item->outport.push_back(outport);
					int npos = line.rfind(':');
					string name = line.substr(npos + 3, line.length() - npos - 5);
					item->dstInfo.push_back(name);
					
					cout <<".";
				}
				routeTable.push_back(item);
				itemCount++;
			}
			
		}
		cout << "\nData Loading completed." << endl;
		routingFile.close();
	}
	else 
	{
		cout << "Unable to open routing file : " << path << endl;
		return itemCount;
	}

}

/**
 * Méthode d'affichage des tables de routage stockés en mémoire.
 */
void Routing::printData()
{
	for (int i = 0; i < getTotalCount(); i++)
	{
		struct routeItem *item = getTable(i);
		cout << "switch Lid " << item->slid << " guid " << item->guid << " [" << string(item->name) << "] subItems : " << item->subitems << endl;

		for (int j = 0; j < item->dstInfo.size(); j++)
		{
			cout << item->lid[j] << " " << item->outport[j] << " : " << item->dstInfo[j] << endl;
		}
	}	
}

/**
 * Méthode qui retourne la table de routage d'un commutateur.
 */
struct routeItem *Routing::getTableByName(string name)
{
	struct routeItem *item = NULL;
	
	for(int i = 0; i < getTotalCount() ; i++)
	{
		struct routeItem *it = getTable(i);
		if (name.compare(it->name) == 0)
		{
			item = it;
			break;
		}
	}

	return item;
} 


