#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

#include "Bin.h"
#include "PriorityQueue.h"

using namespace std;

bool readFromFile(const string filename, PriorityQueue<Operation>* que);

void nextFit(PriorityQueue<Operation>& queue, const int amountRooms, Bin* rooms, int& totalTime, int& totalOperation, int& bookedTime, int& bookedOperation);
void firstFit(PriorityQueue<Operation>& queue, const int amountRooms, Bin* rooms, int& totalTime, int& totalOperation, int& bookedTime, int& bookedOperation);
void bestFit(PriorityQueue<Operation>& queue, const int amountRooms, Bin* rooms, int& totalTime, int& totalOperation, int& bookedTime, int& bookedOperation);

string intToTime(const int time);
void printSchedule(const int amountRooms, const Bin* rooms);
void printEffectivity(const int totalTime, const int totalOperation, const int& bookedTime, const int bookedOperation);

/*
*  main: Starting point
*/
int main() {
	PriorityQueue<Operation> queue(MAX_HEAP);

	int totalTime, totalOperation, bookedTime, bookedOperation;

	int amountRooms = 0;
	Bin* rooms;

	if (readFromFile("Operationer_1a.txt", &queue)) {
		amountRooms = 3;
		rooms = new Bin[amountRooms];

		//create rooms
		for (int i = 0; i < amountRooms; i++) {
			rooms[i].resize(60 * 11);	//8.00 - 19.00 (11 hours)
		}

		nextFit(queue, amountRooms, rooms, totalTime, totalOperation, bookedTime, bookedOperation);

		cout << "\tTest 1 - Operationer_1a.txt - Next Fit - Max Heap" << endl << endl;
		printSchedule(amountRooms, rooms);
		printEffectivity(totalTime, totalOperation, bookedTime, bookedOperation);

		if (readFromFile("Operationer_1a.txt", &queue)) {
			//reset rooms
			for (int i = 0; i < amountRooms; i++) {
				rooms[i].empty();
			}

			firstFit(queue, amountRooms, rooms, totalTime, totalOperation, bookedTime, bookedOperation);

			cout << "\tTest 2 - Operationer_1a.txt - First Fit - Max Heap" << endl << endl;
			printSchedule(amountRooms, rooms);
			printEffectivity(totalTime, totalOperation, bookedTime, bookedOperation);
		}

		delete[] rooms;
	}

	if (readFromFile("Operationer_2.txt", &queue)) {
		amountRooms = 6;
		rooms = new Bin[amountRooms];

		//create rooms
		for (int i = 0; i < amountRooms; i=i+3) {
			rooms[i].resize(60 * 11);	//8.00 - 19.00 (11 hours)
			rooms[i+1].resize(60 * 14);	//8.00 - 22.00 (14 hours)
			rooms[i+2].resize(60 * 9);	//8.00 - 17.00 (9 hours)
		}

		firstFit(queue, amountRooms, rooms, totalTime, totalOperation, bookedTime, bookedOperation);

		cout << "\tTest 3 - Operationer_2.txt - First Fit - Max Heap" << endl << endl;
		cout << "Monday:" << endl;
		printSchedule(amountRooms/2, rooms);
		cout << endl << "Thuesday:" << endl;
		printSchedule(amountRooms/2, rooms+3);
		printEffectivity(totalTime, totalOperation, bookedTime, bookedOperation);

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
void nextFit(PriorityQueue<Operation>& queue, const int amountRooms, Bin* rooms, int& totalTime, int& totalOperation, int& bookedTime, int& bookedOperation) {
	Operation curr;

	int currentRoom = 0;

	totalTime = 0;
	totalOperation = 0;
	bookedTime = 0;
	bookedOperation = 0;

	while (!queue.isEmpty()) {
		curr = queue.dequeue();
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
}


/*
*  firstFit: Fills rooms with operations according to First Fit algorithm
*/
void firstFit(PriorityQueue<Operation>& queue, const int amountRooms, Bin* rooms, int& totalTime, int& totalOperation, int& bookedTime, int& bookedOperation) {
	Operation curr;

	totalTime = 0;
	totalOperation = 0;
	bookedTime = 0;
	bookedOperation = 0;

	while (!queue.isEmpty()) {
		curr = queue.dequeue();
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
}


/*
*  bestFit: Fills rooms with operations according to Best Fit algorithm
*/
void bestFit(PriorityQueue<Operation>& queue, const int amountRooms, Bin* rooms, int& totalTime, int& totalOperation, int& bookedTime, int& bookedOperation) {
	Operation curr;

	totalTime = 0;
	totalOperation = 0;
	bookedTime = 0;
	bookedOperation = 0;

	while (!queue.isEmpty()) {
		curr = queue.dequeue();
		totalTime += curr.getTime();
		totalOperation++;
		//Fix algorithm!
		/*for (int i = currentRoom; i < amountRooms; i++) {
			currentRoom = i;
			if (rooms[i].addOperation(curr)) {
				i = amountRooms;	//break
				bookedTime += curr.getTime();
				bookedOperation++;
			}
		}*/
	}
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
void printSchedule(const int amountRooms, const Bin* rooms) {
	int length = 40;

	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);
	
	for (int i = 0; i < amountRooms; i++) {
		int scale = (1 - ((float)rooms[i].remainingSize() / rooms[i].maxSize())) * length;

		cout << "Room " << i+1 << " |";
		SetConsoleTextAttribute(hstdout, 0x03);
		for (int x = 0; x < length; x++) {
			cout << (scale > x ? (char)254u : (char)NULL);
		}
		SetConsoleTextAttribute(hstdout, csbi.wAttributes);
		cout << "| " << intToTime(rooms[i].remainingSize()) << "/" << intToTime(rooms[i].maxSize()) << endl;
	}
}


/*
*  printEffectivity: Prints effectivity statistics for schedule
*/
void printEffectivity(const int totalTime, const int totalOperation, const int& bookedTime, const int bookedOperation) {
	cout << endl << "Effective Time: " << intToTime(bookedTime) << "/" << intToTime(totalTime) << endl;
	cout << "Operations: " << bookedOperation << "/" << totalOperation << endl << endl;
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;
}