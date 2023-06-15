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
//宏常量
#define INFINITY INT_MAX   //最大值∞
#define  MAX_VERTEX_NUM 20   //最大顶点个数
#include<iostream>
using namespace std;


typedef int Status;
typedef int InfoType;
typedef enum{UDG,UDN} GraphKind;
typedef char VertexType; //

//链表中结点的类型 
typedef struct ArcNode 
{  
    int  adjvex;   //该弧所指向的顶点的位置,邻接点位置下标
    struct ArcNode  *nextarc; // 指向下一条弧的指针
    InfoType   *info; // 该弧相关信息的指针
}ArcNode;

//头结点的类型 
typedef struct VNode 
{ 
    VertexType  data;   // 顶点信息
    ArcNode      *firstarc; // 指向第一条依附该顶点的弧
} VNode, AdjList[MAX_VERTEX_NUM];

//图定义
typedef struct 
{  
    AdjList  vertices;//头节点
    int   vexnum, arcnum; //图的当前顶点数和弧数
    GraphKind   kind; // 图的种类标志
} ALGraph;

//邻接表的方式构造无向图
//找到顶点v在邻接表中的位置
int LocateVex(ALGraph G, int v)
{ 
	int i;
	for(i = 1; i<=G.vexnum; i++)
	{
		if(v == G.vertices[i].data)
        {
			return i;
        }
	}
	return ERROR;
}

//建立无向图
Status CreateUDG(ALGraph  &G)
{
    int inf,i,j,k;
    char v1,v2;
    cout<<"输入无向图的点数，弧数:"<<endl;
    cin>>G.vexnum>>G.arcnum;  //inf为0,表示各边无信息
    cout<<"输入"<<G.vexnum<<"个点:（a b c ……）"<<endl;
    for (i=0 ; i< G.vexnum; ++i)   //初始化顶点表
    {
        cin>>G.vertices[i].data;   
        G.vertices[i].firstarc=NULL; 
    }

    for(int k=0;k!=G.arcnum;k++)
    {
        cout<<"输入构成边的两个点：(a b )"<<endl;
        cin>>v1>>v2;
        i=LocateVex(G,v1);
        j=LocateVex(G,v2);

        ArcNode* p1=new ArcNode;
        p1->adjvex=j;
        p1->info = NULL;
        p1->nextarc=G.vertices[i].firstarc;
        G.vertices[i].firstarc=p1;

        ArcNode* p2=new ArcNode;
        p2->adjvex=i;
        p2->info = NULL;
        p2->nextarc=G.vertices[j].firstarc;
        G.vertices[j].firstarc=p2;
    }
    return TRUE;
}

//建立无向网
Status CreateUDN(ALGraph  &G)
{ 
    int inf,i,j,k,w;
    char v1,v2;
    cout<<"输入无向网的点数，弧数和信息数(0无权值1有权值)："<<endl;
    cin>>G. vexnum>>G.arcnum>>inf;  //inf为0,表示各边无信息
    cout<<"输入"<<G.vexnum<<"个点:（a b c ……）"<<endl;
    for (i=0 ; i< G.vexnum; ++i)   //初始化顶点表
    {
        cin>>G.vertices[i].data;   
        G.vertices[i].firstarc=NULL; 
    }

    //构造边表
    for (k=0;k<G.arcnum;k++) 
    { 
        ArcNode* arcn=new ArcNode;
        cout<<"输入两个点和两个点之间的权值：(a b 权值)"<<endl; 
        cin>>v1>>v2>>w;  //输入一条边依附的顶点及权值

        //确定v1,v2在顶点表中的位置
        i=LocateVex(G,v1); 
        j= LocateVex(G,v2);
        arcn->adjvex=j;  //构造边结点
        if (inf)  
        {   
            InfoType* p=new InfoType;  
            *p=w;  
            arcn->info=p;  
        }
        else
        {
            arcn->info = NULL;
        }
        //采用头插法构造边表
        arcn->nextarc = G.vertices[i].firstarc;  
        G. vertices[i].firstarc=arcn;
    } 
    return OK; 
} //CreateUDN   

istream& operator>>(istream& is,GraphKind& k)//重载cin>>G.kind(G.kind为枚举量)
{
    string kind;
    cin>>kind;
    int x;
    if(kind=="UDG")
        x=0;
    else if(kind=="UDN")
        x=1;
    switch(x)
    {
        case 0:k=UDG;break;
        case 1:k=UDN;break;
    }
    return is;
}

Status CreateGraph(ALGraph  &G) 
{ //建立图的邻接表的结构
    cout<<"输入图G的类型(UDG:无向图 UDN:无向网)"<<endl;;
    cin>>G.kind;
    switch (G.kind) 
    {
        case UDG : return CreateUDG(G);
        case UDN : return CreateUDN(G);
        default : return ERROR;
    }
}

//打印函数
void Print(ALGraph G)
{
    ArcNode* p;
    for(int i=0;i<G.vexnum;i++)
    {
        cout<<"下标为"<<i<<"的顶点:"<<G.vertices[i].data;
        p=G.vertices[i].firstarc;
        while(p)
        {
            int temp = p->adjvex;
            cout<<"->邻接点:"<<G.vertices[temp].data;
            if(p->info)
            {
                int w = *p->info;
                cout<<"(权值:"<<w<<")";
            }
            else if(p->info == NULL)
            {
                cout<<"(无权值)";
            }
            else
            {
                
            }
            p=p->nextarc;
        }
        cout<<endl;
    }
}

//实验4
void test()
{
    ALGraph G;
    if(CreateGraph(G))
    {
        Print(G);
    }
}

int main()
{
    //显示中文
    SetConsoleOutputCP(65001);
    
    //实验4
    test();

    system("pause");
    return 0;
}

                    
