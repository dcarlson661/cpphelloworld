// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int func(int y)
{
	cout << "func address of y is " << &y << endl;
	return y;
}

void func2(int *y)
{
	cout << "func2 address of y is " << &y << endl;
	*y = 1;
}

int main()
{
	string str("hello");
	string::iterator it = str.begin();
	while (it != str.end())
	{
		cout << *it << ",";
		++it;
	}
	cout << endl;
	for (string::iterator it = str.begin(); it != str.end(); ++it)
	{
		cout << *it << ",";
	}
	cout << endl;
	for (string::reverse_iterator it = str.rbegin(); it != str.rend(); ++it)
	{
		cout << *it << ",";
	}
	cout << endl;
	for (string::const_iterator it = str.begin(); it != str.end(); ++it)
	{
		cout << *it << ",";
	}
	string::iterator second = str.begin() + 1;
	cout << endl << *second << endl;
	// end() - begin() gives the number of elements
	string::iterator mid = str.begin() + (str.end() - str.begin()) / 2;  // Iterator to middle element
	cout << "Middle element is " << *mid << endl;

	string::iterator last = str.end() - 1;  // Iterator to last element
	cout << "Last element is " << *last << endl;

	const char strb[] = { 'H','e','l','l','o' };
	const char *pEnd = strb + 5;
	const char *p = strb;
	while (p != pEnd)
	{
		cout << *p << ",";
		++p;
	}

	string strc("hello world");
	char c = 'l';
	cout << "the string is " << strc << endl;
	cout << "searching for char " << c << endl;
	string::iterator res = find(strc.begin(), strc.end(), c);
	if (res != strc.end())
	{
		cout << "found match " << res - strc.begin() << endl;
	}
	else
	{
		cout << "not found" << c << endl;
	}
}
int mainVec()
{
	vector<int> vec;
	vec.push_back(4);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(1);

	cout << "E0 " << vec[0] << endl;
	cout << "E2 " << vec[2] << endl;
	cout << "E4 " << vec[4] << endl;

	for (int i = 0; i < vec.size(); i++)
	{
		cout << "E" << i << "=" << vec[i] << endl;
	}
	return 0;
}

int mainLessonOne()
{
    std::cout << "Hello World!\n";
	int x = 2;
	cout << "address of x is " << &x << endl;
	int z = func(x);
	cout << "address of z is " << &z << endl;
	cout << "after calling func(), z = " << z << endl;
	cout << "----------------------" << endl;
	x = 3;
	cout << "address of x is " << &x << endl;
	func2(&x);
	cout << "after calling func2(int *y), x = " << &x << endl;
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
