#pragma once
#include<iostream>
using namespace std;
template<class T>
struct TreeNode {
	int height;
	int key;
	TreeNode*left;
	TreeNode*right;
	TreeNode() { left = right = NULL; key = NULL; }
	TreeNode(const T&key) {
		this->key = key;
		left = right = NULL;
	}
	TreeNode&operator=(const TreeNode*node) {
		this->key = node->key;
		this->left = node->left;
		this->right = node->right;
	}
};
template<class T>
class AVLTree {
public:
	TreeNode<T>*root;
	int treesize;
	AVLTree() {
		root = new TreeNode<T>;
		treesize = 0;
	}
	~AVLTree() {erase(root);}
	void erase(TreeNode<T>*t);
	void visit(TreeNode<T>*t) { cout << t.key << " "; }
	void inorder(TreeNode<T>*t);
	void insert(const T&thekey);
	void cauheight(TreeNode<T>*t);
	int height() { return height(root); }
	int height(TreeNode<T>*t);
	AVLTree<T>*leftLeftRotation(TreeNode<T>*t);
};
template<class T>
int AVLTree<T>::height(TreeNode<T>*t) {

}
template<class T>
inline AVLTree<T>* AVLTree<T>::leftLeftRotation(TreeNode<T>* t) {
	TreeNode<T>*k;
	k = t->left;
	t-> = k->right;
	return NULL;
}
template<class T>
void AVLTree<T>::erase(TreeNode<T>*t) {
	if (root == NULL)
		return;
	erase(root->left);
	erase(root->right);
	delete root;
}

template<class T>
void AVLTree<T>::inorder(TreeNode<T>* t) {
	inorder(t->left);
	visit(t);
	inorder(t->right);
}

template<class T>
inline void AVLTree<T>::insert(const T & thekey) {
}

template<class T>
inline void AVLTree<T>::cauheight(TreeNode<T>* t) {
	if (t->left&&t->right)
		t->height = t->left->height > t->right->height:t->left->height + 1 ? t->right->height + 1;
	else if (t->left) {
		t->height = t->left->height + 1;
	}
	else if (t->right) {
		t->height = t->right->height+1;
	}

}

template<class T>
inline AVLTree<T>* AVLTree<T>::find(const T & thekey) {
	TreeNode<T>*t = root;
	while (t != NULL) {
		if (thekey < t->key)
			t = t->left;
		else if (thekey > t->key)
			t = t->right;
		else
			return t;
	}
	return NULL;
}

