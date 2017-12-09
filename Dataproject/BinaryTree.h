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
	void erase(TreeNode<T>*);//删除树
	void visit(TreeNode<T>*tree);//访问节点
	void levelorder(TreeNode<T>*t);//层次遍历
	void preorder(TreeNode<T>*t);//先序遍历
	void inorder(TreeNode<T>*t);//中序遍历
	void postorder(TreeNode<T>*t);//后序遍历
	void insert(const T&key);//向树中插入节点
	bool find(const T&key);//查找节点
	void Delete(const T&key);//删除节点
	void Delete_Node(TreeNode<T>*);//删除同时含有左子树和右子树的节点，被Delete()函数调用
	int height(TreeNode<T>*t);//节点T的高度
	int height() { return height(root); }
	TreeNode<T>* recoustruct(vector<T>preor, vector<T>inor);//已知树的 中序遍历和先序遍历，重构树
	int getsize(TreeNode<T>*t);//树的节点个数
};
template<class T>
int BinaryTree<T>::getsize(TreeNode<T>*t) {//使用递归来计算节点个数
	if (t == NULL)
		return 0;
	return getsize(t->left) + getsize(t->right) + 1;//根为t的树的节点个数为t的左子树的节点个数加上右子树的节点个数+1
}
template<class T>
int BinaryTree<T>::height(TreeNode<T>*t) {
	if (t == NULL)
		return 0;
	int hl = height(t->left);
	int hr = height(t->right);
	return  hl > hr ? ++hl : ++hr;//根为t的树的高度为左子树和右子树中高度高者的高度加一
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
void BinaryTree<T>::inorder(TreeNode<T>*t) {//中序遍历，左子树，根，右子树
	if (t != NULL) {
		inorder(t->left);
		inor.push_back(t->key);
		visit(t);
		inorder(t->right);
	}
}
template<class T>
void BinaryTree<T>::preorder(TreeNode<T>*t) {//先序遍历，根，左子树，右子树
	if (t != NULL) {
		preor.push_back(t->key);
		visit(t);
		preorder(t->left);
		preorder(t->right);
	}
}
template<class T>
void BinaryTree<T>::postorder(TreeNode<T>*t) {//后序遍历，左子树，右子树，根
	if (t != NULL) {
		postorder(t->left);
		postorder(t->right);
		visit(t);
	}
}
template<class T>
void BinaryTree<T>::levelorder(TreeNode<T>*t) {//层次遍历，从上到下，从左到右
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
TreeNode<T>* BinaryTree<T>::recoustruct(vector<T>preor, vector<T>inor) {//二叉树的同构
	vector<T>left_pre, left_in, right_pre, right_in;
	int position = 0;
	int length = inor.size();
	if (length == 0)
		return NULL;
	TreeNode<T>*head = new TreeNode<T>(preor[0]);//先序遍历中第一个元素是二叉树的根
	for (int i = 0; i < length; i++) {
		if (preor[0] == inor[i]) {//在中序遍历中，找到根所在的位置
			position = i;
			break;
		}
	}
	for (int i = 1; i < position + 1; i++) {//根的左边是左子树，根的右边是右子树
		left_pre.push_back(preor[i]);//左子树的先序遍历
		left_in.push_back(inor[i - 1]);//左子树的中序遍历
	}
	for (int i = position + 1; i < length; i++) {
		right_pre.push_back(preor[i]);//右子树的先序遍历
		right_in.push_back(inor[i]);//右紫书的中序遍历
	}
	head->left = recoustruct(left_pre, left_in);//对左子树的先序遍历和中序遍历递归调用该方法
	head->right = recoustruct(right_pre, right_in);//右子树的中序遍历和先序遍历递归调用
	return head;
}
template<class T>
bool BinaryTree<T>::find(const T&key) {//查找特定元素
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
void BinaryTree<T>::Delete_Node(TreeNode<T>*t) {//删除既有左子树又有右子树的节点t
	TreeNode<T>*q = t->right;
	TreeNode<T>*pq = t->right;
	while (q->left) {//找到节点t的右子树中的值最小的树节点
		pq = q;
		q = q->left;
	}
	swap(t->key, q->key);//交换该节点和节点t的值
	pq->left = q->right;//因为该节点一定没有左子树，所以直接使父节点指向该节点的右子树
	delete q;
}
template<class T>
void BinaryTree<T>::Delete(const T&key) {//删除关键字为key的树节点
	TreeNode<T>*p = root;
	TreeNode<T>*t = root;
	while (t->key != key&&t->key!=NULL) {//首先查找值为key的树节点是否存在，如果存在则找到该节点，p为t的父节点
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
	if(t->key==key){		//找到该节点
		if (p->key > t->key) {//要删除的节点是父节点的左子节点
			if (t->right == NULL) {//要删除的节点的右子树为空
				p->left = t->left;
				delete t;
			}
			else if (t->left == NULL) {//要删除的节点的左子树为空
				p->left = t->right;
				delete t;
			}
			else {
				Delete_Node(t);//左右子树都不为空
			}
		}
		else if(p->key<t->key){//要删除的节点是父节点的右子节点
			if (t->left == NULL) {//要删除的节点左子树为空
				p->right = t->right;
				delete t;
			}
			else if (t->right == NULL) {//要删除的节点右子树为空
				p->right = t->left;
				delete t;
			}
			else {
				Delete_Node(t);//要删除的节点同时存在左子树和右子树
			}
		}
		else {//要删除的节点是根节点
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
	if (root == NULL) //根节点为空
		root = new TreeNode<T>(key);
	else {
		TreeNode<T>*tempnode = new TreeNode<T>(key);
		TreeNode<T>*temp = root;//从根节点开始查找可以插入的位置
		while (temp->key) {
			if (tempnode->key < temp->key) {
				if (temp->left!=NULL) 
					temp = temp->left;
				else 
					temp->left = tempnode;
			}
			else if (tempnode->key == temp->key)//已经存在节点值为key的节点
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
