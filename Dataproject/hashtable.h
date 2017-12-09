#include<iostream>
using namespace std;
template<class K,class E>
struct pairNode {
	pairNode&operator=(const pairNode&pairnode) {
		key = pairnode.key;
		ele = pairnode.ele;
		hint = pairnode.hint;
		return *this;
	}
	K key;
	E ele;
	int hint;
};
template<class K,class E>
class hashtable {
	template<class K,class E>
	friend ostream&operator<<(ostream&os, hashtable<K,E>&table);
public:
	hashtable(int ndivitor);
	~hashtable() { delete[]table; }
	void expand();
	pairNode<K,E>find(K&thekey);//����
	void insert(pairNode<K,E>&thepair);//����
	void earse(K&thekey);//ɾ��
public:
	pairNode<K,E>*table;
	int divitor;
};
template<class K,class E>
void hashtable<K, E>::expand() {
	divitor *= 2;
	pairNode<K, E>*tables = new pairNode < K,E>[divitor];
	for (int i = 0; i < divitor; i++) {
		table[i].key = NULL;
		table[i].ele = NULL;
		table[i].hint = 0;
	}
	for (int i = 0; i <= divitor / 2; i++) {
		if (table[i].key != NULL) {
			insert(table[i]);
		}
	}
	delete[]table;
	table = tables;
}
template<class K,class E>
hashtable<K,E>::hashtable(int ndivitor) {
	divitor = ndivitor;
	table = new pairNode<K,E>[divitor];
	for (int i = 0; i < divitor; i++) {
		table[i].key = NULL;
		table[i].ele = NULL;
		table[i].hint = 0;
	}
}
template<class K,class E>
pairNode<K,E> hashtable<K,E>::find(K & thekey) 
{
	pairNode<K, E>s;
	s.key = NULL;
	s.ele = NULL;
	s.hint = 0;
	int i = thekey%divitor;
	int j = i;
	do {
		if (table[j].hint == 0) {//��λ��û�й�Ԫ�أ�˵���ýڵ㲻����
			return s;
		}
		else if(table[j].hint==2){//ԭ����Ԫ�ر�ɾ��
			j = (j + 1) % divitor;
		}
		else if(table[j].key==thekey){//�ҵ��ýڵ�
			return table[j];
		}
		else {
			j = (j + 1) % divitor;
		}
	} while (j != i);
	return s;
}
template<class K,class E>
void hashtable<K,E>::insert(pairNode<K,E> &thepair)
{
	int i = thepair.key%divitor;
	int j = i;
	do {
		if (table[j].key==NULL||table[j].key==thepair.key) {//���λ��û��Ԫ�ػ���Ԫ����Ҫ�����Ԫ�ص�key��ͬ�����½ڵ�
			table[j] = thepair;
			table[j].hint = 1;
			return;
		}
		else {
			j = (j + 1) % divitor;
		}
	} while (j != i);//ѭ������ʱ˵��ɢ�б��Ѿ�����
	expand();
	insert(table[i]);
}
template<class K, class E>
void hashtable<K, E>::earse(K&thekey) {
	int i = thekey%divitor;
	int j = i;
	do {
		if (table[j].hint == 0) {//˵��û��ֵ
			return;
		}
		else if (table[j].hint == 2) {//ԭ����ֵ��ɾ��
			j = (j + 1) % divitor;
		}
		else if (table[j].key == thekey) {
			table[j].key = NULL;
			table[j].ele = NULL;
			table[j].hint = 2;
		}
		else {
			j = (j + 1) % divitor;
		}
	} while (j != i);
}
template<class K,class E>
ostream&operator<<(ostream&os, hashtable<K,E>&ta) {//���������
	for (int i = 0; i < ta.divitor; i++) {
		if (ta.table[i].key != NULL) {
			os <<"��"<< i <<"��λ��: "<< "key:" << ta.table[i].key<<" "<<"element:"<<ta.table[i].ele;
			cout << endl;
		}
	}
	return os;
}
