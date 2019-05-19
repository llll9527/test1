 ///
 /// @file    io1.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-16 11:30:44
 ///
 
#include <iostream>
#include <string>
#include <limits>
using std::cin;
using std::cout;
using std::endl;
using std::string;

void printCinStatus()
{
	cout << "cin's badbit = " << cin.bad() << endl
		 << "cin's failbit = " << cin.fail() << endl
		 << "cin's eofbit = " << cin.eof() << endl
		 << "cin's goodbit = " << cin.good() << endl;
}

void test0()
{
	int number = -1;	
	printCinStatus();
	//operator>>(cin, number);
	//while(cin);//cin.good()
	//if(!cin);//if(!cin.good())

	while(cin >> number, !cin.eof()) {
		cout << "number = " << number << endl;
		printCinStatus();//一旦流的状态不是有效状态，流无法正常工作的
		if(!cin.good()) {
			cin.clear();//重置流的状态
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//清空缓冲区的操作
			printCinStatus();
		}
	}

	cin.clear();
	cin.ignore(1024, '\n');

	cout << "input string:" << endl;
	string str;
	cin >> str;

	cout << "str = " << str << endl;
}
 
int main(void)
{
	test0();
	return 0;
}
