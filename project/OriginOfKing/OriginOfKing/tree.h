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

// ��ģ��
template <class T>
class MTree {
private:
	MNode<T> *root;
public:
	MTree() {

	}
	// ��ʼ�����
	void init(MNode<T>* root) {
		
		this->root = root;
	}
	// ����ӽڵ�
	void putChild(MNode<T>* node, MNode<T>* parent) {

		parent->children.push_back(node);
		node->Parent = parent;
		/*
		vector<MNode<T>*> children = parent->children;
		// ���ֲ��ҳ������λ��
		MNode<T>* insertIndexNode = lower_bound(children, children+children.size(), node);
		// ����
		children.insert(insertIndexNode, node);
		// ���ø��ڵ�
		node->parent = parent;*/
	}
	// ����ӽڵ㼯��
	void putChildren(vector<MNode<T>*> nodes, MNode<T> *parent) {
		for (int i = 0; i < nodes.size(); ++i) {
			putChild(nodes[i], parent);
		}
	}
	/*					����				*/
	// �����ӽڵ�
	void tranversalChildren(MNode<T> *root) {

		vector<vector<T>> nodeAll = levelOrder(root);
		for (int i = 0; i< nodeAll.size(); i++) {

			vector<T> nodeLevel = nodeAll[i];
			for (int j = 0; j < nodeLevel.size(); j++) {

				T e = nodeLevel[j];
				cout << e << ", ";
			}
		}
	}
	// ����������
	void tranversal() {

		tranversalChildren(this->root);
	}


	int getMaxDepth(MNode<T> *root, vector<MNode<T>*> nodes) {

		return 0;
	}

	vector<vector<MNode<T> *>> levelOrder(MNode<T> *root) {
		vector<<MNode<T> * > layer;
		vector<vector<< MNode<T> * >> res;
		if (root == NULL) return res;

		queue<MNode<T>*> q;
		MNode<T> * temp;
		q.push(root);
		while (!q.empty()) {/*һֱѭ����ֱ�����пգ����в�������Ļ������*/
			int num = q.size();
			for (int i = 0; i < num; i++) {/*ͳ��ÿһ��Ľڵ�������֤�����굱ǰ��Ľڵ�*/
				temp = q.front();
				q.pop();
				layer.push_back(temp->element);
				if (temp->children.size() != 0) {
					for (int i = 0; i < temp->children.size(); i++) {
						q.push(temp->children[i]);/*��ÿ���ڵ���ӽڵ�ѹ�����*/
					}
				}
			}
			res.push_back(layer);/*������һ���ѹ����*/
			layer.clear();/*ѹ���������layer*/
		}
		return res;
	};
};

// ������������
template <class T>
class MTreeProcessor {

public:
	// �������ȥ��������bool��ʾ�Ƿ����������һ�����
	virtual bool process(const MNode<T> *node) = 0;
};
