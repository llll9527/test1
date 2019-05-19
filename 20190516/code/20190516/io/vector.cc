 ///
 /// @file    vector.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-16 14:45:09
 ///
 
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;// 动态数组

int arr[10];

void printCapacity(vector<int> & vec)
{
	//size() 当前元素的个数
	cout << "vec's size() = " << vec.size() << endl;
	//capacity() 当前数组能够容纳元素的个数
	cout << "vec's capacity() = " << vec.capacity() << endl;
}
 
int main(void)
{
//动态数组的实现原理:
//	当size() == capacity() ，并且还需要再往其中添加新元素时，
//	必须要扩容: 
//		1. 先申请2 * capacity() 的空间，
//		2. 再把原来空间的所有元素复制到新空间中
//		3. 销毁原来空间的所有元素，并回收原来的空间
//		4. 再在新空间的末尾添加新元素
//
//尽管可以动态扩容，但扩容时的开销是很大的
	vector<int> numbers;
	numbers.reserve(30);//预先开辟空间
	printCapacity(numbers);
	cout << "sizeof(numbers) = " << sizeof(numbers) << endl;

	numbers.push_back(1);
	printCapacity(numbers);

	numbers.push_back(1);
	printCapacity(numbers);

	numbers.push_back(1);
	printCapacity(numbers);

	numbers.push_back(1);
	printCapacity(numbers);

	numbers.push_back(1);
	printCapacity(numbers);
	for(int idx = 0; idx != 10; ++idx) {
		numbers.push_back(idx);
	}

	//数组下标形式的访问
	for(size_t idx = 0; idx != numbers.size(); ++idx) {
		cout << numbers[idx] << " ";
	}
	cout << endl;

	//c++11 for-loop
	for(auto & number : numbers) {
		cout << number << " ";
	}
	cout << endl;

	//迭代器
	for(auto it = numbers.begin(); it != numbers.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;

	cout << "sizeof(numbers) = " << sizeof(numbers) << endl;
	return 0;
}
