#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include <cstdlib>

#include "calculation.h"
#include "topology.h"
#include "routing.h"

using namespace std;

Calculation::Calculation() {}

Calculation::~Calculation() {}

/**
 * Constructeur qui charge les informations 
 * de la topologie et table de routage en mémoire.
 */
Calculation::Calculation(char* topoFile, char* routeFile) 
{
	topologyTable.loadData(topoFile);
	routingTable.loadData(routeFile);
}

/**
 * Méthode qui calcule le nombre de sauts 
 * d'un noeud source jusqu'au noeud destination.
 * n’oubliez pas de compléter le code ! 
 */
int Calculation::getHopCount(int fromId, int toId)
{
	int count = 0;
	
	struct hostNode * fromHost = topologyTable.getHostById(fromId);
	struct hostNode * toHost = topologyTable.getHostById(toId);

	//Noeud de calcul source
	string fromNode = fromHost->name;
	//Noeud de calcul destination
	string toNode = topologyTable.getHostById(toId)->name;

	string switchName = fromHost->dstName;
	
	//TODO
	//Parcourir la table de routage du noeud fromId vers le toId
	//Aide : Regarder la struture routeItem et switchNode elles pourront vous aider.
	//Aide : struct routeItem * item = routingTable.getTableByName(switchName); permet de charger la table de routage
	//Retourner le nombre de sauts du noeud fromId vers le toId	

/*
	while (switchName != toNode) {
		routeItem * item = routingTable.getTableByName(switchName);
		int i;
		for (i = 0; i < item->dstInfo.size(); i++)
		{
			if (item->dstInfo[i] == toNode)
				break;
		}
		cout << switchName << endl;
		cout << i << endl;
		cout << item->outport[i] << endl;
		switchName = topologyTable.getSwitchByName(switchName)->dstName[item->outport[i] - 1];
		cout << switchName << endl;
		count++;
	}
*/
	cout << "From " << fromNode << " to " << toNode << ": Hop Count = " << count << endl;
	return count;
}

/**
 * Méthode qui implémente la métrique Minhop.
 */
int Calculation::calculate() 
{
	int minHop = 0; //Min value

	getHopCount(1, 8);

	//TODO 
	//Implémenter l'algo du calcul du nombre de sauts
	//Aide : Pour recueperer le nombre de saut de source vers destination -> getHopCount(source, destination);
	//Aide : Pour recuperer le nombre de HCA -> topologyTable.getHostCount();
	//retourner le minimum trouver.

	return minHop;
}

/**
 * Méthode qui calcule la charge d'un noeud
 * source jusqu'au noeud destination.
 */
int Calculation::getRoute(int fromId, int toId)
{
	struct hostNode * fromHost = topologyTable.getHostById(fromId);

	string fromNode = fromHost->name;

	string toNode = topologyTable.getSwitchById(toId)->name;
	
	cout << "From " << fromNode << " to " << toNode;

	string switchName = fromHost->dstName;


	//TODO
	//Parcourir la table de routage du noeud fromId vers le toId
	//Aide : Regarder la structure routeItem et switchNode elles pourront vous aider.
	//Aide : struct routeItem * item = routingTable.getTableByName(switchName); permet de charger la table de routage
	//Retourner 1 si le noeud toId est attainable depuis fromId sinon 0
	
	return 1;
}

/**
 * Méthode qui implémente la métrique nombre de chemins disjoints.
 */
int Calculation::balance() 
{
	int cpt = 0 ; 
	
	//TODO 
	//Implémenter l'algo du calcul de chemins disjoints 
	//Aide : Pour recueperer le nombre de sauts de source vers destination -> getHopCount(source, destination);
	//Aide : Pour recuperer le nombre de HCA -> topologyTable.getHostCount();
	//retourner la valeur maximale trouvée

	return cpt ;
}

