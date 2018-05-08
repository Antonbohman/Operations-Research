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

int Bin::capacity() const
{
	return size;
}

int Bin::length() const
{
	return schedule.length();
}

Bin & Bin::operator=(const Bin & origin)
{
	size = origin.size;
	schedule = origin.schedule;
	return *this;
}
