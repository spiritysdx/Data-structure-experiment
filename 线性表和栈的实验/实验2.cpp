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
//初始空间参数
#define     LIST_INIT_SIZE      100      //线性表的初始存储空间
#define     LISTINCREMENT       10       //线性表的增量空间
#include<iostream>
#include <stdlib.h> 
using namespace std;

//设置状态码和数据类型
typedef int Status;
typedef int ElemType;

//定义顺序表
typedef  struct SqList{
	ElemType   *elem;	     //头指针指向数组首元素
	int		Length;	    //线性表的当前长度
	int		Listsize;	//线性表的当前容量
}; 

//初始化
Status InitList(SqList &L)
{
    //给表分配空间

	L.elem = new ElemType(LIST_INIT_SIZE);

    //判断是否生成
    if(!L.elem)
    {
        return OVERFLOW;
    }
    else
    {
        L.Listsize = LIST_INIT_SIZE;   //表长度为初始值
        L.Length = 0;                  //表默认长度0
        return OK;
    }
};

//销毁
Status DestroyList(SqList &L)
{
    if(L.elem != NULL)//判断表是否已存在
    {
    free(L.elem);
    L.elem = NULL;
    L.Length = 0;
    L.Listsize = 0;
    return OK;
    }
    else
    {
        return ERROR;
    }
}

//判空
bool ListEmpty(SqList L)
{
    if(L.Listsize == 0)//如果顺序表的长度为0，则表为空
    {
        return true;
    }
    else
    {
        return false;
    }
}

//求表长
int ListLength(SqList L)
{
    return L.Length;//返回顺序表表长
}

//比较函数
// bool compare(int p,int e)
// {
//     if(p == e)
//     {
//         return true;
//     }
//     else
//     {
//         return false;
//     }
// }

//查找返回下标
int LocateElem(SqList L,ElemType e)  //bool compare(int p,int e)
{
    /*
    int i = 0;
    while (i<L.Length)
    {
        if(L.elem[i++] == e)
        {
            return i;
        }
    }
    */
    
    int *p,i;
    p = L.elem;
    i = 1;
    while (i <= L.Length && *p++ != e)//后置++高于*
        //int p = L.elem[i++];
        i++;
    if (i > L.Length)
		i = 0;
	return i;
}

//读表元(已经自动转换下标了)
Status GetElem(SqList L,int i,ElemType &e)
{
    if(i<1 || i>ListLength(L))
        return OVERFLOW;
    int *p;
	p = &(L.elem[i-1]);
	e = *p;
    return OK;
    
}

//求前驱
ElemType PriorElem(SqList L,ElemType cur_e,ElemType &pre_e)
{
    if(L.elem != NULL)
        {
        int i = LocateElem(L,cur_e);
        if(i==0 || i ==1)
        {
            pre_e = NULL;
        }
        else
        {
            pre_e = L.elem[i-2];
        }
        return pre_e;
    }
}

//求后继
ElemType NextElem(SqList L,ElemType cur_e,ElemType &next_e)
{
    if(L.elem != NULL)
        {
        int i = LocateElem(L,cur_e);
        if(i==0 || i ==1)
        {
            next_e = NULL;
        }
        else
        {
            next_e = L.elem[i];
        }
        return next_e;
    }
}

//线性表置空
Status ClearList(SqList &L)
{
    if(L.elem != NULL)
    {
        L.Length = 0;
        return OK;
    }
    else
    {
        return ERROR;
    }
}

//赋值
Status PutElem(SqList &L,int i,ElemType &e)
{
    if(L.elem != NULL && !i<1 && !i>ListLength(L))
    {
        L.elem[i] = e;
        return OK;
    }
    else
    {
        return ERROR;
    }
}

//插入元素
Status ListInsert(SqList &L,int i,ElemType e)
{
    //判断是否非法
    if(i<1||i>L.Length+1)
    {
        return OVERFLOW;
    }
    //判断是否满了，如果满动态扩展
	if (L.Length >= L.Listsize)
	{
		//计算新表大小
		int newsize = L.Listsize + LISTINCREMENT;

		//分配新空间
        //ElemType *newbase = new ElemType(newsize);

        int *newbase = (ElemType *)realloc(L.elem,newsize*sizeof(ElemType));

        //已经自动释放原L，并拷贝数据到新空间

		//将原有数据拷贝到该表下
		//(ElemType *)memcpy(newbase,L.elem,newsize);

        //判断是否成功分配
        if(!newbase) exit(OVERFLOW);

		//更新新空间指向
		L.elem = newbase;

		//更新容量
		L.Listsize += LISTINCREMENT;
    }

    /*
    int j;//设置检索，从后往前
    if(L.elem != NULL && !i<1 && !i>ListLength(L)+1)j
    {
        for(j = L.Length-1;j>i-1;j--)//下标从0开始，第几个元素得减1
        {
            L.elem[j+1]=L.elem[j];//从后往前检索，逐个元素后移
        }
        L.elem[i-1]=e;//第i个元素对应下标为i-1的元素
        L.Length++;
        return OK;
    }
    else
    {
        return ERROR;
    }
    */

    int *q,*p;
    q = &L.elem[i-1];//令q指向ai，静态             
    for(p = L.elem+L.Length-1; p>=q ;--p)//下标从0开始，第几个元素得减1
    {
        //从后往前检索，逐个元素后移
        *(p+1) = *p;
    }
    *q = e;
    ++L.Length;
    return OK;
}

