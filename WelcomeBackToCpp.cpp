// WelcomeBackToCpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TypeSystem.h"
#include "UniformInitialization.h"
#include "ObjectLifetime.h"
#include "RAII.h"
#include "SmartPointers.h"
#include "Pimpl.h"
#include "Containers.h"
#include "Algorithms.h"
#include "StringsAndIO.h"
#include "ErrorsAndExceptions.h"
#include "LINQ.h"
#include "DateTime.h"

int main()
{
	TypeSystem typeSystem;
	typeSystem.Run();

	UniformInitialization uniformInitialization;
	uniformInitialization.Run();

	ObjectLifetime objectLifetime;
	objectLifetime.Run();

	RAII raii;
	raii.Run();

	SmartPointers smartPointers;
	smartPointers.Run();

	Pimpl pimpl;
	pimpl.Run();

	Containers containers;
	containers.Run();

	Algorithms algorithms;
	algorithms.Run();

	StringsAndIO stringsAndIO;
	stringsAndIO.Run();

	ErrorsAndExceptions errorsAndExceptions;
	errorsAndExceptions.Run();

	LINQ linq;
	linq.Run();

	DateTime dateTime;
	dateTime.Run();

    return 0;
}

