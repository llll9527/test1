 ///
 /// @file    io3.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-16 16:24:21
 ///
 
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::istringstream;
using std::ostringstream;
using std::stringstream;

void printCinStatus(stringstream & fs)
{
	cout << "fs's badbit = " << fs.bad() << endl
		 << "fs's failbit = " << fs.fail() << endl
		 << "fs's eofbit = " << fs.eof() << endl
		 << "fs's goodbit = " << fs.good() << endl;
}

void test0()
{
	int val1 = 1;
	int val2 = 2;
	stringstream ss;
	//把其他类型的数据转化成字符串
	ss << "val1= " << val1 << " ,val2= " << val2;
	cout << ss.str() << endl;

	string str0;
	int value;
	printCinStatus(ss);
	//一旦流的状态发生改变时，会产生问题
	while(!ss.eof()) {
		ss >> str0 >> value;
		printCinStatus(ss);
		cout << str0 << " --> " << value << endl << endl;
	}
}

string int2str(int number)
{
	//sprintf();
	ostringstream oss;
	oss << number;
	return oss.str();
}

void readConfiguration(const string & filename)
{
	ifstream ifs(filename);
	if(!ifs) {
		cout << ">>> ifstream open file " << filename << " error!" << endl;
		return ;
	}

	string line;
	while(std::getline(ifs, line)) {
		istringstream iss(line);
		string key, value;
		while(!iss.eof()) {
			iss >> key >> value;
			cout << key << " --> " << value << endl;
		}
	}
}

void test1()
{
	int number = 1024;
	cout << int2str(number) << endl << endl;

	readConfiguration("my.conf");
}

 
int main(void)
{
	//test0();
	test1();
	return 0;
}
