#pragma once

#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>

#include "Bin.h"
#include "PriorityQueue.h"

class Schedule {
private:
	string title;
	int algorithmType;
	int containerType;

	int totalTime, totalOperation, bookedTime, bookedOperation;
	clock_t processTime;

	PriorityQueue<Operation> queue;
	List<Operation> list;

	int amountRooms = 0;
	Bin* rooms;

	string intToTime(const int time) const;

	void nextFit(PriorityQueue<Operation>& queue, const int amountRooms, Bin* rooms, int& totalTime, int& totalOperation, int& bookedTime, int& bookedOperation, clock_t& processTime);
	void nextFit(List<Operation>& list, const int amountRooms, Bin* rooms, int& totalTime, int& totalOperation, int& bookedTime, int& bookedOperation, clock_t& processTime);
	void firstFit(PriorityQueue<Operation>& queue, const int amountRooms, Bin* rooms, int& totalTime, int& totalOperation, int& bookedTime, int& bookedOperation, clock_t& processTime);
	void firstFit(List<Operation>& list, const int amountRooms, Bin* rooms, int& totalTime, int& totalOperation, int& bookedTime, int& bookedOperation, clock_t& processTime);
	void bestFit(PriorityQueue<Operation>& queue, const int amountRooms, Bin* rooms, int& totalTime, int& totalOperation, int& bookedTime, int& bookedOperation, clock_t& processTime);
	void bestFit(List<Operation>& list, const int amountRooms, Bin* rooms, int& totalTime, int& totalOperation, int& bookedTime, int& bookedOperation, clock_t& processTime);

public:
	static const int FIRST_FIT = 1;
	static const int NEXT_FIT = 2;
	static const int BEST_FIT = 3;

	Schedule();
	Schedule(const PriorityQueue<Operation>& _queue, const int _algorithmType = 0, const int _amountRooms = 0, const int* timeSpan = {}); //ordered operations
	Schedule(const List<Operation>& _list, const int _algorithmType = 0, const int _amountRooms = 0, const int* timeSpan = {}); //unordered operations
	Schedule(const Schedule& origin);
	virtual ~Schedule();

	void setTitle(const string _title);

	void printSchedule(const int start, const int end) const;
	void printEffectivity() const;

	Schedule& operator=(const Schedule& origin);
	bool operator==(const Schedule& origin) = delete;
	bool operator!=(const Schedule& origin) = delete;
	bool operator<(const Schedule& origin) = delete;
	bool operator>(const Schedule& origin) = delete;

};