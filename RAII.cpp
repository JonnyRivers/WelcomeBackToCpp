#include "stdafx.h"
#include "RAII.h"

#include <iostream>
#include <memory>

RAII::RAII()
{
}


RAII::~RAII()
{
}

class MyResource
{
public:
	MyResource() 
	{
		std::cout << "MyResource constructor" << std::endl;
	}
	~MyResource() 
	{
		std::cout << "MyResource destructor" << std::endl;
	}
};

class MyClass
{
public:
	MyClass(MyResource* resource) : m_resource(resource) 
	{
		std::cout << "MyClass constructor" << std::endl;
	}
	~MyClass()
	{
		std::cout << "MyClass destructor" << std::endl;
	}
private:
	std::unique_ptr<MyResource> m_resource;
};

void RAII::Run()
{
	MyClass c(new MyResource());
}