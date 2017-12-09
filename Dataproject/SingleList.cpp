#include<iostream>
#include"SingleList.h"
using namespace std;
int main()
{
	int n,size;
	List<int>list1;
	cout << "list1的大小: ";
	cin >> size;
	printf("输入%d个元素\n", size);
	for (int i = 0; i < size; i++) {
		cin >> n;
		list1.insertfront(n);
	}
	cout << "list1：";
	cout << list1 << endl;
	cout << "输入要查找的元素:";
	cin >> n;
	cout << "该元素在:";
	cout << list1.find(n) << endl;
	cout << "要删除的元素: ";
	cin >> n;
	list1.Delete(n);
	cout << list1 << endl;
	List<int>list2;
	cout << "list2的大小: ";
	cin >> size;
	printf("输入%d个元素\n", size);
	for (int i = 0; i < size; i++) {
		cin >> n;
		list2.insertfront(n);
	}
	cout << "list2: ";
	cout << list2 << endl;
	cout << "list1和list2合并："<< endl;	
	list1.mergeiterator(list2);
	cout << list1 << endl;
	cout << "list1反序输出:" << endl;
	list1.reserveiterator();
	system("pause");
	return 0;
}