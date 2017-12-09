//#include<iostream>
//#include<time.h>
//#include"HashTables.h"
//using namespace std;
//int main() {
//	srand((int)time(0));
//	HashTable<int, int> table(1000);
//	int i = 1;
//	pairNode<int, int>b;
//	while (i++ <= 500) {
//		b.ele = rand();
//		b.key = rand();
//		table.insert(b);
//	}
//	cout << table;
//	pairNode<int, int>*c;
//	c = table.find(b.key);
//	cout <<"查找节点"<<b.key<< endl;
//	cout <<"key: "<< c->key << " elememt:" << c->ele << endl;
//	cout << "删除节点" << b.key << endl;
//	table.earse(b.key);
//	cout <<"查找节点"<<b.key<< endl;
//	c = table.find(b.key);
//	cout << "key: " << c->key << " elememt:" << c->ele << endl;
//	system("pause");
//}