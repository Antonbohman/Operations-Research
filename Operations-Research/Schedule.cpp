#include "Schedule.h"

Schedule::Schedule(const PriorityQueue<Operation>& _queue, const int _amountRooms, const int * timeSpan, const int timeSpanLength)
{
	datatype = DataType::HEAP;
	queue = _queue;
	amountRooms = _amountRooms;
	rooms = new Bin[amountRooms];
	for (int i = 0; i < amountRooms; i++)
	{
		rooms[i].resize(timeSpan[i%timeSpanLength]);
		avaibleTime += timeSpan[i%timeSpanLength];
	}
}

Schedule::Schedule(const List<Operation>& _list, const int _amountRooms, const int * timeSpan, const int timeSpanLength)
{
	datatype = DataType::LIST;
	list = _list;
	amountRooms = _amountRooms;
	rooms = new Bin[amountRooms];
	for (int i = 0; i < amountRooms; i++)
	{
		rooms[i].resize(timeSpan[i%timeSpanLength]);
		avaibleTime += timeSpan[i%timeSpanLength];
	}
}

Schedule::Schedule(const Schedule & origin)
{
	//free
	delete[] rooms;
	//set
	datatype = origin.datatype;
	totalTime = origin.totalTime;
	totalOperation = origin.totalOperation;
	avaibleTime = origin.avaibleTime;
	bookedTime = origin.bookedTime;
	bookedOperation = origin.bookedOperation;
	queue = origin.queue;
	list = origin.list;
	amountRooms = origin.amountRooms;
	rooms = new Bin[amountRooms];
	for (int i = 0; i < amountRooms; i++)
	{
		rooms[i] = Bin(origin.rooms[i]);
	}
}

Schedule::~Schedule() {
	delete[] rooms;
}

void Schedule::fillBins(AlgorithmType type) {
	switch (type) {
		case AlgorithmType::NEXT_FIT:
			nextFit();
			break;
		case AlgorithmType::FIRST_FIT:
			firstFit();
			break;
		case AlgorithmType::BEST_FIT:
			bestFit();
			break;
		case AlgorithmType::NO_FIT:
		default:
			//nothing happends....
			break;
	}
}

void Schedule::printSchedule(const int start, const int end) const {
	if (start >= 0 && end >= 0 && start <= end) {
		int length = 80;
		float scale = 0;

		List<Operation> schedule;

		Bin* rooms = this->rooms + start;

		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hstdout, &csbi);

		for (int i = 0; i < end - start; i++) {
			scale = (1 - ((float)rooms[i].remainingSize() / rooms[i].maxSize())) * length;

			cout << "Room " << (i + 1) << (i+1 > 9 ? "":" ") << " |";
			SetConsoleTextAttribute(hstdout, 0x03);
			for (int x = 0; x < length; x++) {
				cout << (scale > x ? (char)254u : (char)NULL);
			}
			SetConsoleTextAttribute(hstdout, csbi.wAttributes);
			cout << "| " << to_string((int)round((scale/length)*100)) << "% " << intToTime(rooms[i].remainingSize()) << "/" << intToTime(rooms[i].maxSize()) << endl;

			schedule = rooms[i].collectOperations();
			cout << "\t ";
			cout << schedule.getAt(0).getID();
			for (int j = 1; j < schedule.length(); j++) {
				cout << "," << schedule.getAt(j).getID();
			}
			cout << endl;
		}
	}
}

void Schedule::printEffectivity() const {
	int effectiveTime = (int)round(((float)bookedTime / avaibleTime) * 100);
	cout << endl << "Effective Time: " << to_string(effectiveTime) << "% " << intToTime(bookedTime) << "/" << intToTime(avaibleTime) << endl;
	cout << "Remaining Time: " << intToTime(totalTime-bookedTime) << endl << endl;
	cout << "Operations: " << bookedOperation << "/" << totalOperation << " | Remaining: " << totalOperation-bookedOperation << endl << endl;
	cout << "Time to process algorithm: " << to_string(((float)processTime) / CLOCKS_PER_SEC) << "ms" << endl << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;
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
			bookedTime += curr.getTime();
			bookedOperation++;
		}
	}

	processTime = clock() - processTime;
}
