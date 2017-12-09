#include<iostream>
using namespace std;
template<class T>
class Queue {
public:
	int length;
	int begin;
	int end;
	int size;
	T* ele;
	Queue(int capacity = 200) {
		size = capacity;
		ele = new T[size];
		begin = end = 0;
		length = 0;
	}
	~Queue() { delete[]ele; }
	bool empty() { return length == 0; }
	T& front() {
		if (length == 0)
			cout << "error";
		return ele[begin+1];
	}
	T&back() {
		if (length == 0)
			cout << "error";
		return ele[end];
	}
	void pop() {
		if (length == 0)
			cout << "error";
		else {
			length--;
			begin = (begin + 1) % size;
			ele[begin].~T();
		}
	}
	void push(const T&theelement) {
		if ((end + 1) % size == begin) {

		}
		length++;
		end = (end + 1) % size;
		ele[end] = theelement;
	}
};