//删除元素
Status ListDelete(SqList &L,int i,ElemType &e)
{
    if(i<1||i>L.Length) 
    {
    return ERROR;  //i非法
    }
    ElemType *p=L.elem+i-1;//p为被删除元素的位置
    e=*p;//被删除元素的值赋给e
    ElemType *q=L.elem+L.Length-1;//表尾元素的位置
    for(++p;p<=q;++p)
    {
        *(p-1)=*p;  //左移一位
    }
    L.Length--;    //表长减1
    return OK;
}

//合并两表
Status unionL(SqList &La,SqList Lb) 
{
    int La_len = ListLength(La); // 求各表的长度 
    int Lb_len = ListLength(Lb); 
    int e;  //初始化e 
    for (int i = 1;  i <= Lb_len;  i++) 
    {
        GetElem(Lb,i,e); // 取Lb中第i个数据元素赋给e
        if (!LocateElem(La, e))
        {
        ListInsert(La, ++La_len, e);    
        // La中不存在和 e 相同的数据元素，则插入
        }
    }
    return OK;
}

//非递减有序排列表合并
void merge(SqList La, SqList Lb,SqList &Lc) 
{
    //求表长
    int la_len = ListLength(La);
    int lb_len = ListLength(Lb);

    //初始化存储索引的a，b和位置i，j
    ElemType a,b;
    int i = 1;
    int j = 1;
    int k = 0;

    //比较入表
    while(i <= la_len && j <= lb_len)
    {
        GetElem(La,i,a);
        GetElem(Lb,j,b);

        if(a<b)
        {  
            ListInsert(Lc, ++k, a);
            ++i;
        }
        if(b<a)
        {
            ListInsert(Lc, ++k, b);
            ++j;
        }
    }

    //比较入表后将剩余元素入表
    while(i <= la_len)        //LB已到达表尾，依次将LA的剩余元素插入LC的后面
    {
        GetElem(La,i,a);
        i++;
        ListInsert(Lc, ++k, a);
    }
    while(j <= lb_len)        //LA已到达表尾，依次将LB的剩余元素插入LC的后面
    {
        GetElem(Lb,j,b);
        j++;
        ListInsert(Lc, ++k, b);
    }
    
} 


//实验1
void test01()
{
    SqList La;
    InitList(La);
    int a;
    cout << "顺序表La的5个元素：" << endl;
	for (int j = 0; j < 5; j++)
	{
		cin >> a;
		ListInsert(La, j+1, a);
	}

    SqList Lb;
    InitList(Lb);
    int b;
    cout << "顺序表Lb的5个元素：" << endl;
	for (int k = 0; k < 5; k++)
	{
		cin >> b;
		ListInsert(Lb, k+1, b);
	}

    unionL(La,Lb);
    cout << "La与Lb的并集为：" << endl;
    int l = 0;
	while(l<La.Length)
    {
        cout<<La.elem[l]<<endl;
        l++;
    }
    cout<<"   "<<endl;
    DestroyList(La);
    DestroyList(Lb);
}


//实验2
void test02()
{
    SqList La;
    InitList(La);
    int a;
    cout << "顺序表La的5个元素：" << endl;
	for (int j = 0; j < 5; j++)
	{
		cin >> a;
		ListInsert(La,j+1, a);
	}

    SqList Lb;
    InitList(Lb);
    int b;
    cout << "顺序表Lb的5个元素：" << endl;
	for (int k = 0; k < 5; k++)
	{
		cin >> b;
		ListInsert(Lb, k+1, b);
	}

    SqList Lc;
    InitList(Lc);
    merge(La,Lb,Lc);

    int i = 0;
    cout<<"合并结果Lc为"<<endl;
    while(i<Lc.Length)
    {
    cout<<Lc.elem[i]<<endl;
    i++;
    }
}

int main()
{
    //显示中文
    SetConsoleOutputCP(65001);


    //实验2
    cout<<"实验2"<<endl;
    test02();

    system("pause");
    return 0;
}