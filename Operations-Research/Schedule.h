#pragma once

#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>

#include "Bin.h"
#include "PriorityQueue.h"

class Schedule {
private:
	enum DataType {
		HEAP,
		LIST
	};

	DataType datatype;

	int totalTime, totalOperation, bookedTime, bookedOperation;
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

	Schedule(const PriorityQueue<Operation>& _queue, const int _amountRooms = 0, const int* timeSpan = { 0 }, const int timeSpanLength = 1); //ordered operations
	Schedule(const List<Operation>& _list, const int _amountRooms = 0, const int* timeSpan = { 0 }, const int timeSpanLength = 1); //unordered operations
	Schedule(const Schedule& origin) = delete;
	virtual ~Schedule();

	void fillBins(AlgorithmType type);

	void printSchedule(const int start, const int end) const;
	void printEffectivity() const;

	Schedule& operator=(const Schedule& origin) = delete;
	bool operator==(const Schedule& origin) = delete;
	bool operator!=(const Schedule& origin) = delete;
	bool operator<(const Schedule& origin) = delete;
	bool operator>(const Schedule& origin) = delete;

};