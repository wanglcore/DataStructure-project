#include<iostream>
#include<stack>
using namespace std;
template<class T>
struct Node {//节点
	Node(const T &datavalue) :data(datavalue), next(NULL) {}
	T data;
	Node*next;
};
template<class T>
class List {
	template<class T>
	friend ostream&operator<<(ostream &os, const List<T>&list);//重载输出流
public:
	List();
	~List();
	void insertfront(const T&data);//从头部插入一个元素
	void insert(const T&data, int index);//从index插入元素
	void Delete(const T&data);//删除特定元素
	int find(const T&data);//查找特定元素
	void reserveiterator();//使用迭代器反转
	void mergeiterator(List<T>&la);//由迭代器实现有序链表归并
	void selectsort();
	class Listiterator;
	Listiterator begin() { return Listiterator(head->next); }
	Listiterator end() { return Listiterator(NULL); }
	//迭代器类
	class Listiterator{
	public:
		Listiterator(Node<T>* theNode = NULL){	node = theNode;	}
		T& operator*() const { return node->data; }
		T* operator->() const { return &node->data; }
		Listiterator& operator++(){
			node = node->next; 
			return *this; 
		}
		Listiterator operator++(int){
			Listiterator old = *this;
			node = node->next;
			return old;
		}
		Node<T>*getnode() {	return node;}//得到当前节点
		bool operator!=(const Listiterator right) const{ return node != right.node;}
		bool operator==(const Listiterator right) const{ return node == right.node;}
	public:
		Node<T>* node;
	};
public:
	Node<T>*head;
};
template<class T>
List<T>::List() {//链表的构造函数   创建一个有头指针的链表
	head = new Node<T>(0);
	head->next = NULL;
}
template<class T>
List<T>::~List() {//析构函数
	Node<T>*deleteNode = NULL;
	while (head != NULL) {
		deleteNode = head->next;
		delete head;
		head = deleteNode;
	}
}
//从头部插入元素
template<class T>
void List<T>::insertfront(const T&data) {
	Node<T>*newNode = new Node<T>(data);
	newNode->next = head->next;
	head->next = newNode;
}
//在index位置上插入元素，如果index大于链表的长度，则插在链表最后
template<class T>
void List<T>::insert(const T & data, int index)
{
	int count = 1;
	Node<T>*phead = head;
	while (count < index&&phead->next != NULL) {
		count++;
		phead = phead->next;
	}
	Node<T>*newNode = new Node<T>(data);
	newNode->next = phead->next;
	phead->next = newNode;
}
//删除数组中的指定元素
template<class T>
void List<T>::Delete(const T&data) {
	if (head->next == NULL)//链表空
		return;
	Node<T>*pre = head;
	for (Node<T>*phead = head->next; phead != NULL; phead = phead->next) {
		if (phead->data == data) {//当前节点的值等于要删除的值
			pre->next = phead->next;
			delete phead;
			phead = pre;
		}
		else {
			pre = phead;
		}
	}
}
//查找数组中的指定元素.返回该元素第一次出现的位置，如果没有则返回0
template<class T>
int List<T>::find(const T & data)
{
	int count = 1;
	for (Node<T>*phead = head->next; phead != NULL; phead = phead->next,count++) {
		if (phead->data == data)
			return count;
	}
	return 0;//链表中没有这个元素，返回0；
}
//用迭代器实现链表反转 利用栈先进后出的特性，遍历链表，依次压栈，然后出栈，实现链表的反序输出。
template<class T>
void List<T>::reserveiterator() {
	stack <T>stack;
	List<T>::Listiterator iter = this->begin();
	while (iter != this->end()) {
		stack.push((*iter));//将各节点的值入栈
		iter++;
	}
	while (!stack.empty()) {//当栈不空的时候，将各元素出栈。
		cout << stack.top();
		stack.pop();
		if (!stack.empty()) {
			cout << "->";
		}
	}
}
//用迭代器实现两个有序链表的合并
template<class T>
void List<T>::mergeiterator(List<T>&la) {
	List<T>::Listiterator iter1 = this->begin();
	List<T>::Listiterator iter2 = la.begin();
	Node<T>*p = new Node<T>(0);
	p = p->next;
	Node<T>*q;
	if (*iter1 <= *iter2) {//确定头节点
		p = iter1.getnode();
		iter1++;
	}
	else {
		p = iter2.getnode();
		iter2++;
	}
	q = p;//q是新链表的头节点
	while (iter1 != this->end() && iter2 != la.end()) {//遍历list1和list2，当两个链表都非空的时候合并
		if (*iter1 <= *iter2) {
			p->next = iter1.getnode();
			iter1++;
		}
		else {
			p->next = iter2.getnode();
			iter2++;
		}
		p = p->next;
	}
	while (iter1 != this->end()) {//检查哪个链表非空，将非空链表加在合并后的链表后面
		p->next = iter1.getnode();
		p = p->next;
		iter1++;
	}
	while (iter2 != la.end()) {
		p->next = iter2.getnode();
		p = p->next;
		iter2++;
	}
	this->head->next = q;
}
template<class T>
//重载输出流
ostream & operator<<(ostream & os, const List<T>& list)
{
	for (Node<T>*phead = list.head->next; phead != NULL; phead = phead->next) {
		os << phead->data;
		if (phead->next != NULL)
			cout << "->";
	}
	return os;
}
template<class T>
void List<T>::selectsort() {
	List<T>::iterator i = this->begin();
	List<T>::iterator j = this.end();
}