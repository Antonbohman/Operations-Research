#include <iostream>
#include <string>
#include <fstream>
#include "Bin.h"
#include "PriorityQueue.h"

using namespace std;

/*
*  readFromFile: Reads graph information from inputed file
*/
bool readFromFile2(const string filename, PriorityQueue<Operation>* que) {
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
			}
			else {
				id = stoi(read.substr(0, pos));
				read = read.substr(pos + 1);

				pos = read.find(",");

				if (pos == string::npos) {
					error = true;
				}
				else {
					type = read.substr(0, pos);
					time = stoi(read.substr(pos + 1));

					tempObj.setID(id);
					tempObj.setType(type);
					tempObj.setTime(time);

					que->enqueue(time, tempObj);
				}
			}
		}
	}
	else {
		error = true;
	}

	return !error;
}

int main() {
	PriorityQueue<Operation> queue(1);
	readFromFile2("Operationer_1b.txt", &queue);

	//create rooms
	int amountRooms = 3;
	Bin* rooms = new Bin[amountRooms];
	for (int i = 0; i < amountRooms; i++)
	{
		rooms[i].resize(60 * 11);//8.00 - 19.00 (11 hours)
	}
	//First fit (osäker på rätt namn)
	while (!queue.isEmpty()) {
		Operation curr = queue.dequeue();
		for (int i = 0; i < amountRooms; i++)
		{
			if (rooms[i].remainingSize() > curr.getTime()) {
				rooms[i].addOperation(curr);
				i = amountRooms;//break
			}
		}
	}

	//print
	int length = 40;
	for (int i = 0; i < amountRooms; i++)
	{
		int scale = (1-((float)rooms[i].remainingSize() / rooms[i].maxSize())) * length;
		cout << "Room " << i << "|";
		for (int x = 0; x < length; x++)
		{
			cout << (scale > x ? (char)254u : (char)NULL);
		}
		cout << "| " << rooms[i].remainingSize() << "/" << rooms[i].maxSize() << endl;
	}

	getchar();
	return 0;
}