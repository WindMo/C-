#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>
#include "util.h"
#include "tree.h"
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
	MTree<int> tree = MTree<int>();
	
	MNode<int> *root1 = &MNode<int>(100);
	MNode<int> *root2 = &MNode<int>(10);
	MNode<int> *root3 = &MNode<int>(200);
	MNode<int> *root4 = &MNode<int>(20);
	MNode<int> *root5 = &MNode<int>(300);
	MNode<int> *root6 = &MNode<int>(30);
	tree.init(root1);
	tree.putChild(root2,root1);
	tree.putChild(root3, root1);
	tree.putChild(root4, root2);
	tree.putChild(root5, root2);
	tree.putChild(root4, root3);
	tree.putChild(root5, root3);
	tree.putChild(root5, root4);
	tree.putChild(root6, root4);
	tree.tranversal();
	return 0;
}