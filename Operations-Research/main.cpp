#include <iostream>
#include <string>
#include <fstream>

#include "PriorityQueue.h"
#include "List.h"
#include "Schedule.h"

using namespace std;

void emptyPriorityQueue(PriorityQueue<Operation>* que);
void emptyList(List<Operation>* list);

bool readFromFile(const string filename, PriorityQueue<Operation>* que);
bool readFromFile(const string filename, List<Operation>* list);

Schedule makeSingleSchedule(const PriorityQueue<Operation>* que, const int heapType, const Schedule::AlgorithmType fitType,
							const int amountRooms, const int* timeSpan, const int timeSpanLength,
							int& testNr, const string fileName);

Schedule makeSingleSchedule(const List<Operation>* list, const Schedule::AlgorithmType fitType,
							const int amountRooms, const int* timeSpan, const int timeSpanLength,
							int& testNr, const string fileName);

Schedule makeDoubleSchedule(const PriorityQueue<Operation>* que, const int heapType, const Schedule::AlgorithmType fitType,
							const int amountRooms, const int* timeSpan, const int timeSpanLength,
							int& testNr, const string fileName);

Schedule makeDoubleSchedule(const List<Operation>* list, const Schedule::AlgorithmType fitType,
							const int amountRooms, const int* timeSpan, const int timeSpanLength,
							int& testNr, const string fileName);

