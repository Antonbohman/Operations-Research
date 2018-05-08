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

	void setID(int _id);
	void setType(string _type);
	void setTime(int _time);

	int getID();
	string getType();
	int getTime();

	Bin& operator=(const Bin& origin);
	Bin& operator==(const Bin& origin);
	Bin& operator<(const Bin& origin);
	Bin& operator>(const Bin& origin);
};