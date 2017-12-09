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
TreeNode<T>* MaxHeap<T>::findlast() {//Ѱ�ҵ�ǰ���е����һ���ڵ�
	queue<TreeNode<T>*>q;
	TreeNode<T>*t = root;//�Ӹ�����ʼ����
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
TreeNode<T>*MaxHeap<T>::pop() {//ɾ�����е����Ԫ��
	//root->key.~T();
	TreeNode<T>*t = findlast();//�����ҵ����һ���ڵ�
	T element = t->key;
	if (t->parent->right != NULL) {//ɾ���ýڵ�
		t->parent->right = NULL;
	}
	else {
		t->parent->left = NULL;
	}
	delete t;
	root->key.~T();
	TreeNode<T>*q = root; //�Ӹ���ʼ������Ѱ��ֵ�ò���λ��
	TreeNode<T>*p = root->left;//p��q�ĺ���
	while (p!=NULL) {//�����Ӳ��ǿյ�
		if (q->right!=NULL&&p->key < q->right->key)//��ǰ���ӵĴ��
			p = q->right;
		if (element >= p->key) {//���ֵ���ڵ��ں��ӵ�ֵ������Խ��ýڵ�ֵ���뵽q��
			break;
		}
		else {
			q->key = p->key;//���ڵ�����
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
void MaxHeap<T>::levelorder(TreeNode<T>*t) {//�������
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
void MaxHeap<T>::push(const T&key) {//����Ԫ��
	if (root->key == NULL)//��Ϊ��ʱֱ�Ӳ���
		root = new TreeNode<T>(key);
	else {
		TreeNode<T>*tnode = new TreeNode<T>(key);
		TreeNode<T>*t = findinsertpos(0);//�ҵ���һ�����Լ���Ľڵ㣬����һ������ȱʧ�Ľڵ�
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
//Ѱ�Ҳ���λ�ã����ò�α�����˼·��ʹ�ö��У��ҵ���һ����ȱʧ�Ľڵ�
template<class T>
TreeNode<T>* MaxHeap<T>::findinsertpos(int hint) {
	queue<TreeNode<T>*>q;
	TreeNode<T>*t = root;
	while (t != NULL) {
		if (t->left == NULL)//�ýڵ�û�����ӣ����ظýڵ�
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