/*
*  main: Starting point
*/
int main() {
	PriorityQueue<Operation> max_queue(MAX_HEAP);
	PriorityQueue<Operation> min_queue(MIN_HEAP);
	List<Operation> list;

	int singleDay[1] = { 60 * 11 };	//
	int doubleDay[3] = { 60 * 11, 60 * 14, 60 * 9 };

	int testNr = 1;
	string fileName = "";

	Schedule currSchedule;
	Schedule storedSchedule;

	int option;

	//create input option
	cout << "Select an option:" << endl;
	cout << "1: Find best schedule example." << endl;
	cout << "2: Nine methods on a single day schedule." << endl;
	cout << "3: Nine methods on a single day schedule but with a greater amount of operations." << endl;
	cout << "4: Same methods but on different operations." << endl;
	cout << "5: Two days schedule split on same operations" << endl;
	cout << "6: High amount of data on many rooms." << endl;
	cout << "Input: ";

	cin >> option;

	switch (option) {
		case 1:
			fileName = "Operationer_1a.txt";

			if (readFromFile(fileName, &max_queue) &&
				readFromFile(fileName, &min_queue) &&
				readFromFile(fileName, &list)) {

				//NEXT FIT
				currSchedule = makeSingleSchedule(&min_queue, MIN_HEAP, Schedule::NEXT_FIT, 3, singleDay, 1, testNr, fileName);
				if (currSchedule > storedSchedule)
					storedSchedule = currSchedule;

				currSchedule = makeSingleSchedule(&max_queue, MAX_HEAP, Schedule::NEXT_FIT, 3, singleDay, 1, testNr, fileName);
				if (currSchedule > storedSchedule)
					storedSchedule = currSchedule;

				currSchedule = makeSingleSchedule(&list, Schedule::NEXT_FIT, 3, singleDay, 1, testNr, fileName);
				if (currSchedule > storedSchedule)
					storedSchedule = currSchedule;

				cout << "\t\t\t\tThe most effective schedule:" << endl << endl;

				storedSchedule.printSchedule(0, 3);
				storedSchedule.printEffectivity();
			}
			break;
		case 2:
			fileName = "Operationer_1a.txt";

			if (readFromFile(fileName, &max_queue) &&
				readFromFile(fileName, &min_queue) &&
				readFromFile(fileName, &list)) {

				//NEXT FIT
				makeSingleSchedule(&max_queue, MAX_HEAP, Schedule::NEXT_FIT, 3, singleDay, 1, testNr, fileName);
				makeSingleSchedule(&min_queue, MIN_HEAP, Schedule::NEXT_FIT, 3, singleDay, 1, testNr, fileName);
				makeSingleSchedule(&list, Schedule::NEXT_FIT, 3, singleDay, 1, testNr, fileName);

				//FIRST FIT
				makeSingleSchedule(&max_queue, MAX_HEAP, Schedule::FIRST_FIT, 3, singleDay, 1, testNr, fileName);
				makeSingleSchedule(&min_queue, MIN_HEAP, Schedule::FIRST_FIT, 3, singleDay, 1, testNr, fileName);
				makeSingleSchedule(&list, Schedule::FIRST_FIT, 3, singleDay, 1, testNr, fileName);

				//BEST FIT
				makeSingleSchedule(&max_queue, MAX_HEAP, Schedule::BEST_FIT, 3, singleDay, 1, testNr, fileName);
				makeSingleSchedule(&min_queue, MIN_HEAP, Schedule::BEST_FIT, 3, singleDay, 1, testNr, fileName);
				makeSingleSchedule(&list, Schedule::BEST_FIT, 3, singleDay, 1, testNr, fileName);
			}
			break;
		case 3:
			fileName = "Operationer_3.txt";

			if (readFromFile(fileName, &max_queue) &&
				readFromFile(fileName, &min_queue) &&
				readFromFile(fileName, &list)) {

				//NEXT FIT
				makeSingleSchedule(&max_queue, MAX_HEAP, Schedule::NEXT_FIT, 3, singleDay, 1, testNr, fileName);
				makeSingleSchedule(&min_queue, MIN_HEAP, Schedule::NEXT_FIT, 3, singleDay, 1, testNr, fileName);
				makeSingleSchedule(&list, Schedule::NEXT_FIT, 3, singleDay, 1, testNr, fileName);

				//FIRST FIT
				makeSingleSchedule(&max_queue, MAX_HEAP, Schedule::FIRST_FIT, 3, singleDay, 1, testNr, fileName);
				makeSingleSchedule(&min_queue, MIN_HEAP, Schedule::FIRST_FIT, 3, singleDay, 1, testNr, fileName);
				makeSingleSchedule(&list, Schedule::FIRST_FIT, 3, singleDay, 1, testNr, fileName);

				//BEST FIT
				makeSingleSchedule(&max_queue, MAX_HEAP, Schedule::BEST_FIT, 3, singleDay, 1, testNr, fileName);
				makeSingleSchedule(&min_queue, MIN_HEAP, Schedule::BEST_FIT, 3, singleDay, 1, testNr, fileName);
				makeSingleSchedule(&list, Schedule::BEST_FIT, 3, singleDay, 1, testNr, fileName);
			}
			break;
		case 4:
			fileName = "Operationer_1a.txt";

			if (readFromFile(fileName, &max_queue) &&
				readFromFile(fileName, &min_queue)) {

				//FIRST FIT
				makeSingleSchedule(&max_queue, MAX_HEAP, Schedule::FIRST_FIT, 3, singleDay, 1, testNr, fileName);
				makeSingleSchedule(&min_queue, MIN_HEAP, Schedule::FIRST_FIT, 3, singleDay, 1, testNr, fileName);
			}

			fileName = "Operationer_1b.txt";

			if (readFromFile(fileName, &max_queue) &&
				readFromFile(fileName, &min_queue) &&
				readFromFile(fileName, &list)) {

				//FIRST FIT
				makeSingleSchedule(&max_queue, MAX_HEAP, Schedule::FIRST_FIT, 3, singleDay, 1, testNr, fileName);
				makeSingleSchedule(&min_queue, MIN_HEAP, Schedule::FIRST_FIT, 3, singleDay, 1, testNr, fileName);
			}
			break;
		case 5:
			fileName = "Operationer_2.txt";

			if (readFromFile(fileName, &max_queue)) {

				//FIRST FIT
				makeDoubleSchedule(&max_queue, MAX_HEAP, Schedule::FIRST_FIT, 6, doubleDay, 3, testNr, fileName);
			}
			break;
		case 6:
			fileName = "Operationer_3.txt";

			if (readFromFile(fileName, &max_queue) &&
				readFromFile(fileName, &min_queue) &&
				readFromFile(fileName, &list)) {

				//BEST FIT
				makeSingleSchedule(&max_queue, MAX_HEAP, Schedule::BEST_FIT, 16, singleDay, 1, testNr, fileName);
				makeSingleSchedule(&min_queue, MIN_HEAP, Schedule::BEST_FIT, 16, singleDay, 1, testNr, fileName);
				makeSingleSchedule(&list, Schedule::BEST_FIT, 16, singleDay, 1, testNr, fileName);
			}
			break;
	}
	
	getchar();
	getchar();
	return EXIT_SUCCESS;
}


