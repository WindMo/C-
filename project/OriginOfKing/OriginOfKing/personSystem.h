#include "service.h"
#include <vector>
#include <queue>
#include<algorithm>
#include <map>

// �ڵ㶨��
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
	MNode(T e, MNode<T> *parent) {
		this->element = e;
		this->parent = parent;
	}
	MNode(T e) {
		this->element = e;
	}
};
class Menu {
	// �˵�

	// ��ʾ����

	// ����ֵ��Ĵ���

	// ����
};

class PersonSystemServiceSupport : public PersonService{

private:
	// ��������
	vector<vector<MNode<Person> *>> container;
	// ����
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
	/*				��ѯ			*/
	// ����������ѯ
	Person queryByName(string &personName) {

		map<string, MNode<Person> *> ::iterator it = findFormCache(personName);
		if (it == cache.end()) {
			return Person::Null;
		}
		else {

			return it->second->element;
		}
	}
	// ���ݡ�������ѯ
	vector<Person>  queryByGeneration(int &number) {

		vector<Person> persons;
		if (number >= 0 && number < container.size()) {
			vector<MNode<Person> *> MNodes = container[number];
			persons = conver(MNodes);
		}
		return persons;
	}
	// ��ѯ����
	vector<Person>  queryByChildren(string &personName) {

		map<string, MNode<Person> *>::iterator it = findFormCache(personName);
		vector<Person> children;
		if (it != cache.end()) {

			children = getChildren(it->second);
		}
		return children;
	}
	// ��ѯ��ͬ���׵���
	vector<Person>  queryByFatherName(string &fatherName) {

		// �������
		vector<Person> children;
		map<string, MNode<Person> *>::iterator itFather = findFormCache(fatherName);
		if (itFather != cache.end()) {

			children = getChildren(itFather->second);
		}
		return children;

	}
	// ��ѯ���ֵ�
	vector<Person>  queryBrother(string &personName) {

		vector<Person> brothers;
		// ����Լ�
		Person self = queryByName(personName);
		if (self.getFatherName() != "") {
			// ������׵ĺ���
			brothers = queryByChildren(self.getFatherName);
			// ɾ�����׺����е��Լ�
			for (vector<Person>::iterator it = brothers.begin(); it != brothers.end(); it++) {

				if (it->getName() == self.getName()) {
					brothers.erase(it);
					break;
				}
			}
		}
		return brothers;
	}
	/*				���			*/
	// ���һ���˲����ص�ǰ����
	int addPerson(Person &person) {


	}
	/*				�޸�			*/
	// ���������޸ĵ�ǰ���˵���Ϣ
	void updatePerson(Person &person);
	/*				ɾ��			*/
	// ��������ɾ������������Ϣ
	Person deletePerson(string &personName);
};
