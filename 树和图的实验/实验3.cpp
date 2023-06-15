//显示中文
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>//用于函数SetConsoleOutputCP(65001);更改cmd编码为utf8
#include <iostream>
using namespace std;

typedef char dataType;
typedef struct node
{
	dataType data; //根节点的值 
	struct node* left; //左孩子 
	struct node* right; //右孩子 
	int ltag; //左标记，“ltag=0”表示当前节点有左孩子，“ltag=1”表示当前节点没有左孩子 
	int rtag; //右标记，“rtag=0”表示当前节点有右孩子，“rtag=1”表示当前节点没有右孩子 
}BiTree;

BiTree* creat() //二叉树的创建及初始化(初始化左右标记为0) 
{
	dataType value;
	BiTree* t;

	cin >> value;
	

	if (value == '#')
	{
		t = NULL;
	}
	else
	{
		t = new BiTree;
		t->data = value;
		t->ltag = 0;//初始化左标记为0 
		t->rtag = 0;//初始化右标记为0 
		cout<<"请输入"<<t->data<<"的左子树: ";
		t->left = creat();
		cout<<"请输入"<<t->data<<"的右子树: ";
		t->right = creat();
	}
	return t;
}

//BiTree *pre=NULL; v
//1.定义全局变量pre
void InThreaded(BiTree* p)
{
	static BiTree* pre = NULL;//2.定义静态变量 	 
	if (p)
	{
		InThreaded(p->left);

		if (!p->left)
		{
			p->ltag = 1;
			p->left = pre;
		}

		if (pre && !pre->right)
		{
			pre->rtag = 1;
			pre->right = p;
		}
		pre = p;

		InThreaded(p->right);
	}
}

BiTree* Next(BiTree* t) //已知节点t找t的"后继"结点位置 
{
	if (t->rtag == 1) //右标志为1，可以直接得到"后继"结点 
	{
		t = t->right;
	}
	else /*右标志为0，不能直接的到"后继"结点，
		   则需要找到右子树最左下角的节点*/
	{
		t = t->right;
		while (t->ltag == 0)
		{
			t = t->left;
		}
	}
	return t;
}

BiTree* Prior(BiTree* t)//已知节点t找t的"前驱"结点位置 
{
	if (t->ltag == 1)//左标志为1，可以直接找到"前驱"结点的位置 
	{
		t = t->left;
	}
	else /*右标志为0，不能直接的到"前驱"结点，
		   则需要找到左子树最右下角的节点*/
	{
		t = t->left;
		while (t->rtag == 0)
		{
			t = t->right;
		} //while
	} //else

	return t;
}

void InorderTraverse(BiTree* t)
{
	if (!t)
	{
		return;
	}

	while (t->ltag == 0)
	{              
		t = t->left;
	}
	printf("%c ", t->data); 
	while (t->right)
	{               
		t = Next(t);
		printf("%c ", t->data);
	}
}


int main()
{
	//显示中文
    SetConsoleOutputCP(65001);
	
	BiTree* root;

	cout<<"请以先序序列输入该树的根节点(以#替代空缺)：";
	root = creat();
	cout << endl;

	InThreaded(root);
	cout << endl;

	printf("中序遍历:");
	InorderTraverse(root);
	cout << endl;


	system("pause");
	return 0;
}
