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
// 树节点定义
template <class T>
struct MNode {
	// 当前结点元素
	T element;
	// 子节点集合
	vector<MNode<T>*> children;
	// 父节点
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

// 树模板
template <class T>
class MTree {
private:
	MNode<T> *root;
public:
	MTree() {

	}
	// 初始化结点
	void init(MNode<T>* root) {
		
		this->root = root;
	}
	// 添加子节点
	void putChild(MNode<T>* node, MNode<T>* parent) {

		parent->children.push_back(node);
		node->Parent = parent;
		/*
		vector<MNode<T>*> children = parent->children;
		// 二分查找出插入的位置
		MNode<T>* insertIndexNode = lower_bound(children, children+children.size(), node);
		// 插入
		children.insert(insertIndexNode, node);
		// 设置父节点
		node->parent = parent;*/
	}
	// 添加子节点集合
	void putChildren(vector<MNode<T>*> nodes, MNode<T> *parent) {
		for (int i = 0; i < nodes.size(); ++i) {
			putChild(nodes[i], parent);
		}
	}
	/*					遍历				*/
	// 遍历子节点
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
	// 遍历整个树
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
		while (!q.empty()) {/*一直循环，直到队列空，队列层序遍历的基本框架*/
			int num = q.size();
			for (int i = 0; i < num; i++) {/*统计每一层的节点树，保证处理完当前层的节点*/
				temp = q.front();
				q.pop();
				layer.push_back(temp->element);
				if (temp->children.size() != 0) {
					for (int i = 0; i < temp->children.size(); i++) {
						q.push(temp->children[i]);/*将每个节点的子节点压入队列*/
					}
				}
			}
			res.push_back(layer);/*处理完一层后，压入结果*/
			layer.clear();/*压入结果后清空layer*/
		}
		return res;
	};
};

// 树遍历处理类
template <class T>
class MTreeProcessor {

public:
	// 给定结点去处理，返回bool表示是否继续遍历下一个结点
	virtual bool process(const MNode<T> *node) = 0;
};
