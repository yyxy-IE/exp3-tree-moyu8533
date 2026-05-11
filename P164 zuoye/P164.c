#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTEX_NUM 30    //定义图的最大顶点数量为30
int visited[MAX_VERTEX_NUM]; //定义访问标志数组
typedef char VertexType;     //使用VertexType代表char类型
typedef struct ArcNode      //定义边表结点结构ArcNode
{
    int adjvex;             //定义adjvex域
    struct ArcNode *nextarc;   //定义nextarc域
    int info;               //定义info域
}ArcNode; 
typedef struct VNode        //定义表示头结点结构VNode
{
    VertexType data;        //定义data域
    ArcNode *firstarc;      //定义firstarc域
}VNode;
typedef struct              //定义以邻接表表示法存储的图ALGraph
{
    VNode adjlist[MAX_VERTEX_NUM];  //表示头结点构成的一维数组
    int vexnum,arcnum;              //图的顶点和边数
}ALGraph;
//获取数组为v的顶点在图G中的位置
int LocateVex(ALGraph G,VertexType v)
{
    int i;
    for(i=0;i<G.vexnum;++i)
      if(G.adjlist[i].data==v)
         return i;
    return -1;
}
//创建无向图G
void CreateALGraph(ALGraph *G)
{
    int i,j,k;
    VertexType v1,v2;
    ArcNode *p1,*p2;
    printf("请输入总点数，总边数，以空格隔开:\n");
    scanf("%d %d",&G->vexnum,&G->arcnum);
    printf("\n输入每个顶点的数据,如A \n");
    //创建存放表头结点的一维数组
    for(i=0;i<G->vexnum;++i)
    {
        fflush(stdin);
        printf("请输入第%d个顶点的数据:",i+1);
        scanf("%c",&G->adjlist[i].data);
        G->adjlist[i].firstarc=NULL;
    }
    printf("\n输入边依附的顶点,如A,B\n");
    //创建边表
    for(k=0;k<G->arcnum;++k)
    {
        fflush(stdin);
        printf("请输入第%d条边依附的顶点:",k+1);
        scanf("%c,%c",&v1,&v2);
        i=LocateVex(*G,v1);    //获取数据为v1的顶点在图G中的位置
        j=LocateVex(*G,v2);    //获取数据为v2的顶点在图G中的位置
    //将顶点j作为顶点i的第一个邻接点
    p1=(ArcNode*)malloc(sizeof(ArcNode));
    p1->adjvex=j;
    p1->nextarc=G->adjlist[i].firstarc;
    G->adjlist[j].firstarc=p1;
    //将顶点i作为顶点j的第一个邻接点
    p2=(ArcNode*)malloc(sizeof(ArcNode));
    p2->adjvex=i;
    p2->nextarc=G->adjlist[j].firstarc;
    G->adjlist[j].firstarc=p2;
    }
}
//输出两个顶点之间的路径
void PrintPath(ALGraph G,int *path,int pathLen)
{  //参数path表示存放路径的数组；参数pathLen表示路径长度
   int i;
   for(i=0;i<pathLen;i++)
       printf("%c ",G.adjlist[path[i]].data);
    printf("\n");
}
/* 搜索两个顶点之间所有可能的路径
   参数G表示以邻接表表示法存储的图
   参数start和参数end分别表示开始顶点和结束顶点在图G中的位置
   参数path表示存放路径的数组
   参数pathLen表示路径长度        */
   void FindPaths(ALGraph G,int start,int end,int *path,int pathLen)
   {
    path[pathLen]=start;      //将开始顶点添加到路径数组中
    pathLen++;                //路径长度加1
    if(start==end)            //若开始顶点和结束顶点相同
     PrintPath(G ,path ,pathLen);     //输出路径
    else
    {
        ArcNode *p;
        visited[start]=1;        //将开始顶点标记为已访问
        p=G.adjlist[start].firstarc; //取开始顶点的第一个邻接点
        while (p)                 //若邻接点存在
        {
            if(visited[p->adjvex]==0)    //若邻接点未被访问
            {
                FindPaths(G,p->adjvex,end,path,pathLen);
                             //搜索邻接点和结束顶点之间所有可能的路径
                visited[p->adjvex]=0; //回溯，将邻接点标记为未访问
            }
            p=p->nextarc;       //找下一个邻接点
        }
        
    }
    pathLen--;             //回溯，从路径数组中移除开始顶点
   }
   int main()
   {
    ALGraph G;
    VertexType v1,v2;
    int i,j,v;
    int path[MAX_VERTEX_NUM];
    CreateALGraph(&G);            //创建无向图G
    fflush(stdin);
    printf("请输入要搜索的公交线路的两个顶点:");
    scanf("%c,%c",&v1,&v2);    
    i=LocateVex(G,v1);    //获取数据为v1的顶点在图G中的位置
    j=LocateVex(G,v2);    //获取数据为v2的顶点在图G中的位置
    for(v=0;v<G.vexnum;++v)     //初始化visited数组
     visited[v]=0;
    FindPaths(G,i,j,path,0);  //获取两个顶点之间所有可能的路径
    return 0;
   }


