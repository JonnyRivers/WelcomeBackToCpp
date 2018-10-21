#include "stdafx.h"
#include "Pimpl.h"

#include <iostream>
#include <memory>

Pimpl::Pimpl()
{
}


Pimpl::~Pimpl()
{
}

class my_class::impl {  // defined privately here
						// ... all private data and functions: all of these
						//     can now change without recompiling callers ...
public:
	void draw(const my_class& o) {
		std::cout << "drawing my_class instance" << std::endl;
	}
};

my_class::my_class() : pimpl(new impl)
{
	// ... set impl values ...
}
void my_class::draw() { pimpl->draw(*this); }

void Pimpl::Run()
{
	my_class obj;
	obj.draw();
}
