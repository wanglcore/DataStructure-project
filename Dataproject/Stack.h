#pragma once
#include<iostream>
template<class T>
class Stack {
public:
	Stack(int capacity=200);
	~Stack() { delete[]stack; }
	int getsize() { return length; }
	bool empty();
	void push(const T &ele);
	T& pop();
	T& top();
public:
	T *stack;
	int tops;
	int size;
	int length;
};
template<class T>
Stack<T>::Stack(int capacity) {
	size = capacity;
	stack = new T[size];
	length = 0;
	tops = -1;
}
template<class T>
bool Stack<T>::empty() {
	return tops == -1;
}
template<class T>
void Stack<T>::push(const T&ele) {
	if (tops == size - 1) {
		T*s = new T[size * 2];
		for (int i = 0; i < size; i++) {
			s[i] = stack[i];
		}
		size *= 2;
		delete []stack;
		stack = s;
	}
	stack[++tops] = ele;
	length++;
}
template<class T>
T& Stack<T>::pop() {
	if (tops == -1) {
		//Ã»ÓÐÔªËØ
		T e = 0;
		return e;
		cout << "empty";
	}
	else {
		T e = stack[tops];
		stack[tops--].~T();
		length--;
		return e;
	}
}
template<class T>
T& Stack<T>::top() {
	if (tops == -1) {
		//
	}
	else {
		return stack[tops];
	}
}