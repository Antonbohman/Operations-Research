#include "Operation.h"

Operation::Operation(int _id, string _type, int _time)
{
	id = _id;
	type = _type;
	time = _time;
}

Operation::Operation(const Operation & origin)
{
	id = origin.id;
	type = origin.type;
	time = origin.time;
}

Operation::~Operation()
{
}

void Operation::setID(int _id)
{
	id = _id;
}

void Operation::setType(string _type)
{
	type = _type;
}

void Operation::setTime(int _time)
{
	time = _time;
}

int Operation::getID()
{
	return id;
}

string Operation::getType()
{
	return type;
}

int Operation::getTime()
{
	return time;
}

Operation & Operation::operator=(const Operation & origin)
{
	id = origin.id;
	type = origin.type;
	time = origin.time;
	
	return *this;
}

bool Operation::operator==(const Operation & origin)
{
	return (id == origin.id && type == origin.type && time == origin.time);
}

bool Operation::operator<(const Operation & origin)
{
	return time < origin.time;
}

bool Operation::operator>(const Operation & origin)
{
	return time > origin.time;
}

