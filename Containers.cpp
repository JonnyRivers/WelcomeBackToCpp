#include "stdafx.h"
#include "Containers.h"

#include <array>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

Containers::Containers()
{
}


Containers::~Containers()
{
}

void Containers::Run()
{
	// By default, use vector as the preferred sequential container in C++. 
	// This is equivalent to List<T> in .NET languages.
	std::vector<std::string> apples;
	apples.push_back("Granny Smith");

	// Use map (not unordered_map) as the default associative container.
	// Use set, multimap, and multiset for degenerate & multi cases.
	std::map<std::string, std::string> apple_color;
	apple_color["Granny Smith"] = "Green";

	// When performance optimization is needed, consider using the following:
	/////////////////////////////////////////////////////////////////////////

	// The array type when embedding is important, for example, as a class member.
	std::array<std::string, 3> arr{ "apple", "banana", "cherry" };

	// Unordered associative containers such as unordered_map. 
	// These have lower per-element overhead and constant-time lookup, but they can be harder to use correctly and efficiently.
	std::unordered_map<std::string, std::string> capitalsByCountry
	{
		{"UK", "London"},
		{"France", "Paris"}
	};

	// A sorted vector<> so that algorithms that work on sorted collections can be utilized
}