#pragma once

template <typename T>
class PriorityQueue {
private:
	class Container {
	public:
		T object;
		int priority;

		Container() {};
		virtual ~Container() {};
	};

	Container* que;
	int nrOfElements;
	int maxElements;

	int heapType;

	void expand();
	bool comparePriority(const Container& left, const Container& right);

	void swapParent(const int childIndex);
	void swapChild(const int parentIndex);
public:
	static const int LOW = 0;
	static const int HIGH = 1;

	PriorityQueue(const int heapType = 0);
	PriorityQueue(const PriorityQueue& origObj);
	PriorityQueue<T>& operator=(const PriorityQueue& origObj);
	~PriorityQueue();

	void enqueue(const int priority, const T& element);
	T dequeue() throw(...);
	T front() const throw(...);
	bool isEmpty() const;
};

template <typename T>
PriorityQueue<T>::PriorityQueue(const int heapType) {
	this->heapType = heapType;

	maxElements = 8;
	nrOfElements = 0;

	que = new Container[maxElements];
}

template <typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue& origObj) {
	this->heapType = origObj.heapType;

	this->maxElements = origObj.maxElements;
	this->nrOfElements = origObj.nrOfElements;

	this->que = new Container[origObj.maxElements];

	for (int i = 0; i < origObj.nrOfElements; i++) {
		this->que[i] = origObj.que[i];
	}
}

template <typename T>
PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue& origObj) {
	if (this != &origObj) {
		this->heapType = origObj.heapType;

		this->maxElements = origObj.maxElements;
		this->nrOfElements = origObj.nrOfElements;

		delete[] this->que;
		this->que = new Container[origObj.maxElements];

		for (int i = 0; i < origObj.nrOfElements; i++) {
			this->que[i] = origObj.que[i];
		}
	}

	return *this;
}

template <typename T>
PriorityQueue<T>::~PriorityQueue() {
	delete[] que;
}

template <typename T>
void PriorityQueue<T>::expand() {
	if (nrOfElements == maxElements) {
		maxElements += ((maxElements / 8) * 4);
		Container* temp = new Container[maxElements];

		for (int i = 0; i < nrOfElements; i++) {
			temp[i] = que[i];
		}
		delete[] que;
		que = temp;
	}
}

template <typename T>
bool PriorityQueue<T>::comparePriority(const Container& left, const Container& right) {
	bool weight = false;

	if (heapType) {
		if (left.priority > right.priority) {
			weight = true;
		}
	} else {
		if (left.priority < right.priority) {
			weight = true;
		}
	}

	return weight;
}

template <typename T>
void PriorityQueue<T>::swapParent(const int childIndex) {
	if (childIndex > 0) {
		int parentIndex = ((childIndex + 1) / 2) - 1;

		if (comparePriority(que[childIndex], que[parentIndex])) {
			Container temp = que[childIndex];
			que[childIndex] = que[parentIndex];
			que[parentIndex] = temp;

			swapParent(parentIndex);
		}
	}
}

template <typename T>
void PriorityQueue<T>::swapChild(const int parentIndex) {
	int leftChildIndex = ((parentIndex + 1) * 2) - 1;
	int rightChildIndex = ((parentIndex + 1) * 2);

	int swapIndex = -1;

	if (leftChildIndex < nrOfElements) {
		if (rightChildIndex < nrOfElements) {
			if (comparePriority(que[leftChildIndex], que[rightChildIndex])) {
				swapIndex = leftChildIndex;
			} else {
				swapIndex = rightChildIndex;
			}
		} else {
			swapIndex = leftChildIndex;
		}

		if (comparePriority(que[swapIndex], que[parentIndex])) {
			Container temp = que[parentIndex];
			que[parentIndex] = que[swapIndex];
			que[swapIndex] = temp;

			swapChild(swapIndex);
		}
	}
}

template <typename T>
void PriorityQueue<T>::enqueue(const int priority, const T& element) {
	expand();

	Container item;
	item.object = element;
	item.priority = priority;

	que[nrOfElements++] = item;

	swapParent(nrOfElements - 1);
}

template <typename T>
T PriorityQueue<T>::dequeue() throw(...) {
	if (nrOfElements <= 0) {
		throw "Que is empty!";
	}

	Container item = que[0];

	que[0] = que[--nrOfElements];

	swapChild(0);

	return item.object;
}

template <typename T>
T PriorityQueue<T>::front() const throw(...) {
	if (nrOfElements <= 0) {
		throw "Que is empty!";
	}

	return que[0].object;
}

template <typename T>
bool PriorityQueue<T>::isEmpty() const {
	return (nrOfElements <= 0);
}
