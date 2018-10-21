#pragma once

#include <memory>

class Pimpl
{
public:
	Pimpl();
	~Pimpl();

	void Run();
};

class my_class {
public:
	my_class();
	void draw();
private:
	class impl;
	std::unique_ptr<impl> pimpl;
};