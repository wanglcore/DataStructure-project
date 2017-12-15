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
	void push(const T&thekey);//����Ԫ��
	TreeNode<T>*pop();//ɾ��Ԫ��
	TreeNode<T>*findinsertpos();//Ѱ�Ҳ���λ��
	void levelorder(TreeNode<T>*);//��α���
	void visit(TreeNode<T>*tree);
	TreeNode<T>* findlast();//Ѱ�����һ��Ԫ��
	void heapsort(T*arr, int length);//������
	void init(T *ele, int length);//��ʼ��
};
template<class T>
void MaxHeap<T>::init(T*ele, int length) {//��ʼ��
	root = new TreeNode<T>(ele[0]);//���ڵ�
	TreeNode<T>*t = root;
	int i = 1;
	T element;
	Queue<TreeNode<T>*>q;
	while (i < length) {
		if (t->left == NULL) {//��ǰ�ڵ��������Ϊ�գ����½ڵ���뵽��������
			t->left = new TreeNode<T>(ele[i++]);
			t->left->parent = t;
			if (i == length)
				break;
		}
		else if (t->right == NULL) {//�����ǰ�ڵ��������Ϊ�գ�
			t->right = new TreeNode<T>(ele[i++]);
			t->right->parent = t;
			if (i == length)
				break;
		}
		else {							//��ǰ�ڵ��������������Ϊ��ʱ�������ع�
			TreeNode<T>*pre = t;//��ʱt�����һ��ӵ�������Ľڵ�
			TreeNode<T>*succ = t->left;
			if (succ->key < pre->right->key) {
				swap(succ->key, pre->right->key);
			}
			element = succ->key;
			while (succ->parent != NULL && pre->key < element) {//�����Ǹ��ڵ㲢�Ҹ��ڵ��ֵС��element��ʹ���ڵ�����
				succ->key = pre->key;
				succ = pre;
				pre = pre->parent;
			}
			succ->key = element;
			q.push(t->left);
			q.push(t->right);
			t = q.front();//��һ���ڵ�
			q.pop();
		}
	}
	if (i == length) {//�������һ���ڵ�
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
void MaxHeap<T>::heapsort(T*arr, int length) {//�Ƚ������ʼ��Ϊһ�����ѣ�Ȼ������Ѷ���Ԫ��
	this->init(arr, length);
	for (int i = 0; i < length; i++) {
		arr[i] = this->root->key;
		this->pop();
	}
}
template<class T>
TreeNode<T>* MaxHeap<T>::findlast() {//Ѱ�ҵ�ǰ���е����һ���ڵ�
	Queue<TreeNode<T>*>q;
	TreeNode<T>*t = root;//�Ӹ�����ʼ����
	while (t != NULL) {
		if (t->left!=NULL)
			q.push(t->left);
		if (t->right!=NULL)
			q.push(t->right);
		if (q.empty())//������Ϊ��ʱ˵���ǵ�ǰ�ڵ������һ���ڵ�.
			return t;
		t = q.front();
		q.pop();
	}
}
template<class T>
TreeNode<T>*MaxHeap<T>::pop() {//ɾ�����е����Ԫ��
	TreeNode<T>*t = findlast();//�����ҵ����һ���ڵ�
	if (t->parent == NULL) {//�ڵ��Ǹ��ڵ�
		delete t;
		return NULL;
	}
	T element = t->key;//�������һ���ڵ��ֵ
	if (t->parent->right != NULL) {//ɾ�����һ���ڵ�
		t->parent->right = NULL;
	}
	else {
		t->parent->left = NULL;
	}
	delete t;
	root->key.~T();
	TreeNode<T>*q = root; //�Ӹ���ʼ������Ѱ���ܹ�����λ��
	TreeNode<T>*p = root->left;//p��q�ĺ���
	while (p!=NULL) {//�����Ӳ��ǿյ�
		if (q->right!=NULL&&p->key < q->right->key)//�ҵ����Ӻ��Һ����нϴ��
			p = q->right;
		if (element >= p->key) {//���ֵ���ڵ��ں��ӵ�ֵ������Խ��ýڵ�ֵ���뵽q�У��˳�ѭ��
			break;
		}
		else {
			q->key = p->key;//���ڵ�����
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
void MaxHeap<T>::levelorder(TreeNode<T>*t) {//��α���
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
void MaxHeap<T>::push(const T&key) {//����Ԫ��
	if (root->key == NULL)//��Ϊ��ʱֱ�Ӳ���
		root = new TreeNode<T>(key);
	else {
		TreeNode<T>*tnode = new TreeNode<T>(key);
		TreeNode<T>*t = findinsertpos();//�ҵ���һ�����Լ���Ľڵ㣬����һ������ȱʧ�Ľڵ�
		if (t->left == NULL) {//�ڵ�û������
			t->left = tnode;
			tnode->parent = t;//ʹ��ָ��parentָ�򸸽ڵ�
		}
		else {//û���Һ���
			t->right = tnode;
			tnode->parent = t;
		}
		TreeNode<T>*pre = tnode->parent;//�����½ڵ�󣬿�ʼ�ع���ʹ����������ѵ�����
		TreeNode<T>*suc = tnode;
		while (suc->parent!=NULL&&pre->key < key) {//���ڵ��ֵС��key���Ҳ��Ǹ��ڵ�
			suc->key = pre->key;
			suc = pre;
			pre = pre->parent;//���ڵ�����
		}
		suc->key = key;//�����ӵ�ֵ��Ϊkey
	}
}
//Ѱ�Ҳ���λ�ã����ò�α�����˼·��ʹ�ö��У��ҵ���һ������ȱʧ�Ľڵ�
template<class T>
TreeNode<T>* MaxHeap<T>::findinsertpos() {
	Queue<TreeNode<T>*>q;
	TreeNode<T>*t = root;
	while (t != NULL) {
		if (t->left == NULL)//�ýڵ�û�����ӣ����ظýڵ�
			return t;
		else
			q.push(t->left);//�������ӣ������Ӽ������
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