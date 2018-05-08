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

	bool addOperation(const Operation& op); //push operation to last place in list
	int remainingSize(); //return size - all operation times schedules
	void emptyBin(); //empty list
	bool resize(int _size); //change size of bin, return true or false if possible when decreasing size 

	Bin& operator=(const Bin& origin);
	bool operator==(const Bin& origin) = delete;
	bool operator!=(const Bin& origin) = delete;
	bool operator<(const Bin& origin) = delete;
	bool operator>(const Bin& origin) = delete;
};