#include<iostream>
#include<time.h>
#include"BinaryTree.h"
using namespace std;
int main() {
	BinaryTree<int>tree;
	srand((int)time(0));
	int i = 0;
	tree.insert(16);
	while (i++ <= 7) {
		tree.insert(rand() % 41+1);
	}
	cout <<"����Ԫ��:16"<< endl;
	cout<<tree.find(16)<<endl;
	cout << "���ĸ߶ȣ�";
	cout << tree.height() << endl;
	TreeNode<int>*e = tree.root;
	cout << "���Ľڵ�����" << tree.getsize(e) << endl;
	cout << "�������" << endl;
	tree.inorder(e);
	cout << endl;
	cout << "�������" << endl;
	tree.preorder(e);
	cout << endl;
	cout << "�������" << endl;
	tree.postorder(e);
	cout << endl;
	cout << "��α���" << endl;
	tree.levelorder(e);
	cout << endl;
	cout << "���������������������ع���ĺ������" << endl;
	tree.postorder(tree.recoustruct(tree.preor,tree.inor));
	cout << endl;
	cout << "ɾ���ڵ�:16" << endl;
	tree.Delete(16);
	TreeNode<int>*m = tree.root;
	cout << "�������" << endl;
	tree.inorder(m);	cout << endl;
	cout << "����Ԫ��: 16" << endl;
	cout << tree.find(16) << endl;
	system("pause");
	return 0;
}