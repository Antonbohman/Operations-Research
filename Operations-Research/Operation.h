#pragma once

#include <string>

using namespace std;

class Operation {
private:
	int id;
	string type;
	int time;
public:
	Operation(int _id = -1, string _type = "NULL", int _time = 0);
	Operation(const Operation &origin);
	~Operation();

	void setID(int _id);
	void setType(string _type);
	void setTime(int _time);

	int getID();
	string getType();
	int getTime();

	Operation& operator=(const Operation& origin);
	bool operator==(const Operation& origin);
	bool operator<(const Operation& origin);
	bool operator>(const Operation& origin);
};