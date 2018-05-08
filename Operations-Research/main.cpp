#include <iostream>
#include <string>
#include <fstream>

#include "Bin.h"
#include "PriorityQueue.h"

using namespace std;

bool readFromFile(const string filename, PriorityQueue<Operation>* que);

int main() {
	PriorityQueue<Operation> queue(MAX_HEAP);

	if (readFromFile("Operationer_2.txt", &queue)) {
		int amountRooms = 3;
		Bin* rooms = new Bin[amountRooms];

		//create rooms
		for (int i = 0; i < amountRooms; i++) {
			rooms[i].resize(60 * 11);	//8.00 - 19.00 (11 hours)
		}

		Operation curr;

		//First fit (osäker på rätt namn)
		while (!queue.isEmpty()) {
			curr = queue.dequeue();
			for (int i = 0; i < amountRooms; i++) {
				if (rooms[i].addOperation(curr)) {
					i = amountRooms;	//break
				}
			}
		}

		//print
		int length = 40;

		for (int i = 0; i < amountRooms; i++) {
			int scale = (1 - ((float)rooms[i].remainingSize() / rooms[i].maxSize())) * length;

			cout << "Room " << i << "|";
			for (int x = 0; x < length; x++) {
				cout << (scale > x ? (char)254u : (char)NULL);
			}
			cout << "| " << rooms[i].remainingSize() << "/" << rooms[i].maxSize() << endl;
		}
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