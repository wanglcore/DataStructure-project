#include <iostream>
#include <stack>
#include <vector>
using namespace std;
struct Point {
	//行与列
	int row;
	int col;
	Point(int x=0, int y=0) {
		this->row = x;
		this->col = y;
	}
	bool operator!=(const Point& rhs) {
		if (this->row != rhs.row || this->col != rhs.col)
			return true;
		return false;
	}
	bool operator==(const Point& rhs) const {
		if (this->row == rhs.row&&this->col == rhs.col)
			return true;
		return false;
	}
};

class MazeDemo {
public:
	int **maze;
	stack<Point>pointStack;
	vector<Point>vecPath;
	int **mark;
	Point getAdjacentNotVisitedNode(Point p1,Point p2);
	Point offset[4] = {(0,1),(1,0),(0,-1),(-1,0) };
	int rows;
	int cols;
	void mazepath(Point point, Point p2);
};
istream&operator>>(istream&is, MazeDemo&ma) {//创建迷宫
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
	ma.mark = new int*[ma.rows + 2];
	for (int i = 0; i<ma.rows + 2; ++i) {
		ma.mark[i] = new int[ma.cols + 2];
	}
	for (int i = 0; i<ma.rows + 2; ++i) {
		for (int j = 0; j<ma.cols + 2; ++j) {
			ma.mark[i][j] = ma.maze[i][j];
		}
	}
	return is;
}
Point MazeDemo::getAdjacentNotVisitedNode(Point point, Point endp) {
	Point ptemp;
	Point resP(-1, -1);
	for (int i = 0; i < 4; i++) {
		ptemp.row = point.row + offset[i].row;
		ptemp.col = point.col + offset[i].col;
		if (mark[ptemp.row][ptemp.col] == 0 || mark[point.row][point.col] + 1 < mark[ptemp.row][ptemp.col]) {
			resP.row = ptemp.row;
			resP.col = ptemp.col;
			return resP;
		}
	}
	return resP;
}
void MazeDemo::mazepath(Point startP, Point endP) {
	if (startP == endP) {//起点等于终点
		vecPath.push_back(startP);
		return;
	}
	//增加一个终点的已被访问的前驱结点集
	vector<Point> visitedEndPointPreNodeVec;
	//将起点入栈
	pointStack.push(startP);
	mark[startP.row][startP.col] = true;
	//栈不空并且栈顶元素不为结束节点
	while (pointStack.empty() == false) {
		Point adjacentNotVisitedNode = getAdjacentNotVisitedNode(pointStack.top(), endP);
		if (adjacentNotVisitedNode.row == -1) { //没有符合条件的相邻节点
			pointStack.pop(); //回溯到上一个节点
			continue;
		}
		if (adjacentNotVisitedNode == endP) {//以较短的路劲，找到了终点,
			mark[adjacentNotVisitedNode.row][adjacentNotVisitedNode.col] = mark[pointStack.top().row][pointStack.top().col] + 1;
			pointStack.push(endP);
			stack<Point> pointStackTemp = pointStack;
			vecPath.clear();
			while (pointStackTemp.empty() == false) {
				vecPath.push_back(pointStackTemp.top());//这里vecPath存放的是逆序路径
				pointStackTemp.pop();
			}
			pointStack.pop(); //将终点出栈
			continue;
		}
		//入栈并设置访问标志为true
		mark[adjacentNotVisitedNode.row][adjacentNotVisitedNode.col] = mark[pointStack.top().row][pointStack.top().col] + 1;
		pointStack.push(adjacentNotVisitedNode);
	}
}
//int main() {
//	MazeDemo maze;
//	cin >> maze;
//	Point startP(1, 1);
//	Point endP(maze.rows, maze.cols);
//	maze.mazepath(startP, endP);
//	if (maze.vecPath.empty() == true) {
//		cout << " ss" << endl;
//	}
//	else {
//		for (auto i = maze.vecPath.rbegin(); i != maze.vecPath.rend(); i++) {
//			printf("(%d,%d) ", i->row, i->col);
//		}
//	}
//	system("pause");
//}