/*
*  emptyPriorityQueue: Dequeues all objects in queue
*/
void emptyPriorityQueue(PriorityQueue<Operation>* que) {
	while (!que->isEmpty()) {
		que->dequeue();
	}
}


/*
*  emptyList: Removes all objects in list
*/
void emptyList(List<Operation>* list) {
	while (list->length() != 0) {
		list->removeAt(0);
	}
}


/*
*  readFromFile: Reads operation information from inputed file into que
*/
bool readFromFile(const string filename, PriorityQueue<Operation>* que) {
	bool error = false;

	emptyPriorityQueue(que);

	string read;
	size_t pos;

	int id;
	string type;
	int time;

	Operation tempObj;

	fstream file;
	file.open(filename, ios::in);

	if (file.is_open()) {
		while (getline(file, read) && !error && read.length() != 0) {
			pos = read.find(",");

			if (pos == string::npos) {
				error = true;
			} else {
				id = stoi(read.substr(0, pos));
				read = read.substr(pos + 1);

				pos = read.find(",");

				if (pos == string::npos) {
					error = true;
				} else {
					type = read.substr(0, pos);
					time = stoi(read.substr(pos + 1));

					tempObj.setID(id);
					tempObj.setType(type);
					tempObj.setTime(time);

					que->enqueue(time, tempObj);
				}
			}
		}
	} else {
		error = true;
	}

	return !error;
}


/*
*  readFromFile: Reads operation information from inputed file into list
*/
bool readFromFile(const string filename, List<Operation>* list) {
	bool error = false;

	emptyList(list);

	string read;
	size_t pos;

	int id;
	string type;
	int time;

	Operation tempObj;

	fstream file;
	file.open(filename, ios::in);

	if (file.is_open()) {
		while (getline(file, read) && !error && read.length() != 0) {
			pos = read.find(",");

			if (pos == string::npos) {
				error = true;
			} else {
				id = stoi(read.substr(0, pos));
				read = read.substr(pos + 1);

				pos = read.find(",");

				if (pos == string::npos) {
					error = true;
				} else {
					type = read.substr(0, pos);
					time = stoi(read.substr(pos + 1));

					tempObj.setID(id);
					tempObj.setType(type);
					tempObj.setTime(time);

					list->insertAt(0, tempObj);
				}
			}
		}
	} else {
		error = true;
	}

	return !error;
}


/*
*  makeSingleScheduleHeap: Creates a single day schedule and outputs result, based on priority queue elements. Returns the schedule for further use.
*/
Schedule makeSingleSchedule(const PriorityQueue<Operation>* que, const int heapType, const Schedule::AlgorithmType fitType,
							const int amountRooms, const int* timeSpan, const int timeSpanLength,
							int& testNr, const string fileName) {
	string heapTypeStr = "";
	string fitTypeStr = "";

	switch (heapType) {
	case MAX_HEAP:
		heapTypeStr = "Max Heap";
		break;
	case MIN_HEAP:
		heapTypeStr = "Min Heap";
		break;
	}

	switch (fitType) {
		case Schedule::NEXT_FIT:
			fitTypeStr = "Next Fit";
			break;
		case Schedule::FIRST_FIT:
			fitTypeStr = "First Fit";
			break;
		case Schedule::BEST_FIT:
			fitTypeStr = "Best Fit";
			break;
	}
	
	Schedule schedule(*que, amountRooms, timeSpan, timeSpanLength);
	schedule.fillBins(fitType);

	cout << endl << "\t\t\tTest " << testNr << " - " << fileName << " - " << fitTypeStr << " - " << heapTypeStr << endl << endl;
	schedule.printSchedule(0, amountRooms);
	schedule.printEffectivity();

	testNr++;

	return schedule;
}

