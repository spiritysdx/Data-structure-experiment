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
#define  STACK_INIT_SIZE  100    //存储空间初始分配量
#define STACKINCREMENT 10    //存储空间分配增量
#include<iostream>
using namespace std;

//设置状态码和数据类型
typedef int Status;
typedef char SElemType;
typedef struct 
{
	SElemType   	*base;  
    //数组首地址,在栈构造之前和销毁之后，base的值为NULL
	SElemType   	*top;   //栈顶指针
	int     	    stacksize;//当前已分配的存储空间，以元素为单位
}SqStack;

//初始化
Status InitStack(SqStack &S ) 
{
    // 构造一个空的顺序栈 
    S.base=new SElemType[STACK_INIT_SIZE];
    if (!S.base) 
    {
        exit(OVERFLOW);
    } //存储分配失败
    S.top = S.base; //长度为0
    S.stacksize = STACK_INIT_SIZE;//初始存储容量
    return OK;
}

//销毁
Status DestroyStack(SqStack &S)
{
    free(S.base);
    S.top == S.base == NULL;
    S.stacksize = 0;
    return OK;
}

//判栈空
Status StackEmpty(SqStack S)
{
	//若栈空，返回TRUE；否则返回FALSE。
	if(S.top==S.base) 
    {
        return TRUE; //栈空
	}
    else 
    {
    return FALSE;
    }
}

//求栈长
Status LengthStack(SqStack &S)
{
	return (S.top-S.base);//栈顶指针减去栈底指针
}

//清空栈
Status ClearStack(SqStack &S)
{
	S.top=S.base;//让栈顶指针指向栈底位置
	return OK; 
}


//读栈顶
Status GetTop(SqStack S, SElemType &e)
{
//若栈不空，则用e返回S的栈顶元素，并返OK，
//否则返回ERROR
    if(S.top==S.base) 
    {
        return ERROR; //栈空
    }
    e=*(S.top-1);
    return OK;
}



//进栈

//int
Status Push(SqStack &S, SElemType e)
{
//插入元素e为新的栈顶元素		
if(S.top-S.base >= S.stacksize) 
{//栈满，追加空间
    SElemType *newbase=(SElemType *)realloc(S.base, (S.stacksize+STACKINCREMENT)*sizeof(SElemType));
    if(!newbase) exit(OVERFLOW);
    S.base=newbase;
    S.top=S.base+S.stacksize;
    S.stacksize+=STACKINCREMENT; 
} //if
    *S.top++=e;	
    return OK;
}

//出栈
//int
Status Pop(SqStack &S, SElemType &e)
{
//若栈不空，则删除栈顶元素，用e返回其值，并返回OK；
//否则返回ERROR	
    if(S.top==S.base) 
    {
        e = *"$";
        return ERROR;  //栈空
    }
    e=*--S.top; 
    return OK;
}

//括号匹配

//判断左括号函数
Status is_left(char ch)   
{   
	if(ch == '('  || ch=='['  ||  ch=='{' )
    {
		return TRUE;
    }
	else
    {
		return FALSE;
    }
}

//判断右括号函数
Status is_right(char ch)    
{	   
	if(ch == ')' || ch==']' || ch=='}') 
    {
		return TRUE;
    }
	else
    {
		return FALSE;
    }
}

//判断是否配对
Status peidui(char a, char b)
{
	if(a == '(' && b == ')')
    {
        return TRUE;
	}
    else if(a == '[' && b == ']') 
    {
        return TRUE;
    }
    else if(a == '{' && b == '}') 
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

Status match(char *exp)
{
    //检验表达式中所含括弧是否正确嵌套，若是则返回OK,否则返回ERROR 
    SElemType left;
    SqStack S;
    InitStack(S);   //初始化栈S
    char *p=exp;
    char ch = *p;
    //当字符串exp未扫描
    while (ch  != '#' )
    {
        if(is_left(ch))
        {
            Push(S,ch);//左括号进栈
        }
        if(is_right(ch))
        {
            Pop(S,left);
            if(!is_left(left) || left == *"$")
            {
                return FALSE; //缺左括号
            }
            else if(!peidui(left,ch))
            {
                return FALSE; //左右不匹配
            }
        }
        p++;
        ch = *p;
    }
    if(!StackEmpty(S))
    {
        
        return FALSE; //有多余的左括号
    }
    else
    {
        return TRUE;
    }
}

//实验5
void test()
{
    char str[20];
    cout<<"输入括号(#结束):";
    cin>>str;
    bool result = match(str);
    if(result != true)
    {
        cout<<"不匹配";
    }
    else
    {
        cout<<"匹配";
    }
    cout<<endl;
}

int main()
{
    //显示中文
    SetConsoleOutputCP(65001);

    //实验5
    test();


    system("pause");
}