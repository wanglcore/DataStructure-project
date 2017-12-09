#pragma once
#pragma once
#include<iostream>
#include<ostream>
#include<istream>
#include"Stack.h"
#include"Queue.h"
#include<vector>
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
	vector<Point>vecPath;
	int **mark;
	Point getAdjacentNotVisitedNode(Point p1, Point p2);
	Point offset[4] = { { 1,0 },{ 0,1 },{ 0,-1 },{ -1,0 } };
	void mazepath(Point point, Point p2);
	int rows;
	int cols;
	int **maze;
	Stack<Point>stack;
	vector<Point>shortpath;
	bool findpath(Point p1, Point p2);
	void pushvi(int row, int col) {
		if (maze[row][col] == 0) {
			Point p(row, col);
			ff = true;
			stack.push(p);
		}
	};
	Point offset[4] = { {1,0},{0,1},{0,-1},{-1,0} };
	bool isgo(int prevalue, int x, int y) {
		if (maze[x][y] == -1 || maze[x][y] >= 1) {
			return false;
		}
		return true;
	}
	bool mazepath(Point p1,Point p2);
};
bool Maze::mazepath(Point p1,Point p2) {
	if (p1 == p2) {
		stack.push(p1);
		return true;
	}
	for (int i = 0; i < 4; i++) {
		Point ptemp;
			ptemp.x= p1.x + offset[i].x;
			ptemp.y = p1.y + offset[i].y;
			if (isgo(maze[p1.x][p1.y], ptemp.x, ptemp.y)) {
				maze[ptemp.x][ptemp.y] = maze[p1.x][p1.y];
				stack.push(ptemp);
				if (mazepath(ptemp, p2))
					return true;
				stack.pop();
			}
	}
	return false;
}
istream&operator>>(istream&is, Maze&ma) {//创建迷宫
	cout << "输入迷宫的大小" << endl;
	is >> ma.rows >> ma.cols;
	ma.maze = new int*[ma.rows + 2];
	for (int i = 0; i < ma.rows + 2; i++) {
		ma.maze[i] = new int[ma.cols + 2];
	}
	cout << "输入迷宫" << endl;
	for (int i = 1; i <= ma.rows; i++) {
		for (int j = 1; j <= ma.cols; j++) {
			is >> ma.maze[i][j];
		}
	}
	for (int i = 0; i < ma.rows + 2; i++) {
		ma.maze[i][0] = 1;
		ma.maze[i][ma.cols + 1] = 1;
	}
	for (int j = 0; j < ma.cols + 2; j++) {
		ma.maze[0][j] = 1;
		ma.maze[ma.rows + 1][j] = 1;
	}
	return is;
}
ostream&operator<<(ostream&os, Maze&ma) {//输出迷宫
	for (int i = 1; i <= ma.rows; i++) {
		for (int j = 1; j <= ma.cols; j++) {
			if (ma.maze[i][j] != 0 && ma.maze[i][j] != 3)
				os << ma.maze[i][j] << " ";
			else
				os << " " << " ";
		}
		cout << endl;
	}

	return os;
}
