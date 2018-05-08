#include "Bin.h"

Bin::Bin(const int _size) {
	size = _size;
}

Bin::Bin(const Bin & origin) {
	size = origin.size;
	schedule = origin.schedule;
}

Bin::~Bin() {
}

bool Bin::addOperation(const Operation & op) {
	bool added = false;

	if (remainingSize() >= op.getTime()) {
		schedule.insertAt(schedule.length(), op);
		added = true;
	}

	return added;
}

int Bin::remainingSize() const {
	int output = size;

	for (int i = 0; i < schedule.length(); i++) {
		output -= schedule.getAt(i).getTime();
	}

	return output;
}

int Bin::maxSize() const {
	return size;
}

void Bin::emptyBin() {
	for (int i = 0; i < schedule.length(); i++) {
		schedule.removeAt(0);
	}
}

bool Bin::resize(const int _size) {
	bool resized = false;
	int changeInSize = 0;

	if (_size >= 0) {
		changeInSize = size - _size;

		if (changeInSize <= remainingSize()) {
			size = _size;
			resized =  true;
		}
	}

	return resized;
}

Bin & Bin::operator=(const Bin & origin) {
	size = origin.size;
	schedule = origin.schedule;
	return *this;
}
