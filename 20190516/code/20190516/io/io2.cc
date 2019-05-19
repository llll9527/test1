 ///
 /// @file    io2.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-16 14:30:58
 ///
 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::string;
using std::vector;

vector<string> file;
void test0()
{
	ifstream ifs;
	//ifs.open("test.txt");
	ifs.open("io2.cc");// 文件输入流要求文件必须存在
	if(!ifs.good()) {
		cout << ">> ifstream open file error!" << endl;
		return;
	}

	//string word;
	//while(ifs >> word) //以空格进行分隔 
	string line;
	while(std::getline(ifs, line))
	{
		cout << line << endl;
		file.push_back(line);
	}

	ifs.close();
}

void test1()
{
	test0();
	//输出流，如果文件不存在，直接创建文件；
	//如果文件存在，它会清空文件流的内容，再写新数据
	//ofstream ofs("test.txt", std::ios::out);
	ofstream ofs("test.txt", std::ios::app);
	//ofstream ofs("test.txt", std::ios::ate);//不起作用
	if(!ofs) {
		cout << "ofstream open file error!" << endl;
		return ;
	}
	cout << "pos = " << ofs.tellp() << endl;
	ofs << "that's new line!" << endl;

#if 0
	for(auto & line : file) {
		ofs << line << "\n";
	}
#endif

	ofs.close();
}

void test2()
{
	//ate模式针对于输入流起作用
	ifstream ifs("test.txt", std::ios::ate);
	if(!ifs) {
		cout << ">> ifstream open file error" << endl;
		return ;
	}

	cout << "pos = " << ifs.tellg() << endl;

	ifs.close();
}

void printCinStatus(fstream & fs)
{
	cout << "fs's badbit = " << fs.bad() << endl
		 << "fs's failbit = " << fs.fail() << endl
		 << "fs's eofbit = " << fs.eof() << endl
		 << "fs's goodbit = " << fs.good() << endl;
}

void test3()
{
	//fstream要求文件必须存在
	fstream fs("test2.txt");	
	if(!fs) {
		cout << "fstream open file error!" << endl;
		return;
	}

	int number;
	cout << "pls input 10 integer number:" << endl;
	for(int idx = 0; idx != 10; ++idx) {
		std::cin >> number;
		fs << number << " ";
	}
	cout << "fs's pos = " << fs.tellg() << endl;
	//printCinStatus(fs);
	cout << endl;
	fs.seekg(0);

	for(int idx = 0; idx !=10; ++idx) {
		fs >> number;
		//printCinStatus(fs);
		//cout << endl;
		cout << number << " ";
	}
	cout << endl;

	fs.close();
}

void test4()
{//从某一个文件中取出全部的内容, 保存到一个字符串中
	string filename = "vector.cc";
	ifstream ifs(filename, std::ios::ate);
	if(!ifs) {
		cout << ">>> ifstream open file " << filename << "error!" << endl;
		return ;
	}

	int length = ifs.tellg();
	cout << ">> length = " << length << endl;
	//char buff[length + 1] = {0};
	char * buff = new char[length+1]();

	ifs.seekg(std::ios::beg);
	ifs.read(buff, length);//常用的到方法
	string content(buff);
	cout << "content: --------" 
		 << content << endl
		 << "--------" << endl;
	
	delete [] buff;
	ifs.close();
}
 
int main(void)
{
	//test0();
	//test1();
	//test2();
	//test3();
	test4();
	return 0;
}
