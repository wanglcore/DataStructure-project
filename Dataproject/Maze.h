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
bool Maze::findpath(Point p1,Point p2) {//寻找从入口到出口的路径
	int row;
	int col;
	Point ptemp;
	if (maze[p1.x][p1.y] == 1 || maze[p2.x][p2.y] == 1)//起点和终点不满足条件
		return false;
	int visited = 2;
	while (!(p1==p2)) {//当当前节点不是终点时
		ff = false;
		if(!(p1==p2))
		maze[p1.x][p1.y] = visited;
		for (int i = 0; i < 4; i++) {//在四个方向上寻找通路
			ptemp.x = p1.x + offset[i].x;
			ptemp.y = p1.y + offset[i].y;
			pushvi(ptemp.x, ptemp.y);
			if (ff)//如果找到一个通路，停止
				break;
		}
		if (stack.empty()) {//如果栈空，说明没到终点
				cout << "没有找到出口" << endl;
				return false;
			}
		else {
			if (ff == false && !(p1 == p2)) {//当前路不通，沿原路返回
				maze[p1.x][p1.y] = 3;
			}
			p1 = stack.pop();
		}
	}
	maze[p2.x][p2.y] = visited;
	cout << "找到出口" << endl;
	return true;
}
istream&operator>>(istream&is, Maze&ma) {//创建迷宫
	cout << "输入迷宫的大小"<<endl;
	is >> ma.rows >> ma.cols;
	ma.maze = new int*[ma.rows+2];
	for (int i = 0; i < ma.rows+2; i++) {
		ma.maze[i] = new int[ma.cols+2];
	}
	cout << "输入迷宫" << endl;
	for (int i = 1; i <= ma.rows; i++) {
		for (int j = 1; j <= ma.cols; j++) {
			is >> ma.maze[i][j];
		}
	}
	for (int i = 0; i < ma.rows+2; i++) {//在迷宫周围加上一圈一
		ma.maze[i][0] = 1;
		ma.maze[i][ma.cols+1] = 1;
	}
	for (int j = 0; j < ma.cols+2; j++) {
		ma.maze[0][j] = 1;
		ma.maze[ma.rows + 1][j] = 1;
	}
	return is;
}
ostream&operator<<(ostream&os, Maze&ma) {//输出迷宫
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
