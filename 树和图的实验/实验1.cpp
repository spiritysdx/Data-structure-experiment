//显示中文
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>//用于函数SetConsoleOutputCP(65001);更改cmd编码为utf8
//函数结果状态代码
#define         TRUE            1
#define         FALSE           0
#define          OK             1
#define          ERROR          0   
#define        INFEASIBLE       -1
#define         OVERFLOW        -2
//定义节点数
#define        MAX_TREE_SIZE    100
#include<iostream>
using namespace std;

typedef int Status;
typedef char TElemType;

//定义二叉树结构体
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

//初始化二叉树
Status InitBiTree(BiTree T)
{   
    //含有头结点，头结点的左孩子指向树的根结点, 
    //T为指向头结点的指针
    if (!(T=new BiTNode)) 
    {
        return ERROR;
    }
    T->lchild=NULL; 
    T->rchild=NULL;
    return OK;	 
}

//销毁
Status DestroyBiTree(BiTree &T)
{ 
    if(!T) 
    {
    return FALSE;
    }
    else
    {    
       if (T->lchild!=NULL) 
        {
            DestroyBiTree(T->lchild);
        }
        if (T->rchild!=NULL )
        {
            DestroyBiTree(T->rchild);
        }
        delete T;  
        return OK;  
    }
}

//找根节点
BiTree Root(BiTree T) 
{   
    if (T->lchild==NULL)
    {
        return NULL;
    }
    return T->lchild;
}

//清空
Status ClearBiTree (BiTree &T)
{   
    BiTNode *p;    
    p=T->lchild;
    if (p) 
    {   
        DestroyBiTree(p);
        T->lchild=NULL;      
        T->rchild=NULL;  
    }
    return OK;
}

//查深度
int BiTreeDepth(BiTree T)
{
	if(!T)
    {
	    return 0;
    }
	else
    {
        int deepth = max(BiTreeDepth(T->lchild),BiTreeDepth(T->rchild))+1;
	    return deepth;//空树会返回深度1
    }
}

//打印函数
void visit(TElemType e)
{
    cout<<e;
}


//先序遍历
void PreOrderTraverse(BiTree T, void(*visit)(TElemType))			
{	
    if (T)
    {
        visit(T->data);
        PreOrderTraverse(T->lchild, visit);
        PreOrderTraverse(T->rchild, visit);
    } 
}

//中序遍历

void InOrderTraverse (BiTree T, void(*visit)(TElemType))
{  
    if (T)
    {
       InOrderTraverse(T->lchild, visit);
       visit(T->data);
       InOrderTraverse(T->rchild, visit);
    } 
}

//后序遍历
void PostOrderTraverse (BiTree T, void(*visit)(TElemType))
{  
    if (T)
    {
       PostOrderTraverse(T->lchild, visit);
       PostOrderTraverse(T->rchild, visit);
       visit(T->data);
    } 
}


Status CreateBiTree(BiTree &T)
{
	char ch;
	char kg;
	scanf("%c",&ch);		//	输入数据
	kg=getchar();			//	空格
	
	if(ch == '#')
    {	
        //输入#代表此节点下子树不存数据，不继续递归创建
		T = NULL;

	}
    else
    {
        if(!(T = (BiTNode *)malloc(sizeof(BiTNode))))  exit(OVERFLOW);
		T->data = ch;						//把当前输入的数据存入当前节点指针的data中
        cout<<"请输入"<<ch<<"的左子树: ";
		CreateBiTree(T->lchild);			//递归创建左子树
		cout<<"请输入"<<ch<<"的右子树: ";			
		CreateBiTree(T->rchild);			//到上一级节点的右边递归创建左右子树
	}
    return OK;
}

//实验1
void test()
{
    cout<<"请以先序序列输入该树的树根节点(以#替代空缺)：";
    BiTree T;
    CreateBiTree(T);

    cout<<"先序输出："<<endl;
    PreOrderTraverse(T,*visit);
    cout<<endl;

    cout<<"中序输出："<<endl;
    InOrderTraverse(T,*visit);
    cout<<endl;

    cout<<"后序输出："<<endl;
    PostOrderTraverse(T,*visit);
    cout<<endl;
    
}

int main()
{
    
    //显示中文
    SetConsoleOutputCP(65001);
    

    //AB#C##D##
    test();

    system("pause");
    return 0;
}