/*
*  makeSingleScheduleList: Creates a single day schedule and outputs result, based on priority list elements. Returns the schedule for further use.
*/
Schedule makeSingleSchedule(const List<Operation>* list, const Schedule::AlgorithmType fitType,
							const int amountRooms, const int* timeSpan, const int timeSpanLength, 
							int& testNr, const string fileName) {
	string fitTypeStr = "";

	switch (fitType) {
	case Schedule::NEXT_FIT:
		fitTypeStr = "Next Fit";
		break;
	case Schedule::FIRST_FIT:
		fitTypeStr = "First Fit";
		break;
	case Schedule::BEST_FIT:
		fitTypeStr = "Best Fit";
		break;
	}

	Schedule schedule(*list, amountRooms, timeSpan, timeSpanLength);
	schedule.fillBins(fitType);

	cout << endl << "\t\t\tTest " << testNr << " - " << fileName << " - " << fitTypeStr << " - Unordered List" << endl << endl;
	schedule.printSchedule(0, amountRooms);
	schedule.printEffectivity();

	testNr++;

	return schedule;
}


/*
*  makeDoubleScheduleHeap: Creates a single day schedule and outputs result, based on priority queue elements. Returns the schedule for further use.
*/
Schedule makeDoubleSchedule(const PriorityQueue<Operation>* que, const int heapType, const Schedule::AlgorithmType fitType,
							const int amountRooms, const int* timeSpan, const int timeSpanLength,
							int& testNr, const string fileName) {
	string heapTypeStr = "";
	string fitTypeStr = "";

	switch (heapType) {
	case MAX_HEAP:
		heapTypeStr = "Max Heap";
		break;
	case MIN_HEAP:
		heapTypeStr = "Min Heap";
		break;
	}

	switch (fitType) {
	case Schedule::NEXT_FIT:
		fitTypeStr = "Next Fit";
		break;
	case Schedule::FIRST_FIT:
		fitTypeStr = "First Fit";
		break;
	case Schedule::BEST_FIT:
		fitTypeStr = "Best Fit";
		break;
	}

	Schedule schedule(*que, amountRooms, timeSpan, timeSpanLength);
	schedule.fillBins(fitType);

	cout << endl << "\t\t\tTest " << testNr << " - " << fileName << " - " << fitTypeStr << " - " << heapTypeStr << endl << endl;
	cout << "Monday:" << endl;
	schedule.printSchedule(0, amountRooms / 2);
	cout << endl << "Thuesday:" << endl;
	schedule.printSchedule(amountRooms / 2, amountRooms);
	schedule.printEffectivity();

	testNr++;

	return schedule;
}


/*
*  makeDoubleScheduleList: Creates a double day schedule and outputs result, based on priority list elements. Returns the schedule for further use.
*/
Schedule makeDoubleSchedule(const List<Operation>* list, const Schedule::AlgorithmType fitType,
							const int amountRooms, const int* timeSpan, const int timeSpanLength,
							int& testNr, const string fileName) {
	string fitTypeStr = "";

	switch (fitType) {
	case Schedule::NEXT_FIT:
		fitTypeStr = "Next Fit";
		break;
	case Schedule::FIRST_FIT:
		fitTypeStr = "First Fit";
		break;
	case Schedule::BEST_FIT:
		fitTypeStr = "Best Fit";
		break;
	}

	Schedule schedule(*list, amountRooms, timeSpan, timeSpanLength);
	schedule.fillBins(fitType);

	cout << endl << "\t\t\tTest " << testNr << " - " << fileName << " - " << fitTypeStr << " - Unordered List" << endl << endl;
	cout << "Monday:" << endl;
	schedule.printSchedule(0, amountRooms / 2);
	cout << endl << "Thuesday:" << endl;
	schedule.printSchedule(amountRooms / 2, amountRooms);
	schedule.printEffectivity();

	testNr++;

	return schedule;
}