#include<iostream>
using namespace std;
template<class T>
class MinHeap {
public:
	MinHeap(int init = 100);
	~MinHeap() { delete[]heap; }
	bool empty()const { return heapsize = 0; }
	int size()const { return heapsize; }
	const T&top() {
		if (heapsize == 0)
			exit(1);
		return heap[1];
	}
	void pop();
	void push(const T&);
	void initialize(T*, int);
private:
	int heapsize;
	int arraylength;
	T*heap;
};
template<class T>
MinHeap<T>::MinHeap(int init) {
	arraylength = init;
	heap = new T[arraylength];
	heapsize = 0;
}
template<class T>
void MinHeap<T>::push(const T&element) {
	if (heapsize == arraylength) {
		//
	}
	int currentNode = ++heapsize;
	while (currentNode != 1 && heap[currentNode / 2] > element) {
		heap[currentNode] = heap[currentNode / 2];
		currentNode /= 2;
	}
	heap[currentNode] = element;
}
template<class T>
void MinHeap<T>::pop() {
	if (heap == 0) {
		return;
	}
	heap[1].~T();
	T lastele = heap[heapsize--];
	int currNode = 1;
	int child = 2;
	while (child <= heapsize) {
		if (child<heapsize&&heap[child]>heap[child + 1]) {
			child++;
		}
		if (lastele <= heap[child])
			break;
		heap[currNode] = heap[child];
		currNode = child;
		child *= 2;
	}
	heap[currNode] = lastele;
}
template<class T>
void MinHeap<T>::initialize(T*theheap, int thelength) {
	delete[]heap;
	heap = theheap;
	heapsize = thelength;
	for (int root = heapsize / 2; root >= 1; root--) {
		T rootele = heap[root];
		int child = root * 2;
		while (child <= heapsize) {
			if (child<heapsize&&heap[child]>heap[child + 1]) {
				child++;
			}
			if (rootele <= heap[child]) {
				break;
			}
			heap[child / 2] = heap[child];
			child *= 2;
		}
		heap[child / 2] = rootele;
	}
}