#include<iostream>
#include<fstream>
#include<string>
#include"Stack.h"
using namespace std;
const char pri[7][7] = {//优先级表[栈顶][当前]
//	+	-	*	/	(	)	\0
	'>','>','<','<','<','>','>',//+
	'>','>','<','<','<','>','>',//-
	'>','>','>','>','<','>','>',//*
	'>','>','>','>','<','>','>',///
	'<','<','<','<','<','=',' ',//(
	' ',' ',' ',' ',' ',' ',' ',//)
	'<','<','<','<','<',' ','='//\0
};
int optr2rank(char op) { //将操作符转化为数字
	    switch (op) {
		case '+': return 0; //加
		case '-': return 1; //减
		case '*': return 2;//乘
		case '/': return 3; //除
		case '(': return 4; //左括号
		case ')': return 5; //右括号
		case '\0': return 6; //起始符与终止符
		default: exit(-1); //未知运算符
	}
}
char orderbetween(char op1, char op2) {
	return pri[optr2rank(op1)][optr2rank(op2)];//判断运算符的优先级
}
double calcu(double a,char op, double b) {
	switch (op) {
	case '+':
		return a + b;
		break;
	case '-':
		return a - b;
		break;
	case '*':
		return a*b;
		break;
	case '/':
		return a / b;
		break;
	default:exit(-1);
	}
}
double evaluate(const char *str) {
	Stack<double>opnd;//操作数栈
	Stack<char>optr;//操作符栈
	optr.push('\0');
	while (!optr.empty()) {//当操作符栈非空时
		if (isdigit(*str)) {//如果是整数
			opnd.push((int)(*str - '0'));//压入操作数栈
			while (isdigit(*(++str))) {//多位整数
				opnd.push(opnd.pop() * 10 + (int)(*str - '0'));
			}
			if ('.' != *str); //此后非小数点，则意味着当前操作数解析完成
			else {
			float fraction = 1; //否则，意味着还有小数部分
			while (isdigit(*(++str))) //逐位加入
				opnd.push(opnd.pop() + (int)(*str - '0') * (fraction /= 10)); //小数部分
		}
		}
		else {//当前字符是操作符
			switch (orderbetween(optr.top(), *str)) {//比较操作符栈中的头和当前字符的优先级
			case '<'://栈顶的优先级低
				optr.push(*str);//当前的操作符入栈
				str++;
				break;
			case '='://两者的优先级相等，当前字符为右括号，或者是\0
				optr.pop();//去除栈顶元素
				str++;
				break;
			case '>'://栈顶的优先级更高
				char op = optr.pop();//获取栈顶操作符
				double opnd2 = opnd.pop(), opnd1 = opnd.pop();//获取操作数，因为栈先进后出，先出栈的是第二个运算数
				if (op == '/'&&opnd2 == 0) {
					cout << "除数不能为零  ";
					return -1;
				}
				else {
					opnd.push(calcu(opnd1, op, opnd2));//计算
				}
				break;
			}
		}
	}
	return opnd.pop();
}
int main() {
	ifstream fp("D:\\!常用文件夹\\桌面\\compution.txt");
	string str;
	while (getline(fp, str)) {
		//cin >> str;
		const char *s = str.c_str();
		cout << str<<" = ";
		cout << evaluate(s);
		cout << endl;
	}
	system("pause");
	return 0;
}
