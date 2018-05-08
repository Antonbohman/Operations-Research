#pragma once

#include "List.h"
#include "Operation.h"

using namespace std;

class Bin {
private:
	int size;
	List<Operation> schedule;
public:
	Bin(int _size = 0);
	Bin(const Bin &origin);
	~Bin();

	int capacity() const;
	int length() const;

	Bin& operator=(const Bin& origin);
	bool operator==(const Bin& origin) = delete;
	bool operator!=(const Bin& origin) = delete;
	bool operator<(const Bin& origin) = delete;
	bool operator>(const Bin& origin) = delete;
};