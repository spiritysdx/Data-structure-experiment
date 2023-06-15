//显示中文
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>//用于函数SetConsoleOutputCP(65001);更改cmd编码为utf8
#define OK 1
#define ERROR -1
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0
#define STACK_INIT_SIZE  100
#define STACKINCREMENT 10
#define EOF   -1   //C++中需要声明
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

//定义数据类型
typedef char SElemType;
typedef int status;

//定义栈
typedef struct 
{
	SElemType* base;
	SElemType* top;
	int stacksize;
}SqStack;

//初始化
status InitStack(SqStack& S) 
{
	S.base = new SElemType[STACK_INIT_SIZE];
	if (!S.base) return(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

//判栈空
status StackEmpty(SqStack S) 
{
	if (S.top == S.base) return TRUE;
}

//求栈长
status StackLength(SqStack S)
{
	return S.top - S.base;
}

//求栈顶
status GetTop(SqStack S, SElemType& e) 
{
	if (S.top == S.base) return ERROR;
	e = *(S.top - 1);
	return OK;
}

//入栈
status Push(SqStack& S, SElemType e) 
{
	if (S.top - S.base >= S.stacksize) {
		SElemType* newbase = (SElemType*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!newbase) return(OVERFLOW); 
		S.base = newbase;
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	} 
	*S.top++ = e;
	return OK;
}

//出栈
status Pop(SqStack& S, SElemType& e) 
{
	if (S.top == S.base) return ERROR;
	e = *--S.top;
	return OK;
}

//清空栈
status ClearStack(SqStack& S)
{
	S.top = S.base;
	S.stacksize = 0;
	return OK;
}

//销毁栈
status DestroyStack(SqStack& S)
{
	S.top = S.base;
	free(S.base);
	S.base = NULL;
	S.top = NULL;
	return OK;
}

//遍历输出
status PrintStack(SqStack S)
{
	SElemType* p = new SElemType[sizeof(SElemType)];
	p = S.top;
	if (p == S.base)
		cout << "栈空" << endl;
	else
	{
		cout << "有效字符为：" << endl;
		p--;
		while (p != S.base - 1)
		{
			cout << *p;
			p--;
		}
	}
	cout<<endl;
	return OK;
}


//识别判断
void LinkEdit(SqStack& S)
{
	char ch;
	SElemType e;
	ch = getchar();//读取字符，读错误返回EOF
	while (ch != EOF && ch != '\n')//EOF为全文结束符
	{
		switch (ch)
		{
		case '@':// 重置S为空栈
			ClearStack(S);
			break;
		case '#'://栈不空，退栈
			Pop(S, e);
			break;
		default:
			Push(S, ch);
		}
		ch = getchar();//读取下一个字符
	}
}

//实验6
void test()
{
	SqStack S, Q;
	SElemType e;//中间变量
	InitStack(S);
	InitStack(Q);
	while (true)
	{
		cout<<"输入："<<endl;
		LinkEdit(S);//识别
		while (StackLength(S))//如果识别判断后不空
		{
			//正序输出转换
			Pop(S, e);
			Push(Q, e);
		}
		PrintStack(Q);
		ClearStack(Q);
	}
	DestroyStack(S);
	DestroyStack(Q);
}

int main()
{
	//显示中文
    SetConsoleOutputCP(65001);
	
	//实验6
	test();

	system("pause");
	return 0;
}