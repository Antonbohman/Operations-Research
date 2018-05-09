#include <iostream>
#include <string>
#include <fstream>

#include "PriorityQueue.h"
#include "List.h"
#include "Schedule.h"

using namespace std;

bool readFromFile(const string filename, PriorityQueue<Operation>* que);
bool readFromFile(const string filename, List<Operation>* list);

/*
*  main: Starting point
*/
int main() {
	PriorityQueue<Operation> max_queue(MAX_HEAP);
	PriorityQueue<Operation> min_queue(MIN_HEAP);
	List<Operation> list;

	int singleDay[1] = { 60 * 11 };	//
	int doubleDay[3] = { 60 * 11, 60 * 14, 60 * 9 };

	if (readFromFile("Operationer_1a.txt", &max_queue) &&
		readFromFile("Operationer_1a.txt", &min_queue) &&
		readFromFile("Operationer_1a.txt", &list)) {

		//NEXT FIT
		{
			Schedule schedule(max_queue, 3, singleDay, 1);
			schedule.fillBins(Schedule::NEXT_FIT);

			cout << "\tTest 1 - Operationer_1a.txt - Next Fit - Max Heap" << endl << endl;
			schedule.printSchedule(0, 3);
			schedule.printEffectivity();
		}

		{
			Schedule schedule(min_queue, 3, singleDay, 1);
			schedule.fillBins(Schedule::NEXT_FIT);

			cout << "\tTest 2 - Operationer_1a.txt - Next Fit - Min Heap" << endl << endl;
			schedule.printSchedule(0, 3);
			schedule.printEffectivity();
		}

		{
			Schedule schedule(list, 3, singleDay, 1);
			schedule.fillBins(Schedule::NEXT_FIT);

			cout << "\tTest 3 - Operationer_1a.txt - Next Fit - Unordered List" << endl << endl;
			schedule.printSchedule(0, 3);
			schedule.printEffectivity();
		}


		//FIRST FIT
		{
			Schedule schedule(max_queue, 3, singleDay, 1);
			schedule.fillBins(Schedule::FIRST_FIT);

			cout << "\tTest 4 - Operationer_1a.txt - First Fit - Max Heap" << endl << endl;
			schedule.printSchedule(0, 3);
			schedule.printEffectivity();
		}

		{
			Schedule schedule(min_queue, 3, singleDay, 1);
			schedule.fillBins(Schedule::FIRST_FIT);

			cout << "\tTest 5 - Operationer_1a.txt - First Fit - Min Heap" << endl << endl;
			schedule.printSchedule(0, 3);
			schedule.printEffectivity();
		}

		{
			Schedule schedule(list, 3, singleDay, 1);
			schedule.fillBins(Schedule::FIRST_FIT);

			cout << "\tTest 6 - Operationer_1a.txt - First Fit - Unordered List" << endl << endl;
			schedule.printSchedule(0, 3);
			schedule.printEffectivity();
		}


		//BEST FIT
		{
			Schedule schedule(max_queue, 3, singleDay, 1);
			schedule.fillBins(Schedule::BEST_FIT);

			cout << "\tTest 7 - Operationer_1a.txt - Best Fit - Max Heap" << endl << endl;
			schedule.printSchedule(0, 3);
			schedule.printEffectivity();
		}

		{
			Schedule schedule(min_queue, 3, singleDay, 1);
			schedule.fillBins(Schedule::BEST_FIT);

			cout << "\tTest 8 - Operationer_1a.txt - Best Fit - Min Heap" << endl << endl;
			schedule.printSchedule(0, 3);
			schedule.printEffectivity();
		}

		{
			Schedule schedule(list, 3, singleDay, 1);
			schedule.fillBins(Schedule::BEST_FIT);

			cout << "\tTest 9 - Operationer_1a.txt - Best Fit - Unordered List" << endl << endl;
			schedule.printSchedule(0, 3);
			schedule.printEffectivity();
		}
	}

	if (readFromFile("Operationer_3.txt", &max_queue) &&
		readFromFile("Operationer_3.txt", &min_queue) &&
		readFromFile("Operationer_3.txt", &list)) {

		//NEXT FIT
			{
				Schedule schedule(max_queue, 3, singleDay, 1);
				schedule.fillBins(Schedule::NEXT_FIT);

				cout << "\tTest 10 - Operationer_3.txt - Next Fit - Max Heap" << endl << endl;
				schedule.printSchedule(0, 3);
				schedule.printEffectivity();
			}

			{
				Schedule schedule(min_queue, 3, singleDay, 1);
				schedule.fillBins(Schedule::NEXT_FIT);

				cout << "\tTest 11 - Operationer_3.txt - Next Fit - Min Heap" << endl << endl;
				schedule.printSchedule(0, 3);
				schedule.printEffectivity();
			}

			{
				Schedule schedule(list, 3, singleDay, 1);
				schedule.fillBins(Schedule::NEXT_FIT);

				cout << "\tTest 12 - Operationer_3.txt - Next Fit - Unordered List" << endl << endl;
				schedule.printSchedule(0, 3);
				schedule.printEffectivity();
			}


			//FIRST FIT
			{
				Schedule schedule(max_queue, 3, singleDay, 1);
				schedule.fillBins(Schedule::FIRST_FIT);

				cout << "\tTest 13 - Operationer_3.txt - First Fit - Max Heap" << endl << endl;
				schedule.printSchedule(0, 3);
				schedule.printEffectivity();
			}

			{
				Schedule schedule(min_queue, 3, singleDay, 1);
				schedule.fillBins(Schedule::FIRST_FIT);

				cout << "\tTest 14 - Operationer_3.txt - First Fit - Min Heap" << endl << endl;
				schedule.printSchedule(0, 3);
				schedule.printEffectivity();
			}

			{
				Schedule schedule(list, 3, singleDay, 1);
				schedule.fillBins(Schedule::FIRST_FIT);

				cout << "\tTest 15 - Operationer_3.txt - First Fit - Unordered List" << endl << endl;
				schedule.printSchedule(0, 3);
				schedule.printEffectivity();
			}


			//BEST FIT
			{
				Schedule schedule(max_queue, 3, singleDay, 1);
				schedule.fillBins(Schedule::BEST_FIT);

				cout << "\tTest 16 - Operationer_3.txt - Best Fit - Max Heap" << endl << endl;
				schedule.printSchedule(0, 3);
				schedule.printEffectivity();
			}

			{
				Schedule schedule(min_queue, 3, singleDay, 1);
				schedule.fillBins(Schedule::BEST_FIT);

				cout << "\tTest 17 - Operationer_3.txt - Best Fit - Min Heap" << endl << endl;
				schedule.printSchedule(0, 3);
				schedule.printEffectivity();
			}

			{
				Schedule schedule(list, 3, singleDay, 1);
				schedule.fillBins(Schedule::BEST_FIT);

				cout << "\tTest 18 - Operationer_3.txt - Best Fit - Unordered List" << endl << endl;
				schedule.printSchedule(0, 3);
				schedule.printEffectivity();
			}
	}


	if (readFromFile("Operationer_2.txt", &max_queue)) {
		{
			Schedule schedule(max_queue, 6, doubleDay, 3);
			schedule.fillBins(Schedule::FIRST_FIT);

			cout << "\tTest 19 - Operationer_2.txt - First Fit - Max Heap" << endl << endl;
			cout << "Monday:" << endl;
			schedule.printSchedule(0, 3);
			cout << endl << "Thuesday:" << endl;
			schedule.printSchedule(3, 6);
			schedule.printEffectivity();
		}
	}

	if (readFromFile("Operationer_3.txt", &max_queue) &&
		readFromFile("Operationer_3.txt", &min_queue) &&
		readFromFile("Operationer_3.txt", &list)) {


			//BEST FIT
			{
				Schedule schedule(max_queue, 16, singleDay, 1);
				schedule.fillBins(Schedule::BEST_FIT);

				cout << "\tTest 16 - Operationer_3.txt - Best Fit - Max Heap" << endl << endl;
				schedule.printSchedule(0, 16);
				schedule.printEffectivity();
			}

			{
				Schedule schedule(min_queue, 16, singleDay, 1);
				schedule.fillBins(Schedule::BEST_FIT);

				cout << "\tTest 17 - Operationer_3.txt - Best Fit - Min Heap" << endl << endl;
				schedule.printSchedule(0, 16);
				schedule.printEffectivity();
			}

			{
				Schedule schedule(list, 16, singleDay, 1);
				schedule.fillBins(Schedule::BEST_FIT);

				cout << "\tTest 18 - Operationer_3.txt - Best Fit - Unordered List" << endl << endl;
				schedule.printSchedule(0, 16);
				schedule.printEffectivity();
			}
	}

	getchar();
	return EXIT_SUCCESS;
}


/*
*  readFromFile: Reads operation information from inputed file into que
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
*  readFromFile: Reads operation information from inputed file into list
*/
bool readFromFile(const string filename, List<Operation>* list) {
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

					list->insertAt(0, tempObj);
				}
			}
		}
	} else {
		error = true;
	}

	return !error;
}