#include "stdafx.h"
#include "UniformInitialization.h"

#include <initializer_list>
#include <map>
#include <string>
#include <vector>

UniformInitialization::UniformInitialization()
{
}


UniformInitialization::~UniformInitialization()
{
}

class BraceInitialization {
public:
	BraceInitialization() {}
	BraceInitialization(std::string str) : m_string{ str } {}
	BraceInitialization(std::string str, double dbl) : m_string{ str }, m_double{ dbl } {}
	double m_double;
	std::string m_string;
};

// Delegating Constructors
//////////////////////////
class DumbConstructors
{
public:
	int max;
	int min;
	int middle;

	DumbConstructors() {}
	DumbConstructors(int my_max) {
		max = my_max > 0 ? my_max : 10;
	}
	DumbConstructors(int my_max, int my_min) {
		max = my_max > 0 ? my_max : 10;
		min = my_min > 0 && my_min < max ? my_min : 1;
	}
	DumbConstructors(int my_max, int my_min, int my_middle) {
		max = my_max > 0 ? my_max : 10;
		min = my_min > 0 && my_min < max ? my_min : 1;
		middle = my_middle < max && my_middle > min ? my_middle : 5;
	}
};

class DelegatingConstructors
{
public:
	int max;
	int min;
	int middle;

	DelegatingConstructors(int my_max) {
		max = my_max > 0 ? my_max : 10;
	}
	DelegatingConstructors(int my_max, int my_min) : DelegatingConstructors(my_max) {
		min = my_min > 0 && my_min < max ? my_min : 1;
	}
	DelegatingConstructors(int my_max, int my_min, int my_middle) : DelegatingConstructors(my_max, my_min) {
		middle = my_middle < max && my_middle > min ? my_middle : 5;
	}
};


void UniformInitialization::Run()
{
	// Brace initialization
	///////////////////////
	BraceInitialization o1{};
	BraceInitialization o1_1;

	BraceInitialization o2{ "ww" };
	BraceInitialization o2_1("xx");

	// Note that the order is as specified in the constructor(string then double), not the memory layout
	BraceInitialization o3{ "yy", 4.4 };
	BraceInitialization o3_1("zz", 5.5);

	// initializer_list
	///////////////////
	std::vector<int> v1{ 9, 10, 11 };
	std::map<int, std::string> m1{ { 1, "a" },{ 2, "b" } };
	std::string s{ 'a', 'b', 'c' };
	std::initializer_list<int> ilist{ 5, 6, 7 };
	std::vector<int> v2(ilist);
}