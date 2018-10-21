#include "stdafx.h"
#include "ObjectLifetime.h"

#include <memory>
#include <string>

ObjectLifetime::ObjectLifetime()
{
}


ObjectLifetime::~ObjectLifetime()
{
}

void ObjectLifetime::Run()
{
	std::unique_ptr<std::string>(new std::string("Hello"));
}
