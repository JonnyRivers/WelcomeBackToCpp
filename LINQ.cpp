#include "stdafx.h"
#include "LINQ.h"

#include <algorithm>
#include <numeric>
#include <vector>

LINQ::LINQ()
{
}


LINQ::~LINQ()
{
}

void Select()// -> transform
{
	// var numbers = new List<int>() { 1, 2, 3, 4, 5 };
	// var squares = numbers.Select(n => n * n);

	std::vector<int> numbers{ 1, 2, 3, 4, 5 };
	std::vector<int> squares;
	std::transform(numbers.begin(), numbers.end(), std::back_inserter(squares), [](int n) { return n * n; });
}

void Where()// -> copy_if
{
	// var numbers = new List<int>() { 1, 2, 3, 4, 5 };
	// var oddNumbers = numbers.Where(n => n%2 == 1);

	std::vector<int> numbers{ 1, 2, 3, 4, 5 };
	std::vector<int> oddNumbers;
	std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(oddNumbers), [](int n) { return n%2 == 1; });
}

void FirstOrDefault()// -> find_if
{
	// var numbers = new List<int>() { 1, 2, 3, 4, 5 };
	// int firstDivisibleByFour = numbers.FirstOrDefault(n => n%4 == 0);

	std::vector<int> numbers{ 1, 2, 3, 4, 5 };
	auto firstDivisibleByFourIter = std::find_if(numbers.begin(), numbers.end(), [](int n) { return n % 4 == 0; });
}

template<class _InIt, class _Pr>
_InIt single_or_default_impl(_InIt _First, const _InIt _Last, _Pr _Pred)
{
	auto firstMatch = std::find_if(_First, _Last, _Pred);
	if (firstMatch == _Last)
	{
		return _Last;
	}

	auto secondMatch = std::find_if(firstMatch + 1, _Last, _Pred);
	if (secondMatch != _Last)
	{
		return _Last;
	}

	return firstMatch;
}

void SingleOrDefault()// -> no natural fit
{
	// var numbers = new List<int>() { 1, 2, 3, 4, 5 };
	// int largeNumber = numbers.SingleOrDefault(n => n > 4);

	std::vector<int> numbers{ 1, 2, 3, 4, 5 };
	auto pred = [](int n) { return n > 4; };
	auto singleIter = single_or_default_impl(numbers.begin(), numbers.end(), pred);
}

void Sum()// -> accumulate
{
	// var numbers = new List<int>() { 1, 2, 3, 4, 5 };
	// int sum = numbers.Sum();

	std::vector<int> numbers{ 1, 2, 3, 4, 5 };
	int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
}

void Count()// -> count_if
{
	// var numbers = new List<int>() { 1, 2, 3, 4, 5 };
	// var numOddNumbers = numbers.Count(n => n%2 == 1);

	std::vector<int> numbers{ 1, 2, 3, 4, 5 };
	int numOddNumbers = std::count_if(numbers.begin(), numbers.end(), [](int n) { return n % 2 == 1; });
}

void Any()// -> any_of
{
	// var numbers = new List<int>() { 1, 2, 3, 4, 5 };
	// bool anyOddNumbers = numbers.Any(n => n%2 == 1);

	std::vector<int> numbers{ 1, 2, 3, 4, 5 };
	bool anyOddNumbers = std::any_of(numbers.begin(), numbers.end(), [](int n) { return n % 2 == 1; });
}

void All()// -> all_of
{
	// var numbers = new List<int>() { 1, 2, 3, 4, 5 };
	// bool allOddNumbers = numbers.All(n => n%2 == 1);

	std::vector<int> numbers{ 1, 2, 3, 4, 5 };
	bool allOddNumbers = std::all_of(numbers.begin(), numbers.end(), [](int n) { return n % 2 == 1; });
}

void LINQ::Run()
{
	Select();
	Where();
	FirstOrDefault();
	SingleOrDefault();
	Sum();
	Count();
	Any();
	All();
}