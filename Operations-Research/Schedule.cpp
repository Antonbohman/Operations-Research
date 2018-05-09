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

void Schedule::setTitle(const string _title) {
}

void Schedule::printSchedule(const int amountRooms, const Bin * rooms) {
}

void Schedule::printEffectivity(const int totalTime, const int totalOperation, const int & bookedTime, const int bookedOperation, const clock_t processTime) {
}

Schedule & Schedule::operator=(const Schedule & origin) {
	// TODO: insert return statement here
}

string Schedule::intToTime(const int time) {
	return string();
}

void Schedule::nextFit(PriorityQueue<Operation>& queue, const int amountRooms, Bin * rooms, int & totalTime, int & totalOperation, int & bookedTime, int & bookedOperation, clock_t & processTime) {
}

void Schedule::nextFit(List<Operation>& list, const int amountRooms, Bin * rooms, int & totalTime, int & totalOperation, int & bookedTime, int & bookedOperation, clock_t & processTime) {
}

void Schedule::firstFit(PriorityQueue<Operation>& queue, const int amountRooms, Bin * rooms, int & totalTime, int & totalOperation, int & bookedTime, int & bookedOperation, clock_t & processTime) {
}

void Schedule::firstFit(List<Operation>& list, const int amountRooms, Bin * rooms, int & totalTime, int & totalOperation, int & bookedTime, int & bookedOperation, clock_t & processTime) {
}

void Schedule::bestFit(PriorityQueue<Operation>& queue, const int amountRooms, Bin * rooms, int & totalTime, int & totalOperation, int & bookedTime, int & bookedOperation, clock_t & processTime) {
}

void Schedule::bestFit(List<Operation>& list, const int amountRooms, Bin * rooms, int & totalTime, int & totalOperation, int & bookedTime, int & bookedOperation, clock_t & processTime) {
}
