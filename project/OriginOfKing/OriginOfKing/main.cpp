#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>
#include "util.h"
#include "tree.h"
#include <map>
using namespace std;

int main()
{

	// 读取
	/*
	string filePath = "C:\\Users\\Administrator\\Desktop\\c++单子\\Genghis Khan.txt";
	list<Person> l = FileUtils::openFile(filePath);
	list<Person>::iterator it;
	for (it = l.begin(); it != l.end(); ++it) {

		cout << PersonUtils::PersonToLineString(*it) << endl;
	}
	FileUtils::saveFile(l, "C:\\Users\\Administrator\\Desktop\\c++单子\\1.txt");
	*/
	map<int, int> mp;
	mp.insert(make_pair(1, 10));
	mp[1] = 11;
	mp.insert(make_pair(2, 20));
	mp.insert(make_pair(3, 30));
	map<int, int>::iterator it;
	for (it = mp.begin(); it != mp.end(); it++) {
		cout << it->first << ": " << it->second << endl;
	}
	map<string, int> mp2;
	mp2["aaa"] = 10;
	map<string, int>::iterator it2;
	for (it2 = mp2.begin(); it2 != mp2.end(); it2++) {
		cout << it2->first << ": " << it2->second << endl;
	}
	return 0;
}