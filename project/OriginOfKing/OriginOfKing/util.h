#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <list>
#include "pojo.h"
using namespace std;
/*
class CtimeUtils {

private:
	static string numberToString(int n);

public:
	static string ctimeToDateString(const time_t date);
	static time_t dateStringToCtime(const string dateString);
	static int compare(const time_t date1, const time_t date2);
};
string CtimeUtils::numberToString(int n) {
	cout << n << endl;
	return n < 10 && n >= 0 ?
		"0" + to_string(n) : to_string(n);
}

string CtimeUtils::ctimeToDateString(const time_t date) {

	tm *gmtm = gmtime(&date);
	string dateString = numberToString(gmtm->tm_year + 1900) + "-" 
		+ numberToString(gmtm->tm_mon + 1) + "-" 
		+ numberToString(gmtm->tm_mday);
	return dateString;
}
// dateString yyyy-MM-dd
time_t CtimeUtils::dateStringToCtime(string dateString) {

	tm tm_;
	int year, month, day;
	char c[20];
	strcpy(c, dateString.c_str());
	sscanf(c, "%d-%d-%d", &year, &month, &day);
	tm_.tm_year = year - 1900;
	 tm_.tm_mon = month - 1;
	tm_.tm_mday = day;
	tm_.tm_hour = 8;// 时区问题， +8
	tm_.tm_min = 0;
	tm_.tm_sec = 0;
	tm_.tm_isdst = 0;
	time_t t = mktime(&tm_); //已经减了8个时区 

	return t;
}
int CtimeUtils::compare(const time_t date1, const time_t date2) {

	return date1 == date2 ? 0 :
		date1 < date2 ? -1 : 1;
}
*/
// person工具类
class PersonUtils {

public:
	static string PersonToLineString(Person person) {

		return person.getName() + " "
			+ to_string(person.getBirthDate()) + " "
			+ to_string(person.getDeathDate())
			+ (person.getFatherName() == "" ? "" : " " + person.getFatherName());
	}
	static Person lineStringToPerson(string lineString) {

		// 以string的正向迭代器一次for循环分割出： 姓名 生年 卒年 父亲名字，并保存到数组中
		char blank = ' ';
		string strArray[4];
		int index = 0;
		// 前一个字符是空白字符与否
		bool isBlankLast = false;
		string::iterator iter = lineString.begin();
		for (; iter < lineString.end(); iter++) {

			if (*iter == blank) {
				if (!isBlankLast) {
					index++;
				}
				isBlankLast = true;
			}
			else {
				isBlankLast = false;
				strArray[index] += *iter;
			}
		}

		// 姓名
		string name = strArray[0];
		// 生年
		int birthDate;
		sscanf(strArray[1].c_str(), "%d", &birthDate);
		// 卒年
		int deathDate;
		sscanf(strArray[2].c_str(), "%d", &deathDate);
		// 父亲姓名
		string fatherName = strArray[3];

		Person person = Person(name, birthDate, deathDate, fatherName);
		return person;
	}
	
};

class FileUtils {

public:
	static list<Person> openFile(string filePath) {

		ifstream infile;
		string temp;
		list<Person> persnList = list<Person>();
		// 按行读取
		infile.open(filePath);
		if (!infile.is_open()) {

			cout << "open file failure" << endl;
		}
		else {
			while (getline(infile, temp)) {
			
				Person person = PersonUtils::lineStringToPerson(temp);
				persnList.push_back(person);
			}
			infile.close();
		}
		return persnList;
	}
	static int saveFile(list<Person> personList, string filePath) {

		ofstream outfile;
		string temp;
		outfile.open(filePath);
		if (!outfile.is_open()) {

			cout << "open file failure" << endl;
		}
		else {
			list<Person>::iterator it;
			for (it = personList.begin(); it != personList.end(); it++) {

				outfile << PersonUtils::PersonToLineString(*it) << endl;
			}
			outfile.close();
		}

		return 0;
	}
};