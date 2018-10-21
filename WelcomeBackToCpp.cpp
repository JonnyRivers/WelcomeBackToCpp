// WelcomeBackToCpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TypeSystem.h"
#include "UniformInitialization.h"
#include "ObjectLifetime.h"
#include "RAII.h"
#include "SmartPointers.h"

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

    return 0;
}

