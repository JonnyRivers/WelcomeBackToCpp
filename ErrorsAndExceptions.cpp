#include "stdafx.h"
#include "ErrorsAndExceptions.h"

#include <stdexcept>
#include <limits>
#include <iostream>

ErrorsAndExceptions::ErrorsAndExceptions()
{
}


ErrorsAndExceptions::~ErrorsAndExceptions()
{
}

void MyFunc(int c)
{
	if (c > std::numeric_limits<char>::max())
		throw std::invalid_argument("MyFunc argument too large.");
	//...
}

int ErrorsAndExceptions::Run()
{
	try
	{
		MyFunc(256); //cause an exception to throw
	}

	catch (std::invalid_argument& e)
	{
		std::cerr << e.what() << std::endl;
		return -1;
	}
	//...
	return 0;
}