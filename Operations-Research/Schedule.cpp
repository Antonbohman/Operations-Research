#include "Schedule.h"

Schedule::Schedule() {

}

Schedule::Schedule(const PriorityQueue<Operation>& _queue, const int _algorithmType, const int _amountRooms, const int* timeSpan) {
}

Schedule::Schedule(const List<Operation>& _list, const int _algorithmType, const int _amountRooms, const int* timeSpan) {
}

Schedule::Schedule(const Schedule & origin) {
}

Schedule::~Schedule() {

}

void Schedule::setTitle(const string _title) 
{
	title = _title;
}

void Schedule::fillBins(AlgorithmType type)
{
}

void Schedule::printSchedule(const int amountRooms, const Bin * rooms) {
}

void Schedule::printEffectivity(const int totalTime, const int totalOperation, const int & bookedTime, const int bookedOperation, const clock_t processTime) {
}

Schedule & Schedule::operator=(const Schedule & origin) {
	// TODO: insert return statement here
}

string Schedule::intToTime(const int time) {
	string hour = to_string(time / 60);
	if (hour.length() == 1)
		hour = "0" + hour;

	string min = to_string(time % 60);
	if (min.length() == 1)
		min = "0" + min;

	return hour + "h" + min + "m";
}

void Schedule::nextFit()
{
	Operation curr;

	int currentRoom = 0;

	totalTime = 0;
	totalOperation = 0;
	bookedTime = 0;
	bookedOperation = 0;

	processTime = clock();
	int index = 0;
	int length = list.length();
	while ((datatype == DataType::HEAP ? !queue.isEmpty() : index < length)) {
		curr = (datatype == DataType::HEAP ? queue.dequeue() : list.getAt(index++));
		totalTime += curr.getTime();
		totalOperation++;
		for (int i = currentRoom; i < amountRooms; i++) {
			currentRoom = i;
			if (rooms[i].addOperation(curr)) {
				i = amountRooms;	//break
				bookedTime += curr.getTime();
				bookedOperation++;
			}
		}
	}
	processTime = clock() - processTime;
}

void Schedule::firstFit()
{
	Operation curr;

	totalTime = 0;
	totalOperation = 0;
	bookedTime = 0;
	bookedOperation = 0;

	processTime = clock();
	int index = 0;
	int length = list.length();
	while ((datatype == DataType::HEAP ? !queue.isEmpty() : index < length)) {
		curr = (datatype == DataType::HEAP ? queue.dequeue() : list.getAt(index++));
		totalTime += curr.getTime();
		totalOperation++;
		for (int i = 0; i < amountRooms; i++) {
			if (rooms[i].addOperation(curr)) {
				i = amountRooms;	//break
				bookedTime += curr.getTime();
				bookedOperation++;
			}
		}
	}
	processTime = clock() - processTime;
}

void Schedule::bestFit()
{
	Operation curr;

	totalTime = 0;
	totalOperation = 0;
	bookedTime = 0;
	bookedOperation = 0;

	processTime = clock();
	//best fit decreasing
	int index = 0;
	int length = list.length();
	while ((datatype == DataType::HEAP ? !queue.isEmpty() : index < length)) {
		curr = (datatype == DataType::HEAP ? queue.dequeue() : list.getAt(index++));
		totalTime += curr.getTime();
		totalOperation++;

		int minIndex = -1;
		int minValue = INT_MAX;
		for (int i = 0; i < amountRooms; i++) {
			if (rooms[i].remainingSize() - curr.getTime() < minValue && rooms[i].remainingSize() - curr.getTime() >= 0) {
				minIndex = i;
			}
		}
		if (minIndex != -1) {
			rooms[minIndex].addOperation(curr);
			bookedOperation++;
		}
	}

	processTime = clock() - processTime;
}
