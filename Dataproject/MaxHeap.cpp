#include<iostream>
#include<time.h>
#include<vector>
#include"MaxHeap.h"
using namespace std;
//int main() {
//	MaxHeap<int> maxheap;
//	srand((int)time(0));
//	int i = 0;
//	int b;
//	while (i++ <= 7) {
//		b = rand() % 41;
//		maxheap.push(b);
//	}
//	cout << "�ѵĲ�α���\n";
//	maxheap.levelorder(maxheap.root);
//	cout << endl;
//	maxheap.pop();
//	cout << "ɾ���Ѷ�Ԫ��" << endl;
//	maxheap.levelorder(maxheap.root);
//	cout << endl;
//	int a[10] = {1,2,11,9,13,7,12,4,10,1};
//	cout << "ԭ����\n";
//	for (const auto&i : a) {
//		cout << i << " ";
//	}
//	cout << endl;
//	MaxHeap<int>heap;
//	heap.heapsort(a, 10);
//	cout << "�����\n";
//	for (const auto &i : a)
//		cout << i << " ";
//	system("pause");
//	return 0;
//}