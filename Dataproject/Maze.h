#pragma once
#include<iostream>
#include"Stack.h"
using namespace std;
struct Point {
	Point(int i = 0, int j = 0) {
		x = i;
		y = j;
	}
	bool operator==(const Point&point)const {
		return x == point.x&&y == point.y;
	}
	int x;
	int y;
};
class Maze {
public:
	bool ff;
	friend ostream&operator<<(ostream&os, Maze&ma);
	friend istream&operator>>(ostream&os, Maze&ma);
	Point offset[4] = { { 0,1 },{ 1,0 },{ 0,-1 },{ -1,0 } };
	int rows;
	int cols;
	int **maze;
	Stack<Point>stack;
	bool findpath(Point p1,Point p2);
	void pushvi(int row, int col) {
		if (maze[row][col] == 0) {
			Point p(row, col);
			ff = true;
			stack.push(p);
		}
	};
};
bool Maze::findpath(Point p1,Point p2) {//Ѱ�Ҵ���ڵ����ڵ�·��
	int row;
	int col;
	Point ptemp;
	if (maze[p1.x][p1.y] == 1 || maze[p2.x][p2.y] == 1)//�����յ㲻��������
		return false;
	int visited = 2;
	while (!(p1==p2)) {//����ǰ�ڵ㲻���յ�ʱ
		ff = false;
		if(!(p1==p2))
		maze[p1.x][p1.y] = visited;
		for (int i = 0; i < 4; i++) {//���ĸ�������Ѱ��ͨ·
			ptemp.x = p1.x + offset[i].x;
			ptemp.y = p1.y + offset[i].y;
			pushvi(ptemp.x, ptemp.y);
			if (ff)//����ҵ�һ��ͨ·��ֹͣ
				break;
		}
		if (stack.empty()) {//���ջ�գ�˵��û���յ�
				cout << "û���ҵ�����" << endl;
				return false;
			}
		else {
			if (ff == false && !(p1 == p2)) {//��ǰ·��ͨ����ԭ·����
				maze[p1.x][p1.y] = 3;
			}
			p1 = stack.pop();
		}
	}
	maze[p2.x][p2.y] = visited;
	cout << "�ҵ�����" << endl;
	return true;
}
istream&operator>>(istream&is, Maze&ma) {//�����Թ�
	cout << "�����Թ��Ĵ�С"<<endl;
	is >> ma.rows >> ma.cols;
	ma.maze = new int*[ma.rows+2];
	for (int i = 0; i < ma.rows+2; i++) {
		ma.maze[i] = new int[ma.cols+2];
	}
	cout << "�����Թ�" << endl;
	for (int i = 1; i <= ma.rows; i++) {
		for (int j = 1; j <= ma.cols; j++) {
			is >> ma.maze[i][j];
		}
	}
	for (int i = 0; i < ma.rows+2; i++) {//���Թ���Χ����һȦһ
		ma.maze[i][0] = 1;
		ma.maze[i][ma.cols+1] = 1;
	}
	for (int j = 0; j < ma.cols+2; j++) {
		ma.maze[0][j] = 1;
		ma.maze[ma.rows + 1][j] = 1;
	}
	return is;
}
ostream&operator<<(ostream&os, Maze&ma) {//����Թ�
	for (int i = 1; i <= ma.rows; i++) {
		for (int j = 1; j <= ma.cols; j++) {
			if (ma.maze[i][j] != 0&&ma.maze[i][j]!=3)
				os << ma.maze[i][j] << " ";
			else
				os << " " << " ";
		}
		cout << endl;
	}
	
	return os;
}
