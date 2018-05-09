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

void Schedule::printSchedule(const int start, const int end) const {
	if (start >= 0 && end >= 0 && start <= end) {
		int length = 40;

		Bin* rooms = this->rooms + start;

		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hstdout, &csbi);

		for (int i = 0; i < end - start; i++) {
			int scale = (1 - ((float)rooms[i].remainingSize() / rooms[i].maxSize())) * length;

			cout << "Room " << i + 1 << " |";
			SetConsoleTextAttribute(hstdout, 0x03);
			for (int x = 0; x < length; x++) {
				cout << (scale > x ? (char)254u : (char)NULL);
			}
			SetConsoleTextAttribute(hstdout, csbi.wAttributes);
			cout << "| " << intToTime(rooms[i].remainingSize()) << "/" << intToTime(rooms[i].maxSize()) << endl;
		}
	}
}

void Schedule::printEffectivity() const {
	cout << endl << "Effective Time: " << intToTime(bookedTime) << "/" << intToTime(totalTime) << endl;
	cout << "Operations: " << bookedOperation << "/" << totalOperation << endl << endl;
	cout << "Time to process algorithm: " << to_string(((float)processTime) / CLOCKS_PER_SEC) << "ms" << endl << endl;
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;
}

Schedule & Schedule::operator=(const Schedule & origin) {
	// TODO: insert return statement here
}

string Schedule::intToTime(const int time) const {
	string hour = to_string(time / 60);
	if (hour.length() == 1)
		hour = "0" + hour;

	string min = to_string(time % 60);
	if (min.length() == 1)
		min = "0" + min;

	return hour + "h" + min + "m";
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
