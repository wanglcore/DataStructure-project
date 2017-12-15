#pragma once
#include<iostream>
#include<vector>
#include"Queue.h"
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
	void push(const T&thekey);//增加元素
	TreeNode<T>*pop();//删除元素
	TreeNode<T>*findinsertpos();//寻找插入位置
	void levelorder(TreeNode<T>*);//层次遍历
	void visit(TreeNode<T>*tree);
	TreeNode<T>* findlast();//寻找最后一个元素
	void heapsort(T*arr, int length);//堆排序
	void init(T *ele, int length);//初始化
};
template<class T>
void MaxHeap<T>::init(T*ele, int length) {//初始化
	root = new TreeNode<T>(ele[0]);//根节点
	TreeNode<T>*t = root;
	int i = 1;
	T element;
	Queue<TreeNode<T>*>q;
	while (i < length) {
		if (t->left == NULL) {//当前节点的左子树为空，则将新节点插入到左子树上
			t->left = new TreeNode<T>(ele[i++]);
			t->left->parent = t;
			if (i == length)
				break;
		}
		else if (t->right == NULL) {//如果当前节点的右子树为空，
			t->right = new TreeNode<T>(ele[i++]);
			t->right->parent = t;
			if (i == length)
				break;
		}
		else {							//当前节点的左右子树都不为空时，进行重构
			TreeNode<T>*pre = t;//此时t是最后一个拥有子树的节点
			TreeNode<T>*succ = t->left;
			if (succ->key < pre->right->key) {
				swap(succ->key, pre->right->key);
			}
			element = succ->key;
			while (succ->parent != NULL && pre->key < element) {//当不是根节点并且父节点的值小于element，使父节点上移
				succ->key = pre->key;
				succ = pre;
				pre = pre->parent;
			}
			succ->key = element;
			q.push(t->left);
			q.push(t->right);
			t = q.front();//下一个节点
			q.pop();
		}
	}
	if (i == length) {//处理最后一个节点
		if (t->right != NULL) {
			if (t->left->key < t->right->key)
				swap(t->right->key, t->left->key);
		}
		TreeNode<T>*succ = t->left;
		element = succ->key;
		while (succ->parent != NULL && t->key < element) {
			succ->key = t->key;
			succ = t;
			t = t->parent;
		}
		succ->key = element;
	}
}
template<class T>
void MaxHeap<T>::heapsort(T*arr, int length) {//先将数组初始化为一个最大堆，然后输出堆顶的元素
	this->init(arr, length);
	for (int i = 0; i < length; i++) {
		arr[i] = this->root->key;
		this->pop();
	}
}
template<class T>
TreeNode<T>* MaxHeap<T>::findlast() {//寻找当前堆中的最后一个节点
	Queue<TreeNode<T>*>q;
	TreeNode<T>*t = root;//从根部开始遍历
	while (t != NULL) {
		if (t->left!=NULL)
			q.push(t->left);
		if (t->right!=NULL)
			q.push(t->right);
		if (q.empty())//当队列为空时说明是当前节点是最后一个节点.
			return t;
		t = q.front();
		q.pop();
	}
}
template<class T>
TreeNode<T>*MaxHeap<T>::pop() {//删除堆中的最大元素
	TreeNode<T>*t = findlast();//首先找到最后一个节点
	if (t->parent == NULL) {//节点是根节点
		delete t;
		return NULL;
	}
	T element = t->key;//保存最后一个节点的值
	if (t->parent->right != NULL) {//删除最后一个节点
		t->parent->right = NULL;
	}
	else {
		t->parent->left = NULL;
	}
	delete t;
	root->key.~T();
	TreeNode<T>*q = root; //从根开始遍历，寻找能够插入位置
	TreeNode<T>*p = root->left;//p是q的孩子
	while (p!=NULL) {//当孩子不是空的
		if (q->right!=NULL&&p->key < q->right->key)//找到左孩子和右孩子中较大的
			p = q->right;
		if (element >= p->key) {//如果值大于等于孩子的值，则可以将该节点值插入到q中，退出循环
			break;
		}
		else {
			q->key = p->key;//父节点下移
			q = p;
			p = p->left;
		}
	}
	q->key = element;
	return NULL;
}
template<class T>
void MaxHeap<T>::visit(TreeNode<T>*tree) {
	std::cout << tree->key << " ";
}
template<class T>
void MaxHeap<T>::levelorder(TreeNode<T>*t) {//层次遍历
	Queue<TreeNode<T>*>q;
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
		TreeNode<T>*t = findinsertpos();//找到第一个可以加入的节点，即第一个孩子缺失的节点
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
//寻找插入位置，利用层次遍历的思路，使用队列，找到第一个孩子缺失的节点
template<class T>
TreeNode<T>* MaxHeap<T>::findinsertpos() {
	Queue<TreeNode<T>*>q;
	TreeNode<T>*t = root;
	while (t != NULL) {
		if (t->left == NULL)//该节点没有左孩子，返回该节点
			return t;
		else
			q.push(t->left);//存在左孩子，则将左孩子加入队列
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