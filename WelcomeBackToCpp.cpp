// WelcomeBackToCpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TypeSystem.h"
#include "UniformInitialization.h"
#include "ObjectLifetime.h"

int main()
{
	TypeSystem typeSystem;
	typeSystem.Run();

	UniformInitialization uniformInitialization;
	uniformInitialization.Run();

	ObjectLifetime objectLifetime;
	objectLifetime.Run();

    return 0;
}

