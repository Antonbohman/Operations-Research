#include <iostream>
#include <string>
#include <fstream>

#include "Bin.h"
#include "PriorityQueue.h"

using namespace std;

bool readFromFile(const string filename, PriorityQueue<Operation>* que);
void printSchedule(const int amountRooms, const Bin* rooms, const int totalTime, const int totalOperation, const int bookedOperation);

/*
*  main: Starting point
*/
int main() {
	PriorityQueue<Operation> queue(MAX_HEAP);
	int totalTime = 0;
	int totalOperation = 0;
	int bookedOperation = 0;

	if (readFromFile("Operationer_1b.txt", &queue)) {
		int amountRooms = 3;
		Bin* rooms = new Bin[amountRooms];

		//create rooms
		for (int i = 0; i < amountRooms; i++) {
			rooms[i].resize(60 * 11);	//8.00 - 19.00 (11 hours)
		}

		Operation curr;

		//First fit decreasing
		//while (!queue.isEmpty()) {
		//	curr = queue.dequeue();
		//	totalTime += curr.getTime();
		//	totalOperation++;
		//	for (int i = 0; i < amountRooms; i++) {
		//		if (rooms[i].addOperation(curr)) {
		//			i = amountRooms;	//break
		//			bookedOperation++;
		//		}
		//	}
		//}

		//best fit decreasing
		while (!queue.isEmpty()) {
			curr = queue.dequeue();
			totalTime += curr.getTime();
			totalOperation++;

			int minIndex = -1;
			int minValue = INT_MAX;
			for (int i = 0; i < amountRooms; i++) {
				if (rooms[i].remainingSize() - curr.getTime() < minValue && rooms[i].remainingSize() - curr.getTime() >= 0) {
					minIndex = i;
				}
			}
			if (minIndex != -1) { rooms[minIndex].addOperation(curr); bookedOperation++; };
		}

		printSchedule(amountRooms, rooms, totalTime, totalOperation, bookedOperation);
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
		while (getline(file, read) && !error) {
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
*  intToTime: Converts minutes to a string with hour and min seperated
*/
string intToTime(const int time) {
	string output = "";

	string hour = to_string(time / 60);
	if (hour.length() == 1)
		hour.append("0");

	string min = to_string(time % 60);
	if (min.length() == 1)
		min.append("0");


	output = hour + "h" + min + "m";

	return output;
}

/*
*  printSchedule: Prints schedule for selected rooms
*/
void printSchedule(const int amountRooms, const Bin* rooms, const int totalTime, const int totalOperation, const int bookedOperation) {
	int length = 40;
	int bookedTime = 0;

	for (int i = 0; i < amountRooms; i++) {
		int scale = (1 - ((float)rooms[i].remainingSize() / rooms[i].maxSize())) * length;

		cout << "Room " << i << "|";
		for (int x = 0; x < length; x++) {
			cout << (scale > x ? (char)254u : (char)NULL);
		}
		cout << "| " << intToTime(rooms[i].remainingSize()) << "/" << intToTime(rooms[i].maxSize()) << endl;

		bookedTime += rooms[i].maxSize() - rooms[i].remainingSize();
	}

	cout << endl << "Effective Time: " << intToTime(bookedTime) << "/" << intToTime(totalTime) << endl;
	cout << "Operations: " << bookedOperation << "/" << totalOperation << endl;
}