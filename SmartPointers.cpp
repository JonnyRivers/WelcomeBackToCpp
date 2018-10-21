#include "stdafx.h"
#include "SmartPointers.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

SmartPointers::SmartPointers()
{
}


SmartPointers::~SmartPointers()
{
}

class Song
{
public:
	Song(const std::wstring& a, const std::wstring& t) : artist(a), title(t) {}

	std::wstring artist;
	std::wstring title;
};

std::unique_ptr<Song> SongFactory(const std::wstring& artist, const std::wstring& title)
{
	// Implicit move operation into the variable that stores the result.
	return std::make_unique<Song>(artist, title);
}

void MakeSongs()
{
	// Create a new unique_ptr with a new object.
	auto song = std::make_unique<Song>(L"Mr. Children", L"Namonaki Uta");

	// Use the unique_ptr.
	std::vector<std::wstring> titles = { song->title };

	// Move raw pointer from one unique_ptr to another.
	std::unique_ptr<Song> song2 = std::move(song);

	// Obtain unique_ptr from function that returns by value.
	auto song3 = SongFactory(L"Michael Jackson", L"Beat It");
}

void SongVector()
{
	std::vector<std::unique_ptr<Song>> songs;

	// Create a few new unique_ptr<Song> instances
	// and add them to vector using implicit move semantics.
	songs.push_back(std::make_unique<Song>(L"B'z", L"Juice"));
	songs.push_back(std::make_unique<Song>(L"Namie Amuro", L"Funky Town"));
	songs.push_back(std::make_unique<Song>(L"Kome Kome Club", L"Kimi ga Iru Dake de"));
	songs.push_back(std::make_unique<Song>(L"Ayumi Hamasaki", L"Poker Face"));

	// Pass by const reference when possible to avoid copying.
	for (const auto& song : songs)
	{
		std::wcout << L"Artist: " << song->artist << L"   Title: " << song->title << std::endl;
	}
}

void UniquePtr()
{
	MakeSongs();
	SongVector();
}

void SharedPtr()
{
	// Use make_shared function when possible.
	auto sp1 = std::make_shared<Song>(L"The Beatles", L"Im Happy Just to Dance With You");

	// Ok, but slightly less efficient. 
	// Note: Using new expression as constructor argument
	// creates no named variable for other code to access.
	std::shared_ptr<Song> sp2(new Song(L"Lady Gaga", L"Just Dance"));

	// When initialization must be separate from declaration, e.g. class members, 
	// initialize with nullptr to make your programming intent explicit.
	std::shared_ptr<Song> sp5(nullptr);
	//Equivalent to: shared_ptr<Song> sp5;
	//...
	sp5 = std::make_shared<Song>(L"Elton John", L"I'm Still Standing");

	//Initialize with copy constructor. Increments ref count.
	auto sp3(sp2);

	//Initialize via assignment. Increments ref count.
	auto sp4 = sp2;

	//Initialize with nullptr. sp7 is empty.
	std::shared_ptr<Song> sp7(nullptr);

	// Initialize with another shared_ptr. sp1 and sp2
	// swap pointers as well as ref counts.
	sp1.swap(sp2);

	std::vector<std::shared_ptr<Song>> v{
		std::make_shared<Song>(L"Bob Dylan", L"The Times They Are A Changing"),
		std::make_shared<Song>(L"Aretha Franklin", L"Bridge Over Troubled Water"),
		std::make_shared<Song>(L"Thala", L"Entre El Mar y Una Estrella")
	};

	std::vector<std::shared_ptr<Song>> v2;
	std::remove_copy_if(v.begin(), v.end(), std::back_inserter(v2), [](std::shared_ptr<Song> s)
	{
		return s->artist.compare(L"Bob Dylan") == 0;
	});

	for (const auto& s : v2)
	{
		std::wcout << s->artist << L":" << s->title << std::endl;
	}

	// We can hang on to things that were in a collection
	std::vector<std::shared_ptr<Song>> v3{
		std::make_shared<Song>(L"Aretha Franklin", L"Bridge Over Troubled Water"),
		std::make_shared<Song>(L"Thala", L"Entre El Mar y Una Estrella")
	};
	std::shared_ptr<Song> bridge = v3[0];
	v3.clear();
	std::wcout << bridge->artist << L":" << bridge->title << std::endl;

	// Initialize two separate raw pointers.
	// Note that they contain the same values.
	auto song1 = new Song(L"Village People", L"YMCA");
	auto song2 = new Song(L"Village People", L"YMCA");

	// Create two unrelated shared_ptrs.
	std::shared_ptr<Song> p1(song1);
	std::shared_ptr<Song> p2(song2);

	// Unrelated shared_ptrs are never equal.
	std::wcout << "p1 < p2 = " << std::boolalpha << (p1 < p2) << std::endl;
	std::wcout << "p1 == p2 = " << std::boolalpha << (p1 == p2) << std::endl;

	// Related shared_ptr instances are always equal.
	std::shared_ptr<Song> p3(p2);
	std::wcout << "p3 == p2 = " << std::boolalpha << (p3 == p2) << std::endl;
}

class Controller
{
public:
	int Num;
	std::wstring Status;
	std::vector<std::weak_ptr<Controller>> others;
	explicit Controller(int i) : Num(i), Status(L"On")
	{
		std::wcout << L"Creating Controller" << Num << std::endl;
	}

	~Controller()
	{
		std::wcout << L"Destroying Controller" << Num << std::endl;
	}

	// Demonstrates how to test whether the  
	// pointed-to memory still exists or not. 
	void CheckStatuses() const
	{
		for_each(others.begin(), others.end(), [](std::weak_ptr<Controller> wp)
		{
			try
			{
				auto p = wp.lock();
				if (p != nullptr)
				{
					std::wcout << L"Status of " << p->Num << " = " << p->Status << std::endl;
				}
				else
				{
					std::wcout << L"Null object" << std::endl;
				}
			}
			catch (std::bad_weak_ptr b)
			{
				std::wcout << L"Null object" << std::endl;
			}
		});
	}
};

void WeakPtr()
{
	std::vector<std::shared_ptr<Controller>> v{
		std::make_shared<Controller>(0),
		std::make_shared<Controller>(1),
		std::make_shared<Controller>(2),
		std::make_shared<Controller>(3),
		std::make_shared<Controller>(4),
	};

	// Each controller depends on all others not being deleted. 
	// Give each controller a pointer to all the others. 
	for (size_t i = 0; i < v.size(); ++i)
	{
		for_each(v.begin(), v.end(), [&v, i](std::shared_ptr<Controller> p)
		{
			if (p->Num != i)
			{
				v[i]->others.push_back(std::weak_ptr<Controller>(p));
				std::wcout << L"push_back to v[" << i << "]: " << p->Num << std::endl;
			}
		});
	}

	for_each(v.begin(), v.end(), [](std::shared_ptr<Controller>& p)
	{
		std::wcout << L"use_count = " << p.use_count() << std::endl;
		p->CheckStatuses();
	});

	v.pop_back();

	for_each(v.begin(), v.end(), [](std::shared_ptr<Controller>& p)
	{
		std::wcout << L"use_count = " << p.use_count() << std::endl;
		p->CheckStatuses();
	});
}

void SmartPointers::Run()
{
	// unique_ptr
	UniquePtr();
	
	// shared_ptr
	// Reference counted pointer type
	SharedPtr();

	// weak_ptr
	WeakPtr();
}