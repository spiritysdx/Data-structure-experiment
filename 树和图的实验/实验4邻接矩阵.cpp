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

// 弧的定义
typedef struct ArcCell
{   
  VRType  adj; // VRType是顶点关系类型
  InfoType  *info;  // 该弧相关信息的指针
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];


typedef struct MGraph
{ // 图的定义
    VertexType vexs[MAX_VERTEX_NUM];//顶点向量
    AdjMatrix arcs;      // 邻接矩阵                     
    int vexnum, arcnum;  // 图的当前顶点数、弧数   
    int IncInfo;         //IncInfo为0,表示各弧无信息
    GraphKind   kind;    // 图的种类标志             
};

//基础操作函数

//清空图或网
void ClearGraph(MGraph &G)
{
  G.vexnum = 0;
  G.arcnum = 0;
  G.IncInfo = 0;
}

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

//对顶点v赋值
Status PutVex(MGraph &G,VertexType v,VertexType value)
{
  int k;
  k = LocateVex(G,v);
  if(k)
  {
    G.vexs[k]=value;
    return OK;
  }
  else
  {
    return ERROR;
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

//插入v邻接点到图
Status InsertVex(MGraph &G,VertexType v)
{
  int i,k,t;

  if(G.vexnum == MAX_VERTEX_NUM)  //顶点已满
  {
    return ERROR;
  }

  if(G.kind%2)             //网
  {
    t = INFINITY;
  }
  else                   //图
  {
    t = 0;
  }

  k = G.vexnum + 1;
  G.vexs[k] = v;

  for(i=1;i<=k;i++)
  {
    G.arcs[i][k].adj = t;
    G.arcs[k][i].adj = t;
  }

  G.vexnum++;
  return OK;
}

//删除顶点v
Status DeleteVex(MGraph &G,VertexType v)
{
  int i,j,k,t;
  
  k = LocateVex(G,v);
  if(!k)
  {
    return ERROR;
  }

  if(G.kind%2)
  {
    t = INFINITY;  //网
  }
  else
  {
    t = 0;        //图
  }
  
  for(i=1;i<=k;i++)
  {
    if(G.arcs[k][i].adj != t)
    {
      G.arcnum--;    //计算新的弧数
    }
  

    if(G.kind == DG || G.kind == DN)  //有向
    {
      if(G.arcs[i][k].adj != t)
      {
        G.arcnum--;
      }
    }
  }

  for(i=1;i<=G.vexnum;i++)
  {
    for(j=k+1;j<=G.vexnum;j++)
    {
      G.arcs[i][k].adj = G.arcs[i][j].adj;
    }
  }

  for(i=k+1;i<=G.vexnum;i++)
  {
    for(j=1;j<=G.vexnum-1;j++)
    {
      G.arcs[i-1][j] = G.arcs[i][j];
    }
  }

  G.vexnum--;
  return OK;
}

//插入弧v,w
/*
Status InsertArc(MGraph &G,VertexType v,VertexType w)
{
  int k1,k2;

  k1 = LocateVex(G,v);
  k2 = LocateVex(G,w);

  if(!k1 || !k2)
  {
    return ERROR;
  }

  G.arcs[k1][k2].adj = adj;
  va_list ap;
  va_start(ap,adj);
  G.arcs[k1][k2].info = va_arg(ap,InfoType);
  va_end(ap);

  if(G.kind == UDG || G.kind == UDN)
  {
    G.arcs[k2][k1] = G.arcs[k1][k2];
  }
  G.arcnum++;
  return OK;
}
*/


//删除弧段v,w
Status DeleteArc(MGraph &G,VertexType v,VertexType w)
{
  int k1,k2;

  k1 = LocateVex(G,v);
  k2 = LocateVex(G,w);

  if(!k1 || !k2)
  {
    return ERROR;
  }
  if(G.kind%2)
  {
    G.arcs[k1][k2].adj = INFINITY;
  }
  else
  {
    G.arcs[k1][k2].adj = 0;
  }

  if(G.kind == UDG || G.kind == UDN)
  {
    G.arcs[k2][k1] = G.arcs[k1][k2];
  }
  G.arcnum--;
  return OK;
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
  
  cout<<"输入"<<G.vexnum<<"个点:（a b c ……）"<<endl;
  int i,j;
  for(i=0;i<G.vexnum;++i)
  {
    cin>>G.vexs[i];     //构造顶点向量
  }

  

  for(i=0;i<G.vexnum;++i)   //初始化邻接矩阵
  {
    for(j=0;j<G.vexnum;++j)
    {
      G.arcs[i][j].adj = INFINITY;
      G.arcs[i][j].info= NULL;
    }
  }

  VertexType v1,v2;
  int k;
  for(k=0;k<G.arcnum;k++)
  {
    cout<<"输入构成边的弧尾弧头："<<endl;
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

//构造有向网
Status CreateDN(MGraph &G)
{
  cout<<"输入有向网的点数，弧数和信息数(0无1有):"<<endl;
  cin>>G.vexnum>>G.arcnum>>G.IncInfo;

  cout<<"输入"<<G.vexnum<<"个点:（a b c ……）"<<endl;
  int i,j;
  for(int i=0;i<G.vexnum;++i)
  {
    cin>>G.vexs[i];
  }
  for(i=0;i<G.vexnum;++i)//初始化邻接矩阵
  {
    for(j=0;j<G.vexnum;++j)
    {
      G.arcs[i][j].adj = INFINITY;
      G.arcs[i][j].info= NULL;
    }
  }

  int k;
  VertexType v1,v2;
  VRType w;
  for(k=1;k<=G.arcnum;k++)
  {
    int w;
    cout<<"输入两个点和两个点之间的权值：(a b 权值)"<<endl;
    cin>>v1>>v2>>w;  //输入一条边依附的顶点及权值

    i = LocateVex(G,v1);
    j = LocateVex(G,v2);
    G.arcs[i][j].adj = w;

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
  cout<<"输入无向图的点数，弧数和信息数(0无1有):"<<endl;
  cin>>G.vexnum>>G.arcnum>>G.IncInfo;

  cout<<"输入"<<G.vexnum<<"个点:（a b c ……）"<<endl;
  int i,j;
  for(i=0;i<G.vexnum;++i)
  {
    cin>>G.vexs[i];     //构造顶点向量
  }

  for(i=0;i<G.vexnum;++i)//初始化邻接矩阵
  {
    for(j=0;j<G.vexnum;++j)
    {
      G.arcs[i][j].adj = INFINITY;
      G.arcs[i][j].info= NULL;
    }
  }

  int k;
  VertexType v1,v2;
  for(k=0;k<G.arcnum;k++)
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

//构造无向网
Status CreateUDN(MGraph &G)//采用邻接矩阵表示法，构造无向网G
{ 
  cout<<"输入无向网的点数，弧数和信息数(0无1有)："<<endl;
  cin>>G.vexnum>>G.arcnum>>G.IncInfo;
  //char kg;
  //kg = getchar();

  cout<<"输入"<<G.vexnum<<"个点:（a b c ……）"<<endl;
  int i,j;
  for (i=0; i<G.vexnum; ++i)
  {
    cin>>G.vexs[i];     //构造顶点向量
  }

  for (i=0; i<G.vexnum; ++i)  //初始化邻接矩阵
  {
    for(j=0; j<G.vexnum; ++j)
    {
      G.arcs[i][j].adj = INFINITY;
      G.arcs[i][j].info= NULL;
    }
  }

  int k;
  VertexType v1,v2;
  VRType w;
  for (k=0;k<G.arcnum;k++) 
  {
    cout<<"输入两个点和两个点之间的权值：(a b 权值)"<<endl; 
    cin>>v1>>v2>>w;  //输入一条边依附的顶点及权值
    i= LocateVex(G,v1); 
    j= LocateVex(G,v2);
    G.arcs[i][j].adj=w;
    if (G.IncInfo)
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
    else if(kind=="DN")
        x=1;
    else if(kind=="UDG")
        x=2;
    else if(kind=="UDN")
        x=3;
    switch(x)
    {
        case 0:k=DG;break;
        case 1:k=DN;break;
        case 2:k=UDG;break;
        case 3:k=UDN;break;
    }
    return is;
}

//创建图或表
Status CreateGraph(MGraph &G) 
{ 
  //采用数组（邻接矩阵）表示法，构造图G
  cout<<"输入图G的类型(DG:有向图 DN:有向网 UDG:无向图 UDN:无向网)"<<endl;;
  cin>>G.kind;
  switch (G.kind) 
  {
    case DG : return CreateDG(G);
    case DN : return CreateDN(G);
    case UDG : return CreateUDG(G);
    case UDN : return CreateUDN(G);
    default : return ERROR;
  }
}

//打印函数
void Print(MGraph G)//输出图G的邻接矩阵
{
  cout<<"图的类型为"<<G.kind<<endl;
    for(int i=0;i!=G.vexnum;i++)
    {
      for(int j=0;j!=G.vexnum;j++)
      {
        if(G.arcs[i][j].adj != INFINITY)
        {
          cout<<G.arcs[i][j].adj<<'\t';
        }
        else
        {
          cout<<"∞"<<'\t';
        }
      }
      cout<<endl;
    }
}



//实验4
void test()
{
  MGraph G;
  bool result = CreateGraph(G);
  if(result)
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




