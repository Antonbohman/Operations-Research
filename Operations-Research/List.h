#pragma once

template<typename T>
class List {
private:
	class Node {
	public:
		T object;
		Node* next;

		Node() {};
		virtual ~Node() {};

	};

	int nrOfNodes;
	Node* frontNode;

	int findPos(const T& element) const;

public:
	List();
	List(const List& other);
	List& operator=(const List& other);
	virtual ~List();

	void insertAt(int pos, const T& element) throw(...);
	T getAt(int pos) const throw(...);
	void removeAt(int pos) throw(...);

	bool removeElement(const T& element);
	bool findElement(const T& toFind) const;

	int length() const;
	void getAll(T arr[], int cap) throw(...);
};


template<typename T>
List<T>::List() {
	frontNode = nullptr;
	nrOfNodes = 0;
}

template<typename T>
List<T>::List(const List& other) {
	Node* newNode;
	Node* thisNode;
	Node* otherNode = other.frontNode;

	if (otherNode != nullptr) {
		newNode = new Node();
		newNode->object = otherNode->object;
		this->frontNode = newNode;

		thisNode = newNode;
		otherNode = otherNode->next;

		while (otherNode != nullptr) {
			newNode = new Node();
			newNode->object = otherNode->object;
			thisNode->next = newNode;

			thisNode = newNode;
			otherNode = otherNode->next;
		}
	} else {
		this->frontNode = nullptr;
	}

	this->nrOfNodes = other.nrOfNodes;
}

template<typename T>
List<T>& List<T>::operator=(const List& other) {
	if (this != &other) {
		this->~List();

		Node* newNode;
		Node* thisNode;
		Node* otherNode = other.frontNode;

		if (otherNode != nullptr) {
			newNode = new Node();
			newNode->object = otherNode->object;
			this->frontNode = newNode;

			thisNode = newNode;
			otherNode = otherNode->next;

			while (otherNode != nullptr) {
				newNode = new Node();
				newNode->object = otherNode->object;
				thisNode->next = newNode;

				thisNode = newNode;
				otherNode = otherNode->next;
			}
		} else {
			this->frontNode = nullptr;
		}

		this->nrOfNodes = other.nrOfNodes;
	}
	return *this;
}

template<typename T>
List<T>::~List() {
	Node* currentNode = frontNode;
	Node* nextNode = nullptr;

	while (currentNode != nullptr) {
		nextNode = currentNode->next;
		delete currentNode;
		currentNode = nextNode;
	}

	frontNode = nullptr;
}

template<typename T>
void List<T>::insertAt(int pos, const T& element) throw(...) {
	if (pos < 0 || pos > nrOfNodes) {
		throw "Out of bounds!";
	}

	Node* newNode = new Node();
	newNode->object = element;

	Node* nextNode = nullptr;
	Node* currentNode = frontNode;

	if (pos == 0) {
		newNode->next = currentNode;
		frontNode = newNode;
	} else {
		nextNode = currentNode->next;

		for (int i = 1; i < pos; i++) {
			currentNode = nextNode;
			nextNode = currentNode->next;
		}

		newNode->next = nextNode;
		currentNode->next = newNode;
	}

	nrOfNodes++;
}

template<typename T>
T List<T>::getAt(int pos) const throw(...) {
	if (pos < 0 || pos >= nrOfNodes) {
		throw "Out of bounds!";
	}

	Node* targetNode = frontNode;

	for (int i = 0; i < pos; i++) {
		targetNode = targetNode->next;
	}

	T element = targetNode->object;

	return element;
}

template<typename T>
void List<T>::removeAt(int pos) throw(...) {
	if (pos < 0 || pos >= nrOfNodes) {
		throw "Out of bounds!";
	}

	Node* nextNode = nullptr;
	Node* currentNode = frontNode;

	if (pos == 0) {
		nextNode = currentNode;
		frontNode = currentNode->next;
	} else {
		nextNode = currentNode->next;

		for (int i = 1; i < pos; i++) {
			currentNode = nextNode;
			nextNode = currentNode->next;
		}

		currentNode->next = nextNode->next;
	}

	delete nextNode;

	nrOfNodes--;
}

template<typename T>
int List<T>::findPos(const T& element) const {
	int pos = -1;

	Node* currentNode = frontNode;

	int index = 0;
	while (currentNode != nullptr && pos == -1) {
		if (currentNode->object == element)
			pos = index;

		currentNode = currentNode->next;
		index++;
	}

	return pos;
}

template<typename T>
bool List<T>::removeElement(const T& element) {
	bool removed = false;
	int pos = findPos(element);

	if (pos != -1) {
		removeAt(pos);
		removed = true;
	}

	return removed;
}

template<typename T>
bool List<T>::findElement(const T& toFind) const {
	bool found = false;
	int pos = findPos(toFind);

	if (pos != -1) {
		getAt(pos);
		found = true;
	}

	return found;
}

template<typename T>
int List<T>::length() const {
	return nrOfNodes;
}

template<typename T>
void List<T>::getAll(T arr[], int cap) throw(...) {
	if (cap < nrOfNodes) {
		throw "Array is not big enough for data!";
	}

	Node* currentNode = frontNode;

	int index = 0;
	while (currentNode != nullptr) {
		arr[index] = currentNode->object;
		currentNode = currentNode->next;
		index++;
	}
}

