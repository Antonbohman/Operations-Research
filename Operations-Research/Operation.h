#pragma once

#include <string>

using namespace std;

class Operation {
private:
	int id;
	string type;
	int time;
public:
	Operation(const int _id = -1, const string _type = "NULL", const int _time = 0);
	Operation(const Operation& origin);
	~Operation();

	void setID(const int _id);
	void setType(const string _type);
	void setTime(const int _time);

	int getID() const;
	string getType() const;
	int getTime() const;

	Operation& operator=(const Operation& origin);
	bool operator==(const Operation& origin) const;
	bool operator<(const Operation& origin) const;
	bool operator>(const Operation& origin) const;
};