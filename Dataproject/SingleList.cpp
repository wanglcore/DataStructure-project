#include<iostream>
#include"SingleList.h"
using namespace std;
int main()
{
	int n,size;
	List<int>list1;
	cout << "list1�Ĵ�С: ";
	cin >> size;
	printf("����%d��Ԫ��\n", size);
	for (int i = 0; i < size; i++) {
		cin >> n;
		list1.insertfront(n);
	}
	cout << "list1��";
	cout << list1 << endl;
	cout << "����Ҫ���ҵ�Ԫ��:";
	cin >> n;
	cout << "��Ԫ����:";
	cout << list1.find(n) << endl;
	cout << "Ҫɾ����Ԫ��: ";
	cin >> n;
	list1.Delete(n);
	cout << list1 << endl;
	List<int>list2;
	cout << "list2�Ĵ�С: ";
	cin >> size;
	printf("����%d��Ԫ��\n", size);
	for (int i = 0; i < size; i++) {
		cin >> n;
		list2.insertfront(n);
	}
	cout << "list2: ";
	cout << list2 << endl;
	cout << "list1��list2�ϲ���"<< endl;	
	list1.mergeiterator(list2);
	cout << list1 << endl;
	cout << "list1�������:" << endl;
	list1.reserveiterator();
	system("pause");
	return 0;
}