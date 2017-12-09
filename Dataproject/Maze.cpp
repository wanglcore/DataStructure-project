#include<iostream>
#include"Stack.h"
#include"maze.h"
int main() {
	Maze ma;
	cin >> ma;
	Point p1(1, 1);
	Point p2(ma.rows, ma.cols);
	ma.findpath(p1,p2);
	cout << ma;
	//cout<<ma.length;
	system("pause");
	return 0;
}