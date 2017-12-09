#include<iostream>
#include<fstream>
#include<string>
#include"Stack.h"
using namespace std;
const char pri[7][7] = {//���ȼ���[ջ��][��ǰ]
//	+	-	*	/	(	)	\0
	'>','>','<','<','<','>','>',//+
	'>','>','<','<','<','>','>',//-
	'>','>','>','>','<','>','>',//*
	'>','>','>','>','<','>','>',///
	'<','<','<','<','<','=',' ',//(
	' ',' ',' ',' ',' ',' ',' ',//)
	'<','<','<','<','<',' ','='//\0
};
int optr2rank(char op) { //��������ת��Ϊ����
	    switch (op) {
		case '+': return 0; //��
		case '-': return 1; //��
		case '*': return 2;//��
		case '/': return 3; //��
		case '(': return 4; //������
		case ')': return 5; //������
		case '\0': return 6; //��ʼ������ֹ��
		default: exit(-1); //δ֪�����
	}
}
char orderbetween(char op1, char op2) {
	return pri[optr2rank(op1)][optr2rank(op2)];//�ж�����������ȼ�
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
	Stack<double>opnd;//������ջ
	Stack<char>optr;//������ջ
	optr.push('\0');
	while (!optr.empty()) {//��������ջ�ǿ�ʱ
		if (isdigit(*str)) {//���������
			opnd.push((int)(*str - '0'));//ѹ�������ջ
			while (isdigit(*(++str))) {//��λ����
				opnd.push(opnd.pop() * 10 + (int)(*str - '0'));
			}
			if ('.' != *str); //�˺��С���㣬����ζ�ŵ�ǰ�������������
			else {
			float fraction = 1; //������ζ�Ż���С������
			while (isdigit(*(++str))) //��λ����
				opnd.push(opnd.pop() + (int)(*str - '0') * (fraction /= 10)); //С������
		}
		}
		else {//��ǰ�ַ��ǲ�����
			switch (orderbetween(optr.top(), *str)) {//�Ƚϲ�����ջ�е�ͷ�͵�ǰ�ַ������ȼ�
			case '<'://ջ�������ȼ���
				optr.push(*str);//��ǰ�Ĳ�������ջ
				str++;
				break;
			case '='://���ߵ����ȼ���ȣ���ǰ�ַ�Ϊ�����ţ�������\0
				optr.pop();//ȥ��ջ��Ԫ��
				str++;
				break;
			case '>'://ջ�������ȼ�����
				char op = optr.pop();//��ȡջ��������
				double opnd2 = opnd.pop(), opnd1 = opnd.pop();//��ȡ����������Ϊջ�Ƚ�������ȳ�ջ���ǵڶ���������
				if (op == '/'&&opnd2 == 0) {
					cout << "��������Ϊ��  ";
					return -1;
				}
				else {
					opnd.push(calcu(opnd1, op, opnd2));//����
				}
				break;
			}
		}
	}
	return opnd.pop();
}
int main() {
	ifstream fp("D:\\!�����ļ���\\����\\compution.txt");
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
