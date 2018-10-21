#include "stdafx.h"
#include "StringsAndIO.h"

#include <iostream>
#include <iomanip>

StringsAndIO::StringsAndIO()
{
}


StringsAndIO::~StringsAndIO()
{
}

void StringsAndIO::Run()
{
	std::ios state(nullptr);

	std::cout << "The answer in decimal is: " << 42 << std::endl;

	state.copyfmt(std::cout); // save current formatting
	std::cout << "In hex: 0x" // now load up a bunch of formatting modifiers
		<< std::hex
		<< std::uppercase
		<< std::setw(8)
		<< std::setfill('0')
		<< 42            // the actual value we wanted to print out
		<< std::endl;
	std::cout.copyfmt(state); // restore previous formatting
}