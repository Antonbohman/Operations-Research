#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

#include "Bin.h"
#include "PriorityQueue.h"

using namespace std;

bool readFromFile(const string filename, PriorityQueue<Operation>* que);

void firstFit(PriorityQueue<Operation>& queue, const int amountRooms, Bin* rooms, int& totalTime, int& totalOperation, int& bookedOperation);


string intToTime(const int time);
void printSchedule(const int amountRooms, const Bin* rooms, const int totalTime, const int totalOperation, const int bookedOperation);

/*
*  main: Starting point
*/
int main() {
	PriorityQueue<Operation> queue(MAX_HEAP);

	int totalTime, totalOperation, bookedOperation;

	int amountRooms = 0;
	Bin* rooms;

	if (readFromFile("Operationer_1a.txt", &queue)) {
		amountRooms = 3;
		rooms = new Bin[amountRooms];

		//create rooms
		for (int i = 0; i < amountRooms; i++) {
			rooms[i].resize(60 * 11);	//8.00 - 19.00 (11 hours)
		}

		firstFit(queue, amountRooms, rooms, totalTime, totalOperation, bookedOperation);

		printSchedule(amountRooms, rooms, totalTime, totalOperation, bookedOperation);

		if (readFromFile("Operationer_1b.txt", &queue)) {
			//reset rooms
			for (int i = 0; i < amountRooms; i++) {
				rooms[i].empty();
			}

			firstFit(queue, amountRooms, rooms, totalTime, totalOperation, bookedOperation);

			printSchedule(amountRooms, rooms, totalTime, totalOperation, bookedOperation);
		}

		delete[] rooms;
	}

	if (readFromFile("Operationer_2.txt", &queue)) {
		amountRooms = 9;
		rooms = new Bin[amountRooms];

		//create rooms
		for (int i = 0; i < amountRooms; i=i+3) {
			rooms[i].resize(60 * 11);	//8.00 - 19.00 (11 hours)
			rooms[i+1].resize(60 * 14);	//8.00 - 22.00 (14 hours)
			rooms[i+2].resize(60 * 9);	//8.00 - 17.00 (9 hours)
		}

		firstFit(queue, amountRooms, rooms, totalTime, totalOperation, bookedOperation);

		printSchedule(amountRooms, rooms, totalTime, totalOperation, bookedOperation);

		delete[] rooms;
	}

	getchar();
	return EXIT_SUCCESS;
}


/*
*  readFromFile: Reads operation information from inputed file
*/
bool readFromFile(const string filename, PriorityQueue<Operation>* que) {
	bool error = false;

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
*  nextFit: Fills rooms with operations according to Next Fit algorithm
*/
void nextFit(PriorityQueue<Operation>& queue, const int amountRooms, Bin* rooms, int& totalTime, int& totalOperation, int& bookedOperation) {

}


/*
*  firstFit: Fills rooms with operations according to First Fit algorithm
*/
void firstFit(PriorityQueue<Operation>& queue, const int amountRooms, Bin* rooms, int& totalTime, int& totalOperation, int& bookedOperation) {
	Operation curr;

	totalTime = 0;
	totalOperation = 0;
	bookedOperation = 0;

	//First fit (osäker på rätt namn)
	while (!queue.isEmpty()) {
		curr = queue.dequeue();
		totalTime += curr.getTime();
		totalOperation++;
		for (int i = 0; i < amountRooms; i++) {
			if (rooms[i].addOperation(curr)) {
				i = amountRooms;	//break
				bookedOperation++;
			}
		}
	}
}


/*
*  bestFit: Fills rooms with operations according to Best Fit algorithm
*/
void bestFit(PriorityQueue<Operation>& queue, const int amountRooms, Bin* rooms, int& totalTime, int& totalOperation, int& bookedOperation) {

}


/*
*  intToTime: Converts minutes to a string with hour and min seperated
*/
string intToTime(const int time) {
	string hour = to_string(time / 60);
	if (hour.length() == 1)
		hour = "0" + hour;

	string min = to_string(time % 60);
	if (min.length() == 1)
		min = "0" + min;

	return hour + "h" + min + "m";
}


/*
*  printSchedule: Prints schedule for selected rooms
*/
void printSchedule(const int amountRooms, const Bin* rooms, const int totalTime, const int totalOperation, const int bookedOperation) {
	int length = 40;
	int bookedTime = 0;

	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);
	
	for (int i = 0; i < amountRooms; i++) {
		int scale = (1 - ((float)rooms[i].remainingSize() / rooms[i].maxSize())) * length;

		cout << "Room " << i << " |";
		SetConsoleTextAttribute(hstdout, 0x03);
		for (int x = 0; x < length; x++) {
			cout << (scale > x ? (char)254u : (char)NULL);
		}
		SetConsoleTextAttribute(hstdout, csbi.wAttributes);
		cout << "| " << intToTime(rooms[i].remainingSize()) << "/" << intToTime(rooms[i].maxSize()) << endl;

		bookedTime += rooms[i].maxSize() - rooms[i].remainingSize();
	}

	cout << endl << "Effective Time: " << intToTime(bookedTime) << "/" << intToTime(totalTime) << endl;
	cout << "Operations: " << bookedOperation << "/" << totalOperation << endl << endl;
}