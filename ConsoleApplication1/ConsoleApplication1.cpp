// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <tuple>
#include <bitset>
#include <functional>
#include <chrono>
#include <thread>
#include <random>
#include <atomic>
#include <future>

using namespace std;
using namespace std::placeholders;
using namespace std::literals;

void print(const set<int>& s)
{
	cout << "Set Values:";
	set<int>::iterator it;
	for (it = s.begin(); it != s.end(); ++it)
	{
		cout << *it << ",";
	}
	cout << endl;
}
//Note the const arg map makes it different then the print with a set arg
void print(const map<string, int>& scores) 
{
	cout << "Map elements: " << endl;
	map<string, int>::const_iterator it;
	for (it = scores.begin(); it != scores.end(); ++it)
		cout << it->first << " has a score of " << it->second << endl;
	cout << endl;
}

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

class is_shorter 
{
public:
	bool operator () (const string& lhs, const string& rhs)
	{
		return lhs.size() < rhs.size();
	}
};

//from sec4 lambdas
class Test {
	int time{ 10 };                                      // Data member
public:
	void countdown() {                              // Member function which calls a lambda expression
		[this]() {        			                // Capture class instance by reference
			if (time > 0)
				cout << "t-minus " << time << endl;
			else if (time == 0)
				cout << "Liftoff!" << endl;
			--time;
		}();			 			   			// Call the lambda function
	}
};
//sec4lambdapartical
auto greeter(const string& salutation) {
	return [salutation](const string& name) {return salutation + "," + name; };
}

#pragma region Region_1_lesson17 virtual
class Drawable
{
public:
	virtual void draw() const = 0;
	virtual ~Drawable() {};
};
class Circle : public Drawable
{
public:
	void draw() const { cout << "I'm a circle!\n"; }
};
class Triangle : public Drawable
{
public:
	void draw() const { cout << "I'm a triangle!\n"; }
};
//not in one of the example classes rather its a stand alone that will call into the classes
void draw_shape(const Drawable& d) 
{
	d.draw(); // Calls draw member function of Circle etc
}
#pragma endregion Region_1_lesson17 virtual

template <class T>
T Max(const T& t1, const T& t2)
{
	if (t1 > t2)
		return t1;
	return t2;
}

//a predicate because it only returns a bool
// do the const parameters have anything to do with it being a predicate
// this can be used in a for loop in mainSortByPredicateAndFunctor
bool is_shorterPredicate(const string& lsh, const string& rsh)
{
	return lsh.size() < rsh.size();
}

//for bind example the argument are by Reference
void incrFunctionWhichTakesArgsByReference(int& number, int& value)
{
	number = value;
	++value;
}
void square(double x)
{
	std::cout << "square " << x << "^2 == " << x * x << std::endl;
}

void product(double x, double y)
{
	std::cout << "double " << x << "*" << y << " == " << x * y << std::endl;
}


///////////////////////////////////////////////////////
//lesson80
int func80()
{
	cout << "Executing func in thread with ID " << this_thread::get_id() << endl;
	std::this_thread::sleep_for(5s);
	return 42;

}
int mainPackagedTask()
{
	packaged_task<int(int, int)> ptask([&](int a, int b) {return a + b; });
	future<int> fut = ptask.get_future();
	ptask(6, 7);
	cout << "6+7 is " << fut.get() << endl;

	cout << "In main thread with ID " << this_thread::get_id() << endl;
	cout << "Calling func..." << std::endl;
	//auto result = std::async(std::launch::async, func80);
    auto result = std::async(std::launch::deferred, func80);
	//auto result = std::async(func80);
	std::this_thread::sleep_for(2s);
	std::cout << "Calling get()" << std::endl;
	std::cout << result.get() << std::endl;

	return 0;
}


