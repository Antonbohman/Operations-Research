#include "Operation.h"

Operation::Operation(const int _id, const string _type, const int _time) {
	id = _id;
	type = _type;
	time = _time;
}

Operation::Operation(const Operation & origin) {
	id = origin.id;
	type = origin.type;
	time = origin.time;
}

Operation::~Operation() {
}

void Operation::setID(const int _id) {
	id = _id;
}

void Operation::setType(const string _type) {
	type = _type;
}

void Operation::setTime(const int _time) {
	time = _time;
}

int Operation::getID() const {
	return id;
}

string Operation::getType() const {
	return type;
}

int Operation::getTime() const {
	return time;
}

Operation & Operation::operator=(const Operation & origin) {
	if (this != &origin) {
		id = origin.id;
		type = origin.type;
		time = origin.time;
	}

	return *this;
}

bool Operation::operator==(const Operation & origin) const {
	return (id == origin.id && type == origin.type && time == origin.time);
}

bool Operation::operator<(const Operation & origin) const {
	return time < origin.time;
}

bool Operation::operator>(const Operation & origin) const {
	return time > origin.time;
}

