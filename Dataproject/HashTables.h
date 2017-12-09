#include<iostream>
using namespace std;
template<class K,class E>
struct pairNode {
	K key;
	E ele;
	pairNode*next;
};
template<class K,class E>
class HashTable {//链式散列
	template<class K,class E>
	friend ostream&operator<<(ostream&os, HashTable<K,E>&ta);//重载输出流
protected:
	int divisor;
	pairNode<K,E>*table;  //散列表
public:
	HashTable(int ndivisor);
	~HashTable() { delete[]table; }
	void insert(pairNode<K, E>&pairnode);
	void earse(K&thekey);
	pairNode<K, E>*find(K&thekey);
};
template<class K, class E>
HashTable<K,E>::HashTable(int ndivisor) {//初始化
	divisor = ndivisor;
	table = new pairNode<K, E>[divisor];
	for (int i = 0; i < divisor; i++) {
		table[i].key = NULL;
		table[i].ele = NULL;
		table[i].next = NULL;
	}
}
template<class K, class E>
void HashTable<K, E>:: insert(pairNode<K, E>&pairnode) {
	int i = pairnode.key%divisor;//获取值，该值为节点在散列表中的位置
	pairNode<K, E>*node = new pairNode<K, E>;
	node->key = pairnode.key;
	node->ele = pairnode.ele;
	pairNode<K, E>*q = table[i].next;
	bool exist = false;
	for (; q != NULL; q = q->next) {//查找是否存在相同的key，如果存在相同的key，则替换掉原来的element；并退出循环
		if (q->key == pairnode.key) {
			q->ele = pairnode.ele;
			exist = true;
			break;
		}
	}
	if(exist){}//如果exist为true说明前面找到相同的key；不做任何操作。
	else {//不存在相同的key
		node->next = table[i].next;
		table[i].next = node;//每一次都从头部插入。其中table[i]是头节点。
		table[i].key = 1;//设置标记位；如果为1则说明该头节点后有值
	}
}
template<class K, class E>
pairNode<K, E>*HashTable<K,E>::find(K&thekey) {
	int i = thekey%divisor;//获取该元素的位置
	pairNode<K, E>*q = table[i].next;
	for (; q != NULL; q = q->next) {//遍历链表，如果找到，返回
		if (q->key == thekey) {
			return q;
		}
	}
	pairNode<K, E>*s = new pairNode<K, E>;//找不到，返回一个空节点
	s->key = NULL;
	s->ele = NULL;
	return s;
}
template<class K,class E>
ostream&operator<<(ostream&os, HashTable<K,E>&ta) {
	for (int i = 0; i < ta.divisor; i++) {
		if (ta.table[i].key == 1) {
			pairNode<K,E>*q = ta.table[i].next;
			cout << "第"<<i<<"个位置: ";
			for (; q != NULL; q = q->next) {
				cout <<"（key:"<< q->key<<" element:"<<q->ele<<") ";
			}
			cout << endl;
		}
	}
	return os;
}
template<class K, class E>
void HashTable<K, E>::earse(K&thekey) {
	int i = thekey%divisor;
	if (table[i].key == 1) {
		if (table[i].next->key == thekey) {
			table[i].next = table[i].next->next;
		}
		else {
			pairNode<K, E>*q = table[i].next->next;
			pairNode<K, E> *p = table[i].next;
			for (; q != NULL; q = q->next) {//遍历链表，如果找到节点，删除
				if (q->key == thekey) {
					p->next = q->next;
					delete q;
					return;
				}
				p = q;

			}
		}
	}
}