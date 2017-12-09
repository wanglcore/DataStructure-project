#include<iostream>
using namespace std;
template<class T>
struct Node {
	Node(const T&datavalue) :data(datavalue), next(NULL), pre(NULL) {}
	Node* next;
	Node*pre;
	T data;
};
template<class T>
class DoubleList {
	template<class T>
	friend ostream &operator<<(ostream&os, const DoubleList<T>&list);
private:
	Node<int>*head, *tail;
public:
	DoubleList();
	~DoubleList();
	void insertfront(const T&data);
	void insert(const T&data, int index);
	void Delete(const T&data);
	int find(const T&data);

};
template<class T>
DoubleList<T>::DoubleList() {
	head = new Node<T>(0);
	head->next = NULL;
	head->pre = NULL;
}
template<class T>
DoubleList<T>::~DoubleList() {
	Node<T>*temp, *phead;
	phead = head->next;
	while (phead != NULL) {
		temp = phead->next;
		head->next = temp;
		if (temp != NULL) {
			temp->pre = head;
			delete phead;
			phead = temp;
		}
	}
}
template<class T>
void DoubleList<T>::insertfront(const T&data) {
	Node<T>*newNode = new Node<T>(data);
	if (head->next == NULL) {
		head->next = newNode;
		newNode->pre = head;
	}
	else {
		newNode->next = head->next;
		head->next->pre = newNode;
		newNode->pre = head;
		head->next = newNode;
	}
}
template<class T>
void DoubleList<T>::insert(const T&data, int index) {
	int count = 1;
	Node<T>*phead= head;
	while (count < index&&phead->next != NULL) {
		phead = phead->next;
		count++;
	}
	Node<T>*temp = new Node<T>(data);
	if (phead->next == NULL) {
		phead->next = newNode;
		newNode.pre = phead;
	}
	else if (count <= index) {
		newNode->next = phead->next;
		phead->next->pre = newNode;
		phead->next = newNode;
		newNode->pre = phead;
	}

}

template<class T>
int DoubleList<T>::find(const T&data) {
	int count = 1;
	Node<T>*phead = head->next;
	for (; phead != NULL; phead = phead->next,count++) {
		if (phead->data == data)
			return count;
	}
	return 0;
}
template<class T>
void DoubleList<T>::Delete(const T&data) {
	if (head->next == NULL)
		return;
	Node<T>*temp = head;
	for (Node<T>*phead = head->next; phead->next != NULL; phead = phead->next) {
		if (phead->data == data) {
			phead->next->pre = temp;
			temp->next = phead->next;
			delete phead;
			phead = temp;
		}
		 if (phead->next == NULL) {
			temp->next = NULL;
			delete phead;
		}
		 else {
			 temp = phead;
		 }
	}
}
template<class T>
ostream &operator<<(ostream&os, const DoubleList<T>&list) {
	for (Node<T>*phead = list.head->next; phead != NULL; phead = phead->next) {
		os << phead->data;
		if (phead->next!= NULL) {
			cout << "->";
		}
	}
	return os;
}