#include<iostream>
#include<fstream>
#include<string>
#include"MinHeap.h"
template<class T>
struct Node {
	T element;
	Node<T>*left;
	Node<T>*right;
	Node() { left = right = NULL; }
	Node(const T&theele) :element(theele) {
		left = right = NULL;
	}
	Node(const T&ele, Node*theleft, Node*theright) :element(ele) {
		left = theleft;
		right = theright;
	}
};
template<class T>
class BinaryTree {
public:
	Node<T>*root;
	int size;
	BinaryTree() {
		root = NULL;
		size = 0;
	}
	~BinaryTree() {};
	string str="";
	void makeTree(const T&ele, BinaryTree<T>&, BinaryTree<T>&);
	void visit(Node<T>*t) { if (t->element != 0)cout << t->element  << " "<<this->str << endl; }
	void postorder(Node<T>*t) {
		if (t->left != NULL) {
			str += "0";
			postorder(t->left);
		}
		if (t->right != NULL) {
			str += "1";
			postorder(t->right);
			str = str.substr(0, str.size() - 1);
			return;
		}
		else {
			cout << t->element << " " << str << endl;
			str = str.substr(0, str.size() - 1);
			return;
		}
	}
};
template<class T>
void BinaryTree<T>::makeTree(const T&ele, BinaryTree<T>&left, BinaryTree<T>&right) {
	root = new Node<T>(ele, left.root, right.root);
	size = left.size + right.size + 1;
	left.root = right.root = NULL;
	left.size = right.size = 0;
}
template<class T>
struct HuffmanNode {
	BinaryTree<T>*tree;
	T w;
	operator T()const { return w; }
};
template<class T>
BinaryTree<T>*huffmanTree(T ele[],int w[], int n) {
	HuffmanNode<T>*hnode = new HuffmanNode<T>[n + 1];
	BinaryTree<T>emptyTree;
	for (int i = 0; i <= n; i++) {
		if (w[i] != 0) {
			hnode[i].w = w[i];
			hnode[i].tree = new BinaryTree<T>;
			hnode[i].tree->makeTree(ele[i], emptyTree, emptyTree);
		}
	}
	MinHeap<HuffmanNode<T>>heap[1];
	heap->initialize(hnode, n);
	HuffmanNode<T>x, y, z;
	BinaryTree<T>*t;
	for (int i = 1; i < n; i++) {
		x = heap->top();
		heap->pop();
		y = heap->top();
		heap->pop();
		t = new BinaryTree<T>;
		t->makeTree(0, *x.tree, *y.tree);
		z.w = x.w + y.w;
		z.tree = t;
		heap->push(z);
		delete x.tree;
		delete y.tree;
	}
	return heap->top().tree;
}
int main() {
	int a[7] = { 0,2,3,4,4,5,7 };
	char b[7] = { '0','f','o','r','g','e','t' };
	BinaryTree<char>*x = huffmanTree(b, a, 6);
	x->postorder(x->root);
	system("pause");
	return 0;
}