//lesson77 atomic
atomic<int> counter{ 0 };
void task()
{
	for (int i = 0; i < 100'000; i++)
	{
		++counter;
	}
}
int mainAtomic()
{
	vector<thread> tasks;
	for (int i = 0; i < 10; i++)
	{
		tasks.push_back(thread{ task });
	}
	for (auto& t : tasks)
	{
		t.join();
	}
	std::cout << counter << endl;
	return 0;
}

//rememeber the real main() is at the BOTTOM of this code 
// and above main are the "prototypes" instead of a header or prototypes
//

//section4 misc functions like BIND
// i had to read this explination and example to "start" to get bind with placeholders

int mainDrunkardWalk()
{
	vector<int> vec{ 3, 1, 4, 1, 5, 9 };
	static mt19937 mt; //include random

	static bernoulli_distribution berni;
	//static bernoulli_distribution b(0.75);
	int x = 1;
	const int WIDTH = 40;
	int sign = 1;

	while (true) {
		if (berni(mt)) {
			sign = 1;
		}
		else {
			sign = -1;
		}
		if (x == 1) {
			sign = 1;
		}
		if (x == WIDTH) {
			sign = -1;
		}
		x += sign;
		cout << string(x, ' ') << '.' << string(WIDTH - x + 1, ' ') << "\r" << flush;
		std::this_thread::sleep_for(100ms);
	}

	return 0;
}
//lesson61
int mainMiscFunctions() 
{
	int n{ 2 };   //int n initialized to 2
	// Bind n becomes the second argument of incr and is called a "capture"
	// remember you need "using namespace std::placeholders;"
	// capture the value 'n' as the second argument.  remember the first argument is the function pointer
	// bind always passes arguments by value NOT REFERENCE so 'n' is copied
	//  and the copy of n is modified by the function not the real 'n'
	// _1 placeholder is  bound to  the first argument of incrFunctionWhichTakesArgsByReference(int& number, int& value)
	//                                                                        which means -1 becomes "number" 
	//
	auto incr_n = bind(incrFunctionWhichTakesArgsByReference, _1, n); //"auto" think var with a little different

	vector<int> numbers(5); //just give me an array of numbers
	for (int i = 0; i < numbers.size(); i++)
	{
		//the actual function takes two int arguments
		// incrFunctionWhichTakesArgsByReference(int& number, int& value)
		//
		//incr_n is "bound" with the signature (func, _1, n);  //see just above
		//  which means n, a local scope int,  becomes captured as the n in the signature
		//  the local n never changes because bind is always pass by value (copy) not a ref (pointer to)
		//
		//
		incr_n(i);
	}
	//after the for
	cout << "After for int i= call, elements are:" << endl;
	for (auto number : numbers)
		 cout << number << ", ";
	cout << endl << endl << "n = " << n << endl;   // Has value of n changed?

	for (auto& number : numbers)
	{
		incr_n(number);                            // Call incr with bound argument
	}
	cout << "After auto% for call, elements are:" << endl;
	for (auto number : numbers)
		cout << number << ", ";
	cout << endl << endl << "n = " << n << endl;   // Has value of n changed?


	//https://docs.microsoft.com/en-us/cpp/standard-library/1-object?view=msvc-160
	double arg[] = { 1, 2, 3 };
	std::for_each(&arg[0], &arg[3], square); //call square with no binds
	std::cout << std::endl;

	std::for_each(&arg[0], &arg[3], std::bind(product, _1, 2)); //_1 becomes 1,2,3 the last arg 2 is hardcode constant
	std::cout << std::endl;

	std::for_each(&arg[0], &arg[3], std::bind(square, _1)); //_1 becomes 1,2,3

	string hello{ "hello," };
	string pi(to_string(3.14159));
	hello += pi;
	cout << hello << endl;

	cout << stoi(pi) << endl;
	cout << stod(pi) << endl;

	return 0;
}

//section5bitset
int mainbitset()
{
	bitset<8> b1{ "10101110" };                                // Initialize from string literal - bitset with value 174
	bitset<8> b2{ 0xae };                                      // Initialize from integer value (decimal or hexadecimal)
	bitset<8> b3{ 0b1010'1110 };                               // Initialize from binary constant (C++14)

	bitset<8> b4{ 0b010'1010 };                                // Bitset with value 42

	cout << "b1 bit 2 test ="<< b1.test(1) << endl;
	cout << "b1 bit 4 test =" << b1.test(4) << endl;
	for (std::size_t i = 0; i < b1.size(); ++i) {
		std::cout << "b1 bit "<< i << " test=" << b1.test(i) << '\n';
	}

	cout << "b1 is " << b1 << endl;                          // Displays 10101110
	cout << "b4 is " << b4 << endl;                          // Displays 00101010
	cout << "b2 in decimal is " << b2.to_ulong() << endl;    // Displays 174
	cout << "b2 as a string is " << b2.to_string() << endl;  // Displays 10101110

	cout << "~b1 is " << ~b1 << endl;                        // Displays 01010001

	cout << "b1 & b4 is " << (b1 & b4) << endl;               // Displays 00101010
	cout << "b1 | b4 is " << (b1 | b4) << endl;              // Displays 10101110
	cout << "b1 ^ b4 is " << (b1 ^ b4) << endl;              // Displays 10000100

	return 0;
}

//section5
int mainTuple() 
{
	string s = "helloworld"s; 
	cout << s << endl;

	tuple<double, int, string>numbers{ 88.0, 2, "Three"s};
	//or
	auto numbers2{ make_tuple(99.0, 2, "three"s) };

	double dd = 111.2;
	std::tuple_cat(numbers, make_tuple(dd, 5, "SEEME"s));

	tuple<int, std::string, bool> foo{ 10, "Hello, world!", false };
	auto foo_ext = std::tuple_cat(foo, std::make_tuple('a'));

	auto x = get<0>(numbers); //Store the first element
	std::cout << "First " << x << endl;

	cout << "second to 3" << endl;
	get<1>(numbers) = 3;

	//c++14
	auto i = get<int>(numbers); //store in element i
	cout << "v=" << i << endl;

	//continued with Tie.cpp
	double d;
	int ii;
	string str;

	tie(d, ii, str) = numbers;              // Store all elements in variables
	cout << "Tuple elements are: " << d << ", " << i << R"(, ")" << str << R"(")" << endl;

	return 0;
}


//section 4 lambda expressions 
int mainSection4Lambdas()
{
	std::cout << "clearer of which cout is being used" << std::endl;
	cout << "using namespace std i can reference just cout not std::cout" << endl;
	vector<int> vec{ 3,1,4,1,5,9 };// notice no '=' straight to the brackets is enough

	auto n_odd = count_if(vec.cbegin(), vec.cend(),
			[](const int n) {
				return(n % 2 == 1);
			}
		);

	cout << "number odd=" << n_odd << endl;

	Test test; //a class up above that contains a lambda function with this to itself
	test.countdown(); //only decraments once. its not a loop the value is kept

	auto greet_formal = greeter("Good Morning"s);  
	//NOW "Good Morning" is stored in greet_formal.
	cout << "Formal greeting:" << greet_formal("Dr Stroustrup") << endl;

	//c++14
	string str1{ "hello" };
	string str2{ " world" };
	auto func = [](auto x, auto y) {return x + y; };
	cout << "one: " << func(2, 5) << endl;
	cout << "two: " << func(str1, str2) << endl;


	return 0;
}
int main16virtualandbasicexception()
{
	//virtualfunctionlesson16 and exception lesson17:
	vector<Drawable*> shapes;
	shapes.push_back(new Circle());
	shapes.push_back(new Triangle());
	for (vector<Drawable*>::iterator it = shapes.begin(); it != shapes.end();  ++it)
	{
		(*it)->draw();
	}

	Circle circle;
	draw_shape(circle);

	vector<int> v;
	try {
		if (v.size() < 3)
			throw std::out_of_range("Oops");
		cout << v[2] << endl;
	}
	catch (const std::exception& e) {           // Will handle all subclasses of std::exception
		cout << "Exception caught: " << e.what() << endl;               // Print out a description of the exception
	}



	return 0;
}
int mainSortByPredicateAndFunctor() 
{
	vector<string> words;
	words.push_back("a");
	words.push_back("collection");
	words.push_back("of");
	words.push_back("words");
	words.push_back("with");
	words.push_back("varying");
	words.push_back("lengths");

	sort(words.begin(), words.end());
	cout << "alpha" << endl;
	vector<string>::iterator it;
	for (it = words.begin(); it != words.end(); ++it)
	{
		cout << *it << ",";
	}
	cout << endl;

	sort(words.begin(), words.end(), is_shorterPredicate);
	cout << "by predicate len" << endl;
	for (it = words.begin(); it != words.end(); ++it)
	{
		cout << *it << ",";
	}
	cout << endl;

	sort(words.begin(), words.end(), is_shorter());
	cout << "by functor len" << endl;
	for (it = words.begin(); it != words.end(); ++it)
	{
		cout << *it << ",";
	}
	cout << endl;


	return 0;
}
int mainVecSort()
{
	vector<string> words;
	string s;

	cout << "Please type in some words separated by spaces type stop or ctrl-z to finish" << endl;
	while (cin >> s && s!="stop")
	{
		words.push_back(s);
	}

	sort(words.begin(), words.end());

	vector<string>::iterator it;
	for (it = words.begin(); it != words.end(); ++it)
	{
		cout << *it << ",";
	}

	return 0;
}
int mainMap()
{
	map <string, int> scores;
	scores.insert(make_pair<string, int>("Maybelline", 96));
	scores.insert(make_pair<string, int > ("Graham", 78));
	print(scores);

	cout << "Graham has a score of " << scores["Graham"] << endl;

	cout << "Settings Graham's score to 66 " << endl;
	scores["Graham"] = 66;
	print(scores);
	cout << "Adding Grace's score of 66" << endl;
	scores["Grace"] = 66;           // Creates a new element with key "Grace"
	print(scores);

	map<string, int>::const_iterator p = scores.find("Graham");
	if (p != scores.end())
	{
		cout << "Found element with key " << p->first << ". it has value " << p->second << endl;
	}


	return 0;
}

//simple set
int main11Set()
{
	set < int> s; // the element is the key and value
	s.insert(6);
	s.insert(7);
	s.insert(4);
	s.insert(5);
	s.insert(3);
	print(s);

	cout << endl << "Trying to insert 3" << endl;
	pair < set<int>::iterator, bool> ret;
	ret = s.insert(3);
	if (ret.second)
	{
		cout << "added value 3 to set \n";
	}
	else
	{
		cout << "Set already contains" << *(ret.first) << endl;
	}
	s.erase(3);
	print(s);
	return *(ret.first);
}

//string::iterator over string and find for loops
int main7()
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
	return 0;
}

//vector simple introduction
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

//start here and call the study functions above
int main()
{
	mainPackagedTask();
	//mainAtomic();
	//mainDrunkardWalk();
	//mainMiscFunctions();
	//mainbitset();
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
