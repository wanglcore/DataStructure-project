#include<iostream>
#include<time.h>
#include"hashtable.h"
using namespace std;
int main() {
	srand((int)time(0));
	hashtable<int,int>table(10);
	pairNode<int,int>b;
	int i = 1;
	while (i++ <= 35) {
		b.key = rand();
		b.ele = rand();
		table.insert(b);
	}
	cout << table;
	pairNode<int, int>c;
	c=table.find(b.key);
	cout << "���ҽ��" << b.key << endl;
	cout << "key:" << c.key << " element:" << c.ele << endl;
	cout << "ɾ���ڵ�" << b.key << endl;
	table.earse(b.key);
	c = table.find(b.key);
	cout << "���ҽڵ�" << b.key<<endl;
	cout << "key:" << c.key << " element:" << c.ele << endl;
	system("pause");
}