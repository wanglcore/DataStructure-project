#pragma once
#include<iostream>
#include<queue>
using namespace std;

template<class T>
struct binaryTreeNode {
	T element;
	binaryTreeNode<T> *leftChild, *rightChild;
	binaryTreeNode<T>() { leftChild = rightChild = NULL; }
	binaryTreeNode<T>(const T& theElement) {
		element = theElement;
		leftChild = rightChild = NULL;
	}
	binaryTreeNode<T>(const T& theElement, binaryTreeNode *theLeftChild, binaryTreeNode *theRightChild) {
		element = theElement;
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}
};

template<class T>
class BinaryTree {
public:
	BinaryTree() { root = NULL; treeSize = 0; }
	BinaryTree(binaryTreeNode<T> *theRoot) { root = theRoot; treeSize = size(root); treeHeight = height(root); }
	bool empty() const { return treeSize == 0; }
	int height(binaryTreeNode<T> *t);
	int size(binaryTreeNode<T> *);
	void output();
	void visit(binaryTreeNode<T> *t);
	void preOrder(binaryTreeNode<T> *t);
	void inOrder(binaryTreeNode<T> *t);
	void postOrder(binaryTreeNode<T> *t);
	void leverOrder(binaryTreeNode<T> *t);
private:
	binaryTreeNode<T> *root;//指向根节点的指针
	int treeSize;
	int treeHeight;
};

template<class T>
int BinaryTree<T> ::height(binaryTreeNode<T> *t) {
	if (t == NULL) { return 0; }
	else {
		int leftHeight = height(t->leftChild);
		int rightHeight = height(t->rightChild);
		return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
	}
}

template<class T>
int BinaryTree<T>::size(binaryTreeNode<T> *t) {
	if (t == NULL) { return 0; }
	else {
		int leftSize = size(t->leftChild);
		int rightSize = size(t->rightChild);
		return leftSize + rightSize + 1;
	}
}

template<class T>
void BinaryTree<T>::output() {
	cout << "元素个数：" << treeSize << endl;
	cout << "树高：" << treeHeight << endl;
}

template<class T>
void BinaryTree<T>::visit(binaryTreeNode<T> *t) {
	if (t == NULL) { cout << ""; }
	else { cout << t->element << ""; }
}

template<class T>
void BinaryTree<T>::preOrder(binaryTreeNode<T> *t) {

	if (t != NULL) {
		visit(t);
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}

template<class T>
void BinaryTree<T>::inOrder(binaryTreeNode<T> *t) {

	if (t != NULL) {
		inOrder(t->leftChild);
		visit(t);
		inOrder(t->rightChild);
	}
}

template<class T>
void BinaryTree<T>::postOrder(binaryTreeNode<T> *t) {

	if (t != NULL) {
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		visit(t);
	}
}

template<class T>
void BinaryTree<T>::leverOrder(binaryTreeNode<T> *t) {

	queue<binaryTreeNode<T>*> q;
	while (t != NULL) {
		visit(t);
		if (t->leftChild != NULL) { q.push(t->leftChild); }
		if (t->rightChild != NULL) { q.push(t->rightChild); }
		if (q.empty())
			return;
		t = q.front();
		q.pop();
	}
}
