#pragma once

#include "List.h"
#include "Operation.h"

using namespace std;

class Bin {
private:
	int size;
	List<Operation> schedule;
public:
	Bin(const int _size = 0);
	Bin(const Bin& origin);
	~Bin();

	bool addOperation(const Operation& op);
	int remainingSize() const;
	int maxSize() const;
	void empty();
	bool resize(const int _size);

	Bin& operator=(const Bin& origin);
	bool operator==(const Bin& origin) = delete;
	bool operator!=(const Bin& origin) = delete;
	bool operator<(const Bin& origin) = delete;
	bool operator>(const Bin& origin) = delete;
};