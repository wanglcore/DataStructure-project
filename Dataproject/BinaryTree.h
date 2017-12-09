#include<iostream>
#include<vector>
#include"Queue.h"
template<class T>
struct TreeNode {
	T key;
	TreeNode<T>*left,*right;
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
class BinaryTree {
public:
	TreeNode<T>*root;
	vector<T>preor, inor;
	~BinaryTree() { erase(root); }
	void erase(TreeNode<T>*);//ɾ����
	void visit(TreeNode<T>*tree);//���ʽڵ�
	void levelorder(TreeNode<T>*t);//��α���
	void preorder(TreeNode<T>*t);//�������
	void inorder(TreeNode<T>*t);//�������
	void postorder(TreeNode<T>*t);//�������
	void insert(const T&key);//�����в���ڵ�
	bool find(const T&key);//���ҽڵ�
	void Delete(const T&key);//ɾ���ڵ�
	void Delete_Node(TreeNode<T>*);//ɾ��ͬʱ�������������������Ľڵ㣬��Delete()��������
	int height(TreeNode<T>*t);//�ڵ�T�ĸ߶�
	int height() { return height(root); }
	TreeNode<T>* recoustruct(vector<T>preor, vector<T>inor);//��֪���� �������������������ع���
	int getsize(TreeNode<T>*t);//���Ľڵ����
};
template<class T>
int BinaryTree<T>::getsize(TreeNode<T>*t) {//ʹ�õݹ�������ڵ����
	if (t == NULL)
		return 0;
	return getsize(t->left) + getsize(t->right) + 1;//��Ϊt�����Ľڵ����Ϊt���������Ľڵ���������������Ľڵ����+1
}
template<class T>
int BinaryTree<T>::height(TreeNode<T>*t) {
	if (t == NULL)
		return 0;
	int hl = height(t->left);
	int hr = height(t->right);
	return  hl > hr ? ++hl : ++hr;//��Ϊt�����ĸ߶�Ϊ���������������и߶ȸ��ߵĸ߶ȼ�һ
}
template<class T>
void BinaryTree<T>::erase(TreeNode<T>*t) {
	if (root == NULL)
		return;
	erase(root->right);
	erase(root->left);
	delete root;
}
template<class T>
void BinaryTree<T>::visit(TreeNode<T>*tree) {
	std::cout << tree->key << " ";
}
template<class T>
void BinaryTree<T>::inorder(TreeNode<T>*t) {//���������������������������
	if (t != NULL) {
		inorder(t->left);
		inor.push_back(t->key);
		visit(t);
		inorder(t->right);
	}
}
template<class T>
void BinaryTree<T>::preorder(TreeNode<T>*t) {//���������������������������
	if (t != NULL) {
		preor.push_back(t->key);
		visit(t);
		preorder(t->left);
		preorder(t->right);
	}
}
template<class T>
void BinaryTree<T>::postorder(TreeNode<T>*t) {//���������������������������
	if (t != NULL) {
		postorder(t->left);
		postorder(t->right);
		visit(t);
	}
}
template<class T>
void BinaryTree<T>::levelorder(TreeNode<T>*t) {//��α��������ϵ��£�������
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
TreeNode<T>* BinaryTree<T>::recoustruct(vector<T>preor, vector<T>inor) {//��������ͬ��
	vector<T>left_pre, left_in, right_pre, right_in;
	int position = 0;
	int length = inor.size();
	if (length == 0)
		return NULL;
	TreeNode<T>*head = new TreeNode<T>(preor[0]);//��������е�һ��Ԫ���Ƕ������ĸ�
	for (int i = 0; i < length; i++) {
		if (preor[0] == inor[i]) {//����������У��ҵ������ڵ�λ��
			position = i;
			break;
		}
	}
	for (int i = 1; i < position + 1; i++) {//����������������������ұ���������
		left_pre.push_back(preor[i]);//���������������
		left_in.push_back(inor[i - 1]);//���������������
	}
	for (int i = position + 1; i < length; i++) {
		right_pre.push_back(preor[i]);//���������������
		right_in.push_back(inor[i]);//��������������
	}
	head->left = recoustruct(left_pre, left_in);//���������������������������ݹ���ø÷���
	head->right = recoustruct(right_pre, right_in);//�������������������������ݹ����
	return head;
}
template<class T>
bool BinaryTree<T>::find(const T&key) {//�����ض�Ԫ��
	TreeNode<T>*t = root;
	while (t->key != key) {
		if (key < t->key) {
			if (t->left)
				t = t->left;
			else
				return false;
		}
		else {
			if (t->right)
				t = t->right;
			else
				return false;
		}
	}
	return true;
}
template<class T>
void BinaryTree<T>::Delete_Node(TreeNode<T>*t) {//ɾ�����������������������Ľڵ�t
	TreeNode<T>*q = t->right;
	TreeNode<T>*pq = t->right;
	while (q->left) {//�ҵ��ڵ�t���������е�ֵ��С�����ڵ�
		pq = q;
		q = q->left;
	}
	swap(t->key, q->key);//�����ýڵ�ͽڵ�t��ֵ
	pq->left = q->right;//��Ϊ�ýڵ�һ��û��������������ֱ��ʹ���ڵ�ָ��ýڵ��������
	delete q;
}
template<class T>
void BinaryTree<T>::Delete(const T&key) {//ɾ���ؼ���Ϊkey�����ڵ�
	TreeNode<T>*p = root;
	TreeNode<T>*t = root;
	while (t->key != key&&t->key!=NULL) {//���Ȳ���ֵΪkey�����ڵ��Ƿ���ڣ�����������ҵ��ýڵ㣬pΪt�ĸ��ڵ�
		if (key < t->key) {
			if (t->left != NULL) {
				p = t;
				t = t->left;
			}
		}
		else {
			if (t->right != NULL) {
				p = t;
				t = t->right;
			}
		}
	}
	if(t->key==key){		//�ҵ��ýڵ�
		if (p->key > t->key) {//Ҫɾ���Ľڵ��Ǹ��ڵ�����ӽڵ�
			if (t->right == NULL) {//Ҫɾ���Ľڵ��������Ϊ��
				p->left = t->left;
				delete t;
			}
			else if (t->left == NULL) {//Ҫɾ���Ľڵ��������Ϊ��
				p->left = t->right;
				delete t;
			}
			else {
				Delete_Node(t);//������������Ϊ��
			}
		}
		else if(p->key<t->key){//Ҫɾ���Ľڵ��Ǹ��ڵ�����ӽڵ�
			if (t->left == NULL) {//Ҫɾ���Ľڵ�������Ϊ��
				p->right = t->right;
				delete t;
			}
			else if (t->right == NULL) {//Ҫɾ���Ľڵ�������Ϊ��
				p->right = t->left;
				delete t;
			}
			else {
				Delete_Node(t);//Ҫɾ���Ľڵ�ͬʱ������������������
			}
		}
		else {//Ҫɾ���Ľڵ��Ǹ��ڵ�
			if (root->left == NULL) {
				root = root->right;
			}
			else if (root->right == NULL) {
				root = root->left;
			}
			else {
				Delete_Node(p);
			}
		}
	}
}
template<class T>
void BinaryTree<T>::insert(const T&key) {
	if (root == NULL) //���ڵ�Ϊ��
		root = new TreeNode<T>(key);
	else {
		TreeNode<T>*tempnode = new TreeNode<T>(key);
		TreeNode<T>*temp = root;//�Ӹ��ڵ㿪ʼ���ҿ��Բ����λ��
		while (temp->key) {
			if (tempnode->key < temp->key) {
				if (temp->left!=NULL) 
					temp = temp->left;
				else 
					temp->left = tempnode;
			}
			else if (tempnode->key == temp->key)//�Ѿ����ڽڵ�ֵΪkey�Ľڵ�
				return;
			else {
				if (temp->right!=NULL) 
					temp = temp->right;
				else 
					temp->right = tempnode;
			}
		}
	}
}
