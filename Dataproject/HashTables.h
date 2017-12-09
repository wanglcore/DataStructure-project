#include<iostream>
using namespace std;
template<class K,class E>
struct pairNode {
	K key;
	E ele;
	pairNode*next;
};
template<class K,class E>
class HashTable {//��ʽɢ��
	template<class K,class E>
	friend ostream&operator<<(ostream&os, HashTable<K,E>&ta);//���������
protected:
	int divisor;
	pairNode<K,E>*table;  //ɢ�б�
public:
	HashTable(int ndivisor);
	~HashTable() { delete[]table; }
	void insert(pairNode<K, E>&pairnode);
	void earse(K&thekey);
	pairNode<K, E>*find(K&thekey);
};
template<class K, class E>
HashTable<K,E>::HashTable(int ndivisor) {//��ʼ��
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
	int i = pairnode.key%divisor;//��ȡֵ����ֵΪ�ڵ���ɢ�б��е�λ��
	pairNode<K, E>*node = new pairNode<K, E>;
	node->key = pairnode.key;
	node->ele = pairnode.ele;
	pairNode<K, E>*q = table[i].next;
	bool exist = false;
	for (; q != NULL; q = q->next) {//�����Ƿ������ͬ��key�����������ͬ��key�����滻��ԭ����element�����˳�ѭ��
		if (q->key == pairnode.key) {
			q->ele = pairnode.ele;
			exist = true;
			break;
		}
	}
	if(exist){}//���existΪtrue˵��ǰ���ҵ���ͬ��key�������κβ�����
	else {//��������ͬ��key
		node->next = table[i].next;
		table[i].next = node;//ÿһ�ζ���ͷ�����롣����table[i]��ͷ�ڵ㡣
		table[i].key = 1;//���ñ��λ�����Ϊ1��˵����ͷ�ڵ����ֵ
	}
}
template<class K, class E>
pairNode<K, E>*HashTable<K,E>::find(K&thekey) {
	int i = thekey%divisor;//��ȡ��Ԫ�ص�λ��
	pairNode<K, E>*q = table[i].next;
	for (; q != NULL; q = q->next) {//������������ҵ�������
		if (q->key == thekey) {
			return q;
		}
	}
	pairNode<K, E>*s = new pairNode<K, E>;//�Ҳ���������һ���սڵ�
	s->key = NULL;
	s->ele = NULL;
	return s;
}
template<class K,class E>
ostream&operator<<(ostream&os, HashTable<K,E>&ta) {
	for (int i = 0; i < ta.divisor; i++) {
		if (ta.table[i].key == 1) {
			pairNode<K,E>*q = ta.table[i].next;
			cout << "��"<<i<<"��λ��: ";
			for (; q != NULL; q = q->next) {
				cout <<"��key:"<< q->key<<" element:"<<q->ele<<") ";
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
			for (; q != NULL; q = q->next) {//������������ҵ��ڵ㣬ɾ��
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