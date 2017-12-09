#pragma once
#include<iostream>
#include<queue>
#include<vector>
using namespace std;
template<class T>
struct TreeNode {
	T key;
	TreeNode*left, *right, *parent;
	TreeNode() { left = right = parent= NULL; key = NULL; }
	TreeNode(const T&key) {
		this->key = key;
		left = right= parent = NULL;
	}
	TreeNode&operator=(const TreeNode*node) {
		this->key = node->key;
		this->left = node->left;
		this->right = node->right;
		this->parent = node->parent;
	}
};
template<class T>
class MaxHeap{
public:
	TreeNode<T>*root;
	MaxHeap() {
		root = new TreeNode<T>;
	}
	void push(const T&thekey);
	TreeNode<T>*pop();
	TreeNode<T>*findinsertpos(int hint);
	void levelorder(TreeNode<T>*);
	void visit(TreeNode<T>*tree);
	TreeNode<T>* findlast();
	void init(vector<T>ele, int length);
};
template<class T>
TreeNode<T>* MaxHeap<T>::findlast() {//寻找当前堆中的最后一个节点
	queue<TreeNode<T>*>q;
	TreeNode<T>*t = root;//从根部开始遍历
	while (t != NULL) {
		if (t->left!=NULL)//
			q.push(t->left);
		if (t->right!=NULL)
			q.push(t->right);
		if (q.empty())
			return t;
		t = q.front();
		q.pop();
	}
}
template<class T>
TreeNode<T>*MaxHeap<T>::pop() {//删除堆中的最大元素
	//root->key.~T();
	TreeNode<T>*t = findlast();//首先找到最后一个节点
	T element = t->key;
	if (t->parent->right != NULL) {//删除该节点
		t->parent->right = NULL;
	}
	else {
		t->parent->left = NULL;
	}
	delete t;
	root->key.~T();
	TreeNode<T>*q = root; //从根开始遍历，寻找值得插入位置
	TreeNode<T>*p = root->left;//p是q的孩子
	while (p!=NULL) {//当孩子不是空的
		if (q->right!=NULL&&p->key < q->right->key)//当前孩子的大的
			p = q->right;
		if (element >= p->key) {//如果值大于等于孩子的值，则可以将该节点值插入到q中
			break;
		}
		else {
			q->key = p->key;//父节点下移
			q = p;
			p = p->left;
		}
	}
	q->key = element;//
	return NULL;
}
template<class T>
void MaxHeap<T>::visit(TreeNode<T>*tree) {
	std::cout << tree->key << " ";
}
template<class T>
void MaxHeap<T>::levelorder(TreeNode<T>*t) {//中序遍历
	queue<TreeNode<T>*>q;
	while (t != NULL) {
		visit(t);
		if (t->left != NULL)
			q.push(t->left);
		if (t->right != NULL)
			q.push(t->right);
		if (q.empty())
			return;
		t = q.front();
		q.pop();
	}
}
template<class T>
void MaxHeap<T>::push(const T&key) {//插入元素
	if (root->key == NULL)//树为空时直接插入
		root = new TreeNode<T>(key);
	else {
		TreeNode<T>*tnode = new TreeNode<T>(key);
		TreeNode<T>*t = findinsertpos(0);//找到第一个可以加入的节点，即第一个孩子缺失的节点
		if (t->left == NULL) {//节点没有左孩子
			t->left = tnode;
			tnode->parent = t;//使用指针parent指向父节点
		}
		else {//没有右孩子
			t->right = tnode;
			tnode->parent = t;
		}
		TreeNode<T>*pre = tnode->parent;//插入新节点后，开始重构，使树重新满足堆的条件
		TreeNode<T>*suc = tnode;
		while (suc->parent!=NULL&&pre->key < key) {//父节点的值小于key并且不是根节点
			suc->key = pre->key;
			suc = pre;
			pre = pre->parent;//父节点上移
		}
		suc->key = key;//将孩子的值设为key
	}
}
//寻找插入位置，利用层次遍历的思路，使用队列，找到第一个孩缺失的节点
template<class T>
TreeNode<T>* MaxHeap<T>::findinsertpos(int hint) {
	queue<TreeNode<T>*>q;
	TreeNode<T>*t = root;
	while (t != NULL) {
		if (t->left == NULL)//该节点没有左孩子，返回该节点
			return t;
		else
			q.push(t->left);
		if (t->right == NULL)
			return t;
		else
			q.push(t->right);
		if (q.empty())
			return NULL;
		t = q.front();
		q.pop();
	}
}