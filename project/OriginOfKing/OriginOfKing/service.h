#include "pojo.h"
#include "util.h"
#include <list>
class PersonService {

public:
	/*				查询			*/
	// 根据姓名查询
	virtual Person queryByName(string personName)= 0;
	// 根据“代”查询
	virtual list<Person>  queryByGeneration(int number)= 0;
	// 查询孩子
	virtual list<Person>  queryByChildren(string personName)= 0;
	// 查询相同父亲的人
	virtual list<Person>  queryByFatherName(string fatherName)= 0;
	// 查询其兄弟
	virtual list<Person>  queryBrother(string personName)= 0;
	/*				添加			*/
	// 添加一个人并返回当前总数
	virtual int addPerson(Person person)= 0;
	/*				修改			*/
	// 根据名字修改当前的人的信息
	virtual void updatePerson(Person person)= 0;
	/*				删除			*/
	// 根据名字删除，返回其信息
	virtual Person deletePerson(string personName)= 0;
};
class DataService {

public:
	// 读取
	virtual void readData() = 0;
	// 保存
	virtual void saveData() = 0;
};
class ShowService {

public:
	// 显示单个人
	virtual void show(Person person) = 0;
	// 显示树
	virtual void show(list<Person>  personList) = 0;
};
class PersonSystem : public PersonService, public DataService {

public:
	// 初始化系统，通过路径
	virtual void init(string filePath) = 0;
	// 启动系统
	virtual void start() = 0;
	// 退出系统
	virtual void exit() = 0;
};
