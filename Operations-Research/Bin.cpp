#include "Bin.h"

Bin::Bin(int _size)
{
	size = _size;
}

Bin::Bin(const Bin & origin)
{
	size = origin.size;
	schedule = origin.schedule;
}

Bin::~Bin()
{
}

bool Bin::addOperation(const Operation & op)
{
	schedule.insertAt(schedule.length(),op);
	return true;
}

int Bin::remainingSize()
{
	int output = size;
	for (int i = 0; i < schedule.length(); i++)
	{
		output -= schedule.getAt(i).getTime();
	}
	return output;
}

void Bin::emptyBin()
{
	for (int i = 0; i < schedule.length(); i++)
	{
		schedule.removeAt(0);
	}
}

int Bin::capacity() const
{
	return size;
}

int Bin::length() const
{
	return schedule.length();
}

bool Bin::resize(int _size)
{
	if (_size >= 0) {
		size = _size;
		return true;
	}
	return false;
}

Bin & Bin::operator=(const Bin & origin)
{
	size = origin.size;
	schedule = origin.schedule;
	return *this;
}
