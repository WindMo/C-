#include "pojo.h"
#include "util.h"
#include <list>
class PersonService {

public:
	/*				��ѯ			*/
	// ����������ѯ
	virtual Person queryByName(string personName)= 0;
	// ���ݡ�������ѯ
	virtual list<Person>  queryByGeneration(int number)= 0;
	// ��ѯ����
	virtual list<Person>  queryByChildren(string personName)= 0;
	// ��ѯ��ͬ���׵���
	virtual list<Person>  queryByFatherName(string fatherName)= 0;
	// ��ѯ���ֵ�
	virtual list<Person>  queryBrother(string personName)= 0;
	/*				���			*/
	// ���һ���˲����ص�ǰ����
	virtual int addPerson(Person person)= 0;
	/*				�޸�			*/
	// ���������޸ĵ�ǰ���˵���Ϣ
	virtual void updatePerson(Person person)= 0;
	/*				ɾ��			*/
	// ��������ɾ������������Ϣ
	virtual Person deletePerson(string personName)= 0;
};
class DataService {

public:
	// ��ȡ
	virtual void readData() = 0;
	// ����
	virtual void saveData() = 0;
};
class ShowService {

public:
	// ��ʾ������
	virtual void show(Person person) = 0;
	// ��ʾ��
	virtual void show(list<Person>  personList) = 0;
};
class PersonSystem : public PersonService, public DataService {

public:
	// ��ʼ��ϵͳ��ͨ��·��
	virtual void init(string filePath) = 0;
	// ����ϵͳ
	virtual void start() = 0;
	// �˳�ϵͳ
	virtual void exit() = 0;
};
