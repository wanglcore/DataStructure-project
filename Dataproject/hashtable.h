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
	pairNode<K,E>find(K&thekey);//查找
	void insert(pairNode<K,E>&thepair);//插入
	void earse(K&thekey);//删除
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
		if (table[j].hint == 0) {//该位置没有过元素，说明该节点不存在
			return s;
		}
		else if(table[j].hint==2){//原来的元素被删除
			j = (j + 1) % divitor;
		}
		else if(table[j].key==thekey){//找到该节点
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
		if (table[j].key==NULL||table[j].key==thepair.key) {//这个位置没有元素或者元素与要插入的元素的key相同，更新节点
			table[j] = thepair;
			table[j].hint = 1;
			return;
		}
		else {
			j = (j + 1) % divitor;
		}
	} while (j != i);//循环结束时说明散列表已经满了
	expand();
	insert(table[i]);
}
template<class K, class E>
void hashtable<K, E>::earse(K&thekey) {
	int i = thekey%divitor;
	int j = i;
	do {
		if (table[j].hint == 0) {//说明没有值
			return;
		}
		else if (table[j].hint == 2) {//原来的值被删除
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
ostream&operator<<(ostream&os, hashtable<K,E>&ta) {//重载输出流
	for (int i = 0; i < ta.divitor; i++) {
		if (ta.table[i].key != NULL) {
			os <<"第"<< i <<"个位置: "<< "key:" << ta.table[i].key<<" "<<"element:"<<ta.table[i].ele;
			cout << endl;
		}
	}
	return os;
}
