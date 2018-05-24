#pragma once

#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <chrono>
#include <math.h>

#include "Bin.h"
#include "PriorityQueue.h"

//Microsecond per second
#define MICRO_PER_SEC ((clock_t)1000000)

class Schedule {
private:
	enum DataType {
		NO_TYPE,
		HEAP,
		LIST
	};

	DataType datatype;

	int totalTime, totalOperation, avaibleTime, bookedTime, bookedOperation;
	clock_t processTime;

	PriorityQueue<Operation> queue;
	List<Operation> list;

	int amountRooms;
	Bin* rooms;

	string intToTime(const int time) const;

	void nextFit();
	void firstFit();
	void bestFit();

public:
	enum AlgorithmType {
		NO_FIT,
		FIRST_FIT,
		NEXT_FIT,
		BEST_FIT
	};

	Schedule();
	Schedule(const PriorityQueue<Operation>& _queue, const int _amountRooms = 0, const int* timeSpan = { 0 }, const int timeSpanLength = 1); //ordered operations
	Schedule(const List<Operation>& _list, const int _amountRooms = 0, const int* timeSpan = { 0 }, const int timeSpanLength = 1); //unordered operations
	Schedule(const Schedule& origin);
	virtual ~Schedule();

	void fillBins(AlgorithmType type);

	void printSchedule(const int start, const int end) const;
	void printEffectivity() const;
	float getEffectivity();

	Schedule& operator=(const Schedule& origin);
	bool operator==(const Schedule& origin);
	bool operator!=(const Schedule& origin);
	bool operator<(const Schedule& origin);
	bool operator>(const Schedule& origin);

};