#include "service.h"
#include <vector>
#include <queue>
#include<algorithm>
#include <map>

// 节点定义
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
	MNode(T e, MNode<T> *parent) {
		this->element = e;
		this->parent = parent;
	}
	MNode(T e) {
		this->element = e;
	}
};
class Menu {
	// 菜单

	// 显示内容

	// 输入值后的处理

	// 返回
};

class PersonSystemServiceSupport : public PersonService{

private:
	// 数据容器
	vector<vector<MNode<Person> *>> container;
	// 索引
	map<string, MNode<Person> *> cache;
	void initCache() {

		for (int i = 0; i < container.size(); i++) {

			vector<MNode<Person> *> layer = container[i];
			for (int j = 0; j < layer.size(); j++) {

				MNode<Person> * node = layer[j];
				string key = node->element.getName;
				cache[key] = node;
			}
		}
	}
	map<string, MNode<Person> *>::iterator findFormCache(string &personName) {

		map<string, MNode<Person> *>::iterator it = cache.find(personName);
		return it;
	}
	vector<Person> conver(vector<MNode<Person> *> &MNodes) {

		vector<Person> persons;
		for (int i = 0; i < MNodes.size(); i++) {
			MNode<Person> * node = MNodes[i];
			persons.push_back(node->element);
		}
		return persons;
	}
	vector<Person> getChildren(MNode<Person> *mNode) {

		return conver(mNode->children);
	}
public:
	PersonSystemServiceSupport(vector<vector<MNode<Person> *>> &container) {

		this->container = container;
		initCache();
	}
	/*				查询			*/
	// 根据姓名查询
	Person queryByName(string &personName) {

		map<string, MNode<Person> *> ::iterator it = findFormCache(personName);
		if (it == cache.end()) {
			return Person::Null;
		}
		else {

			return it->second->element;
		}
	}
	// 根据“代”查询
	vector<Person>  queryByGeneration(int &number) {

		vector<Person> persons;
		if (number >= 0 && number < container.size()) {
			vector<MNode<Person> *> MNodes = container[number];
			persons = conver(MNodes);
		}
		return persons;
	}
	// 查询孩子
	vector<Person>  queryByChildren(string &personName) {

		map<string, MNode<Person> *>::iterator it = findFormCache(personName);
		vector<Person> children;
		if (it != cache.end()) {

			children = getChildren(it->second);
		}
		return children;
	}
	// 查询相同父亲的人
	vector<Person>  queryByFatherName(string &fatherName) {

		// 查出父亲
		vector<Person> children;
		map<string, MNode<Person> *>::iterator itFather = findFormCache(fatherName);
		if (itFather != cache.end()) {

			children = getChildren(itFather->second);
		}
		return children;

	}
	// 查询其兄弟
	vector<Person>  queryBrother(string &personName) {

		vector<Person> brothers;
		// 查出自己
		Person self = queryByName(personName);
		if (self.getFatherName() != "") {
			// 查出父亲的孩子
			brothers = queryByChildren(self.getFatherName);
			// 删除父亲孩子中的自己
			for (vector<Person>::iterator it = brothers.begin(); it != brothers.end(); it++) {

				if (it->getName() == self.getName()) {
					brothers.erase(it);
					break;
				}
			}
		}
		return brothers;
	}
	/*				添加			*/
	// 添加一个人并返回当前总数
	int addPerson(Person &person) {


	}
	/*				修改			*/
	// 根据名字修改当前的人的信息
	void updatePerson(Person &person);
	/*				删除			*/
	// 根据名字删除，返回其信息
	Person deletePerson(string &personName);
};
