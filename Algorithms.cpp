#include "stdafx.h"
#include "Algorithms.h"

#include <algorithm>
#include <iostream>
#include <vector>

Algorithms::Algorithms()
{
}


Algorithms::~Algorithms()
{
}

class widget
{
public:
	widget(double weight) : m_weight(weight) {}
	double weight() const { return m_weight; }
private:
	double m_weight;
};

void Algorithms::Run()
{
	// Use for_each to act on all items in a collection
	auto print = [](const int& n) { std::cout << " " << n; };

	std::vector<int> nums{ 3, 4, 2, 8, 15, 267 };
	std::for_each(nums.begin(), nums.end(), print);
	std::cout << std::endl;

	// Use transform to process a collection into something else
	// This is similar to IEnumerable<T>.Select()
	std::vector<int> doubles;
	std::transform(nums.begin(), nums.end(), std::back_inserter(doubles), [](const int& n) { return n * n; });
	std::for_each(doubles.begin(), doubles.end(), print);
	std::cout << std::endl;

	// Use find_if as the default search algorithm (note we could just use std::find here)
	auto victory = std::find_if(doubles.begin(), doubles.end(), [](const int& n) {return n == 9;});
	auto defeat = std::find_if(doubles.begin(), doubles.end(), [](const int& n) {return n == 11; });

	// sorted collections can use algorithms like lower_bound
	auto comp = [](const widget& w1, const widget& w2)
	{ 
		return w1.weight() < w2.weight(); 
	};

	std::vector<widget> v{
		widget(7.3),
		widget(2.1),
		widget(12.4),
		widget(13.3)
	};

	std::sort(v.begin(), v.end(), comp);

	// Find the first widget with a weight that is not less than 10.0
	auto i = std::lower_bound(v.begin(), v.end(), widget(10.0), comp);

	// range-base for
	for (const widget& w : v)
	{
		std::cout << "A lovely big widget that weighs " << w.weight() << " kg" << std::endl;
	}
}