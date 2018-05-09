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

	string title;
	DataType datatype;

	int totalTime, totalOperation, bookedTime, bookedOperation;
	clock_t processTime;

	PriorityQueue<Operation> queue;
	List<Operation> list;

	int amountRooms = 0;
	Bin* rooms;

	string intToTime(const int time) const;

	void nextFit();
	void firstFit();
	void bestFit();

public:
	enum AlgorithmType {
		FIRST_FIT,
		NEXT_FIT,
		BEST_FIT
	};

	Schedule();
	Schedule(const PriorityQueue<Operation>& _queue, const int _algorithmType = 0, const int _amountRooms = 0, const int* timeSpan = {}); //ordered operations
	Schedule(const List<Operation>& _list, const int _algorithmType = 0, const int _amountRooms = 0, const int* timeSpan = {}); //unordered operations
	Schedule(const Schedule& origin);
	virtual ~Schedule();

	void setTitle(const string _title);

	void fillBins(AlgorithmType type);

	void printSchedule(const int start, const int end) const;
	void printEffectivity() const;

	Schedule& operator=(const Schedule& origin);
	bool operator==(const Schedule& origin) = delete;
	bool operator!=(const Schedule& origin) = delete;
	bool operator<(const Schedule& origin) = delete;
	bool operator>(const Schedule& origin) = delete;

};