#include "stdafx.h"
#include "TypeSystem.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

TypeSystem::TypeSystem()
{
}


TypeSystem::~TypeSystem()
{
}

class Widget
{
public:
	Widget(const std::string name) : m_name(name) 
	{
		std::cout << "Constructing widget with name " << m_name << std::endl;
	}
	Widget(Widget&& other) : m_name(std::move(other.m_name))
	{
		std::cout << "Move constructing widget with name " << m_name << std::endl;
	}
private:
	std::string m_name;
};

std::vector<Widget> GetSomeWidgets()
{
	std::vector<Widget> widgets;
	widgets.push_back(Widget("Rod"));
	widgets.push_back(Widget("Jane"));
	widgets.push_back(Widget("Freddy"));
	return widgets;
}

class Base 
{
public:
	virtual void DoSomethingCool() {};
};
class Derived : public Base 
{
public:
	virtual void DoSomethingCool() override {}
};

void TypeSystem::Run()
{
	int result = 0;              // Declare and initialize an integer.
	double coefficient = 10.8;   // Declare and initialize a floating
								 // point value.
	auto name = "Lady G.";       // Declare a variable and let compiler
								 // deduce the type (const char*).
#pragma warning (disable: 4101)
	int maxValue;                // Not recommended! maxValue contains
								 // garbage bits until it is initialized.
#pragma warning (default: 4101)

	// move efficiency: note we only create three widgets here.
	// Widget and std::vector support move construction.
	// As the vector grows, we move construct Widgets.
	// We then move construct the vector that is returned, which is effectively three pointer copies.
	std::vector<Widget> widgets = GetSomeWidgets();

	const char* s = "Help" + 3; // s points to the 'p'

	/////////////////
	// static_cast //
	/////////////////
	// static_cast is checked at compile time only.
	double d = 1.58947;
#pragma warning (disable: 4244)
	int i = d;  // warning C4244 possible loss of data
#pragma warning (default: 4244)
	int j = static_cast<int>(d);       // No warning.
	// Error C2440:cannot convert from double to std:string
	//std::string s = static_cast<std::string>(d); 

	// No error but not necessarily safe.
	Base* b1 = new Base();
	Derived* d1 = static_cast<Derived*>(b1);

	//////////////////
	// dynamic_cast //
	//////////////////
	//dynamic_cast, for safe, runtime-checked casts of pointer-to-base to pointer-to-derived
	Base* b2 = new Base();

	// Run-time check to determine whether b is actually a Derived*
	Derived* d2 = dynamic_cast<Derived*>(b2);

	// If b was originally a Derived*, then d2 is a valid pointer.
	if (d2)
	{
		// Safe to call Derived method.
		d2->DoSomethingCool();
	}
	else
	{
		// Run-time check failed.
		std::cout << "d2 is null" << std::endl;
	}

	////////////////
	// const_cast //
	////////////////
	// const_cast is very naughty

	//////////////////////
	// reinterpret_cast //
	//////////////////////
	// reinterpret_cast, for casts between unrelated types such as pointer to int.
	const char* str = "hello";
	//int i = static_cast<int>(str);//error C2440: 'static_cast' : cannot
								    // convert from 'const char *' to 'int'
	int j2 = (int)str; // C-style cast. Did the programmer really intend
					  // to do this?
	int k = reinterpret_cast<int>(str);// Programming intent is clear.
									   // However, it is not 64-bit safe.
}
