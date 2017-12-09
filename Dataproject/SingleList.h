#include<iostream>
#include<stack>
using namespace std;
template<class T>
struct Node {//�ڵ�
	Node(const T &datavalue) :data(datavalue), next(NULL) {}
	T data;
	Node*next;
};
template<class T>
class List {
	template<class T>
	friend ostream&operator<<(ostream &os, const List<T>&list);//���������
public:
	List();
	~List();
	void insertfront(const T&data);//��ͷ������һ��Ԫ��
	void insert(const T&data, int index);//��index����Ԫ��
	void Delete(const T&data);//ɾ���ض�Ԫ��
	int find(const T&data);//�����ض�Ԫ��
	void reserveiterator();//ʹ�õ�������ת
	void mergeiterator(List<T>&la);//�ɵ�����ʵ����������鲢
	void selectsort();
	class Listiterator;
	Listiterator begin() { return Listiterator(head->next); }
	Listiterator end() { return Listiterator(NULL); }
	//��������
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
		Node<T>*getnode() {	return node;}//�õ���ǰ�ڵ�
		bool operator!=(const Listiterator right) const{ return node != right.node;}
		bool operator==(const Listiterator right) const{ return node == right.node;}
	public:
		Node<T>* node;
	};
public:
	Node<T>*head;
};
template<class T>
List<T>::List() {//����Ĺ��캯��   ����һ����ͷָ�������
	head = new Node<T>(0);
	head->next = NULL;
}
template<class T>
List<T>::~List() {//��������
	Node<T>*deleteNode = NULL;
	while (head != NULL) {
		deleteNode = head->next;
		delete head;
		head = deleteNode;
	}
}
//��ͷ������Ԫ��
template<class T>
void List<T>::insertfront(const T&data) {
	Node<T>*newNode = new Node<T>(data);
	newNode->next = head->next;
	head->next = newNode;
}
//��indexλ���ϲ���Ԫ�أ����index��������ĳ��ȣ�������������
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
//ɾ�������е�ָ��Ԫ��
template<class T>
void List<T>::Delete(const T&data) {
	if (head->next == NULL)//�����
		return;
	Node<T>*pre = head;
	for (Node<T>*phead = head->next; phead != NULL; phead = phead->next) {
		if (phead->data == data) {//��ǰ�ڵ��ֵ����Ҫɾ����ֵ
			pre->next = phead->next;
			delete phead;
			phead = pre;
		}
		else {
			pre = phead;
		}
	}
}
//���������е�ָ��Ԫ��.���ظ�Ԫ�ص�һ�γ��ֵ�λ�ã����û���򷵻�0
template<class T>
int List<T>::find(const T & data)
{
	int count = 1;
	for (Node<T>*phead = head->next; phead != NULL; phead = phead->next,count++) {
		if (phead->data == data)
			return count;
	}
	return 0;//������û�����Ԫ�أ�����0��
}
//�õ�����ʵ������ת ����ջ�Ƚ���������ԣ�������������ѹջ��Ȼ���ջ��ʵ������ķ��������
template<class T>
void List<T>::reserveiterator() {
	stack <T>stack;
	List<T>::Listiterator iter = this->begin();
	while (iter != this->end()) {
		stack.push((*iter));//�����ڵ��ֵ��ջ
		iter++;
	}
	while (!stack.empty()) {//��ջ���յ�ʱ�򣬽���Ԫ�س�ջ��
		cout << stack.top();
		stack.pop();
		if (!stack.empty()) {
			cout << "->";
		}
	}
}
//�õ�����ʵ��������������ĺϲ�
template<class T>
void List<T>::mergeiterator(List<T>&la) {
	List<T>::Listiterator iter1 = this->begin();
	List<T>::Listiterator iter2 = la.begin();
	Node<T>*p = new Node<T>(0);
	p = p->next;
	Node<T>*q;
	if (*iter1 <= *iter2) {//ȷ��ͷ�ڵ�
		p = iter1.getnode();
		iter1++;
	}
	else {
		p = iter2.getnode();
		iter2++;
	}
	q = p;//q���������ͷ�ڵ�
	while (iter1 != this->end() && iter2 != la.end()) {//����list1��list2�������������ǿյ�ʱ��ϲ�
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
	while (iter1 != this->end()) {//����ĸ�����ǿգ����ǿ�������ںϲ�����������
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
//���������
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