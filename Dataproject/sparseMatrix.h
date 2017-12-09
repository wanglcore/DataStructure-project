#pragma once
#include<iostream>
#include<vector>
#include<iterator>
using namespace std;
template<class T>
struct matrixTerm {
	int col;
	int row;
	T value;
	matrixTerm&operator=(const matrixTerm&matrix) {
		row = matrix.row;
		col = matrix.col;
		value = matrix.value;
		return *this;
	}
};
template<class T>
class sparseMatrix {
	template<class T>
	friend ostream&operator<<(ostream&os, sparseMatrix<T>&matrix);
	friend istream&operator>>(ostream&os, sparseMatrix<T>&matrix);
public:
	void transpose(sparseMatrix<T>&matrix);
	void add(sparseMatrix<T>&matrix, sparseMatrix<T>&matrixs);
public:
	int rows;
	int cols;
	vector<matrixTerm<T>>terms;
};
template<class T>
ostream &operator<<(ostream&os, sparseMatrix<T>&x) {
	os << "row:" << x.rows << " col:" << x.cols << endl;
	os << "nonzero:" << x.terms.size() << endl;
	for (vector<matrixTerm<T>>::iterator i = x.terms.begin(); i != x.terms.end(); i++) {
		os << "a(" << (*i).row << ',' << (*i).col << ")=" << (*i).value << endl;
	}
	return os;
}
template<class T>
istream &operator>>(istream&is, sparseMatrix<T>&x) {
	int numberofterms;
	cout << "enter numbers of rows columns,and length" << endl;
	is >> x.rows >> x.cols >> numberofterms;
	x.terms.resize(numberofterms);
	for (int i = 0; i < numberofterms; i++) {
		cout << "enter row,column,and value" << (i + 1) << endl;
		is >> x.terms[i].row >> x.terms[i].col >> x.terms[i].value;
	}
	return is;
}
template<class T>
void sparseMatrix<T>::transpose(sparseMatrix<T>&b) {
	b.cols = rows;
	b.rows = cols;
	b.terms.resize(terms.size());
	int *colsize = new int[cols + 1];//��¼ÿһ�з���Ԫ�صĸ���
	int *rownext = new int[cols + 1];//ԭ����ÿһ�е�һ������Ԫ�����¾����е�������
	for (int i = 1; i <= cols; i++) {
		colsize[i] = 0;
	}
	for (vector<matrixTerm<T>>::iterator i = terms.begin(); i != terms.end(); i++) {//�����ҳ�ת�ú�ľ���ÿ�з���ĸ�������ת��ǰ��ÿһ���з���ĸ�����
		colsize[(*i).col]++;
	}
	rownext[1] = 0;
	for (int i = 2; i <= cols; i++) {
		rownext[i] = rownext[i - 1] + colsize[i - 1];//��ȡÿһ�з���ֵ����ʼ�±ꡣ
	}
	for (vector<matrixTerm<T>>::iterator i = terms.begin(); i != terms.end(); i++) {
		int j = rownext[(*i).col]++;//�õ���*i��ת�ú��λ��
		b.terms[j].row = (*i).col;
		b.terms[j].col = (*i).row;
		b.terms[j].value = (*i).value;
	}
}
template<class T>
void sparseMatrix<T>::add(sparseMatrix<T>&b, sparseMatrix<T>&c) {
	if (rows != b.rows || cols != b.cols) {
		cout << "��������";
		return;
	}
	c.rows = rows;
	c.cols = cols;
	c.terms.resize(terms.size()+b.terms.size());
	int csize = 0;//���Ա��ʵ�ʳ���
	vector<matrixTerm<T>>::iterator it = terms.begin();
	vector<matrixTerm<T>>::iterator ib = b.terms.begin();
	while (it != terms.end() && ib != b.terms.end()) {
		int tindex = (*it).row*cols + (*it).col;//(*it)�ھ����е�λ��
		int bindex = (*ib).row*cols + (*ib).col;//��*ib���ھ����е�λ��
		if (tindex < bindex) {//it��λ��С��ib��
			c.terms[csize++] = (*it);
			it++;
		}
		else {
			if (tindex == bindex) {//it��ib��λ����ͬ
				if ((*it).value + (*ib).value != 0) {
					(*it).value = (*it).value + (*ib).value;
					c.terms[csize++] = (*it);
				}
				it++;
				ib++;
			}
			else {//ib��λ��С��it
				c.terms[csize++] = (*ib);
				ib++;
			}
		}
	}
	for (; it != terms.end(); it++) {//����ĸ����Ա��л���Ԫ�أ���ֱ��׷�ӵ����Ա���
		c.terms[csize++] = (*it);
	}
	for (; ib != b.terms.end(); ib++) {
		c.terms[csize++] = (*ib);
	}
	c.terms.resize(csize);//�ı����Ա�ĳ��ȡ�
}