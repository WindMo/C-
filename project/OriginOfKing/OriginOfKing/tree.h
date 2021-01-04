#include <iostream>
#include <vector>
#include <queue>
#include<algorithm>
using namespace std;
#ifndef DBM_MTREE_H
#define DBM_MTREE_H
#endif
// https://www.cnblogs.com/muxuan/p/ntree.html
// https://blog.csdn.net/weixin_39705503/article/details/79776161
// https://www.runoob.com/w3cnote/cpp-vector-container-analysis.html
// ���ڵ㶨��
template <class T>
struct MNode {
	// ��ǰ���Ԫ��
	T element;
	// �ӽڵ㼯��
	vector<MNode<T>*> children;
	// ���ڵ�
	MNode<T> *parent;

	MNode(T e, vector<MNode<T>*> children, MNode<T> *parent) {
		this->element = e;
		this->parent = parent;
		this->children = children;
	}
	MNode(T e,MNode<T> *parent) {
		this->element = e;
		this->parent = parent;
	}
	MNode(T e) {
		this->element = e;
	}
};
