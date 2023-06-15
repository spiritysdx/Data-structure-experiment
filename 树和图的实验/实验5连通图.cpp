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
typedef int VRType;
typedef struct{ } InfoType;
typedef enum{DG,DN,UDG,UDN} GraphKind;
typedef char VertexType; 

Status visited[MAX_VERTEX_NUM+1];
Status (*VisitFunc)(char v);

// 弧的定义
typedef struct ArcCell
{   
  VRType  adj; // VRType是顶点关系类型
  InfoType  *info;  // 该弧相关信息的指针
}ArcCell, AdjMatrix[MAX_VERTEX_NUM+1][MAX_VERTEX_NUM+1];


typedef struct MGraph
{ // 图的定义
    VertexType vexs[MAX_VERTEX_NUM+1];//顶点向量
    AdjMatrix arcs;      // 邻接矩阵                     
    int vexnum, arcnum;  // 图的当前顶点数、弧数   
    int IncInfo;         //IncInfo为0,表示各弧无信息
    GraphKind   kind;    // 图的种类标志             
};

//基础操作函数


//查找顶点u位置
int LocateVex(MGraph G,VertexType u)
{
  for(int i=0;i!=G.vexnum;i++)
  {
    if(G.vexs[i] == u)
    {
      return i;
    }
  }
  return 0;
}

//返回第v个节点的值
VertexType GetVex(MGraph G,VertexType v)
{
  if(v>=1 && v<=G.vexnum)
  {
    return G.vexs[v];
  }
  else
  {
    return '\0';
  }
}


//查找第一邻接点序号
int FirstAdjVex(MGraph G,VertexType v)
{
  int k,j,t;
  k = LocateVex(G,v);

  if(k)
  {
    if(G.kind%2) //网
    {
      t = INFINITY;
    }
    else         //图
    {
      t = 0;
    }
    for(j=1;j<=G.vexnum;j++)
    {
      if(G.arcs[k][j].adj != t)
      {
        return j;
      }
    }
  }
  return 0;
}

//查找v相对于w的下一邻接点序号
int NextAdjVex(MGraph G,VertexType v,VertexType w)
{
  int k1,k2,j,t;

  k1 = LocateVex(G,v);
  k2 = LocateVex(G,w);

  if(k1 && k2)
  {
    if(G.kind%2)     //网
    {
      t = INFINITY;
    }
    else             //图
    { 
      t = 0;
    }

    for(j = k2+1;j<=G.vexnum;j++)
    {
      if(G.arcs[k1][j].adj != t)
      {
        return j;
      }
    }
  }
  return 0;
}


//录入弧信息
void InPut(InfoType *info)
{
  //弧信息为空
}

//构造有向图
Status CreateDG(MGraph &G)
{
  cout<<"输入有向图的点数，弧数和信息数(0无1有)："<<endl;
  cin>>G.vexnum>>G.arcnum>>G.IncInfo;
  
  cout<<"输入"<<G.vexnum<<"个点（a b c ……）"<<endl;
  int i,j;
  for(i=1;i<=G.vexnum;++i)
  {
    cin>>G.vexs[i];     //构造顶点向量
  }

  

  for(i=1;i<=G.vexnum;++i)   //初始化邻接矩阵
  {
    for(j=1;j<=G.vexnum;++j)
    {
      G.arcs[i][j].adj = INFINITY;
      G.arcs[i][j].info= NULL;
    }
  }

  VertexType v1,v2;
  int k;
  for(k=1;k<=G.arcnum;k++)
  {
    cout<<"输入构成边的弧尾弧头：\n";
    cin>>v1>>v2;  //输入一条边依附的顶点
    i = LocateVex(G,v1);
    j = LocateVex(G,v2);
    G.arcs[i][j].adj = 1;

    if(G.IncInfo)
    {
      InPut(G.arcs[i][j].info);
    }
  }
  return OK;
}


//构造无向图
Status CreateUDG(MGraph &G)
{
  cout<<"输入无向图的点数，弧数和信息数(0无1有):";
  cin>>G.vexnum>>G.arcnum>>G.IncInfo;

  cout<<"输入"<<G.vexnum<<"个点（a b c ……）"<<endl;
  int i,j;
  for(i=1;i<=G.vexnum;++i)
  {
    cin>>G.vexs[i];     //构造顶点向量
  }

  for(i=1;i<=G.vexnum;++i)//初始化邻接矩阵
  {
    for(j=1;j<=G.vexnum;++j)
    {
      G.arcs[i][j].adj = INFINITY;
      G.arcs[i][j].info= NULL;
    }
  }

  int k;
  VertexType v1,v2;
  for(k=1;k<=G.arcnum;k++)
  {
    cout<<"输入构成边的两个点：(a b )"<<endl;
    cin>>v1>>v2;  //输入一条边依附的顶点及权值

    i = LocateVex(G,v1);
    j = LocateVex(G,v2);
    G.arcs[i][j].adj = 1;

    if(G.IncInfo)
    {
      InPut(G.arcs[i][j].info);
    }

    G.arcs[j][i] = G.arcs[i][j];

  }
  return OK;
}

//重载cin
istream& operator>>(istream& is,GraphKind& k)//重载cin>>G.kind(G.kind为枚举量)
{
    string kind;
    cin>>kind;
    int x;
    if(kind=="DG")
        x=0;
    else if(kind=="UDG")
        x=1;
    switch(x)
    {
        case 0:k=DG;break;
        case 1:k=UDG;break;
    }
    return is;
}

//创建图或表
Status CreateGraph(MGraph &G) 
{ 
  //采用数组（邻接矩阵）表示法，构造图G
  cout<<"输入图G的类型(DG:有向图  UDG:无向图 )"<<endl;;
  cin>>G.kind;
  switch (G.kind) 
  {
    case DG : return CreateDG(G);
    case UDG : return CreateUDG(G);
    default : return ERROR;
  }
}


//访问函数
Status Visit(char v)
{
  cout<<v<<ends;
  return OK;
}


//深度优先搜索遍历

void DFS(MGraph G,int v)
{
    int w;
    visited[v] = TRUE;
    VisitFunc(G.vexs[v]);

    for(w=FirstAdjVex(G,G.vexs[v]);w!=0;w=NextAdjVex(G,G.vexs[v],G.vexs[w]))
    {
      if(!visited[w])
      {
         DFS(G,w);       
      }
    }
}

void DFSTraverse(MGraph G,Status (*Visit)(char v))
{
  int v;
  VisitFunc = Visit;
  for(v=1;v<=G.vexnum;v++)
  {
    visited[v] = FALSE;
  }

  for(v=1;v<=G.vexnum;v++)
  {
    if(!visited[v])
    {
      DFS(G,v);
    }
  }
}


//实验5
void test()
{
  MGraph G;
  bool result = CreateGraph(G);
  if(result)
  {
    cout<<"(连通图)深度优先搜索遍历结果为："<<endl;
    DFSTraverse(G,Visit);
  }
}

int main()
{
  //显示中文
  SetConsoleOutputCP(65001);

  //实验5
  test();

  system("pause");
  return 0;
}
