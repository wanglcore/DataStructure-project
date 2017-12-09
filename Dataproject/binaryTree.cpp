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
	cout <<"查找元素:16"<< endl;
	cout<<tree.find(16)<<endl;
	cout << "树的高度：";
	cout << tree.height() << endl;
	TreeNode<int>*e = tree.root;
	cout << "树的节点数：" << tree.getsize(e) << endl;
	cout << "中序遍历" << endl;
	tree.inorder(e);
	cout << endl;
	cout << "先序遍历" << endl;
	tree.preorder(e);
	cout << endl;
	cout << "后序遍历" << endl;
	tree.postorder(e);
	cout << endl;
	cout << "层次遍历" << endl;
	tree.levelorder(e);
	cout << endl;
	cout << "根据先序遍历和中序遍历重构后的后序遍历" << endl;
	tree.postorder(tree.recoustruct(tree.preor,tree.inor));
	cout << endl;
	cout << "删除节点:16" << endl;
	tree.Delete(16);
	TreeNode<int>*m = tree.root;
	cout << "中序遍历" << endl;
	tree.inorder(m);	cout << endl;
	cout << "查找元素: 16" << endl;
	cout << tree.find(16) << endl;
	system("pause");
	return 0;
}