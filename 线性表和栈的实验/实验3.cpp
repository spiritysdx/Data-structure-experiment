//显示中文
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>//用于函数SetConsoleOutputCP(65001);更改cmd编码为utf8
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#include<iostream>
using  namespace std;

typedef int ElemType;
typedef int status;

//创建节点结构体
typedef struct LNode 
{
	ElemType   data;
	struct  LNode *next;
}LNode, *LinkList;

//初始化
status InitList(LinkList&L) 
{
	L = new LNode;
	if (!L) exit(OVERFLOW);
	L->next = NULL;
	return OK;
}

//
status Getelem(LinkList L, int i, ElemType&e)
{
	LNode *p; int j;
	p = L->next; j = 1;
	while (p&&j < 1)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i)return ERROR;
	e = p->data;
	return OK;
}

void Tail_Insert(LinkList &L)
{
	int e;
	LNode *p, *s;
	L = new LNode;
	L->next = NULL;//定义头结点
	p = L;         //p是L的尾指针
	cout<<"请输入节点(输入0结束并输出结果)："<<endl;
	cin >> e;      //从键盘输入一个结点
	while (e != 0) 
	{
		s = new LNode;
		s->data = e;
		s->next = NULL;
		p->next = s;//插入链表
		p = s;		//更新尾指针
		cin >> e;   //继续读
	}
}

//打印
void PrintList(LinkList L)
{
	LinkList tem = L;
	while (tem->next != NULL)
	{
		tem = tem->next;
		cout << tem->data << " ";
	}
}

//实验3
void test()
{
	LinkList L;
	Tail_Insert(L);
	cout << "输出：";
	PrintList(L);
	cout<<endl;
}

int main()
{
	//显示中文
    SetConsoleOutputCP(65001);
	
	//实验3
	test();
	
	system("pause");
	return 0;
}