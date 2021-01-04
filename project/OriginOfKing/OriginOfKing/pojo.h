#include <iostream>
#include <ctime>
using namespace std;
class Person {

private:
	// 姓名
	string name;
	// 生年
	int birthDate;
	// 卒年
	int deathDate;
	// 父亲姓名
	string fatherName;

public:
	static const Person Null;
	Person(string name, int birthDate, int deathDate, string fatherName) {

		this->name = name;
		this->birthDate = birthDate;
		this->deathDate = deathDate;
		this->fatherName = fatherName;
	}
	~Person() {

	}
	string getName() {
		return this->name;
	}
	void setName(string name) {
		this->name = name;
	}
	int getBirthDate() {
		return this->birthDate;
	}
	void setBirthDate(int birthDate) {
		this->birthDate = birthDate;
	}
	int getDeathDate() {
		return this->deathDate;
	}
	void setDeathDate(int deathDate) {
		this->deathDate = deathDate;
	}
	string getFatherName() {
		return this->fatherName;
	}
	void setFatherName(string fatherName) {
		this->fatherName = fatherName;
	}
	// 重载运算符
	bool operator==(const Person& person) {

		return this->name == person.name;
	}
	bool operator<(const Person& person) {

		return this->birthDate < person.birthDate;
	}
	bool operator>(const Person& person) {

		return this->birthDate > person.birthDate;
	}
};