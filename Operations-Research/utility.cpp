#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "PriorityQueue.h"
#include "Operation.h"

using namespace std;

/*
*  readFromFile: Reads graph information from inputed file
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

					que->enqueue(time,tempObj);
				}
			}
		}
	} else {
		error = true;
	}

	return !error;
}