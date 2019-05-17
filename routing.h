#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include <set>
#include <cstdlib>

#define START_CONDITION		"ibwarn: "
#define END_CONDITION		"valid lids dumped"
#define TABLE_HDR_MAGIC		"Unicast lids"

using namespace std;

// routing information table item descriptor
typedef struct routeItem
{
	int slid;	
	int guid;						
	string name;					
	vector <int> lid;				
	vector <int> outport;			
	vector <string> dstInfo;		
	int subitems;
}ROUTE;

class Routing
{
	public:
		Routing();
		~Routing();
		Routing(char * path) { itemCount = loadData(path); };

		int loadData(char * path);	
		void printData();  
		int getTotalCount() { return routeTable.size(); };
		struct routeItem *getTable(int id) {return routeTable[id];};
		struct routeItem *getTableByName(string name);
		
	private:
		int itemCount;
		vector<ROUTE *> routeTable;
};

