#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include <set>
#include <cstdlib>

#define HOST_TYPENAME		"Hca"
#define SWITCH_TYPENAME		"Switch"

#define TYPE_UNKNOWN_NODE	0	//unknown node:nothing
#define TYPE_HOSTNODE_ID	1	//normal host
#define TYPE_SWITCH_ID		2	//switch node

using namespace std;

typedef struct hostNode 
{
	string name;
	int srcPort;
	string dstName;
	int dstPort;
}HOST;

typedef struct switchNode 
{
	string name;
	int portCount;
	vector <int> srcPort;
	vector <string> dstName;
	vector <int> dstPort;
}SWITCH;

class Topology 
{
	public:
		Topology();
		~Topology();
		Topology(char *path){ loadData(path); };

		int loadData(char *path);
		void printData();
		int getHostCount() { return hostCount; };
		int getSwitchCount() { return switchCount; };
		struct hostNode * getHostById(int hid) { return hostList[hid]; };
		struct switchNode * getSwitchById(int sid) { return switchList[sid]; };
		struct switchNode * getSwitchByName(string name);

	private:
		int hostCount;
		int switchCount;
		vector <HOST *> hostList;
		vector <SWITCH *> switchList;
};

