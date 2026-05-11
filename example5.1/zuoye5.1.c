#include<stdio.h>
#include<stdlib.h>
//定义二叉链表的结点BiTNode和指向二叉链表的头指针BiTree
typedef struct Node
{
    char data;
    struct Node *lchild, *rchild; 
} BiTNode,*BiTree;
int N;          //声明全局变量N，用于存放二叉树中的结点数量
//创建以二叉链表形式储存的二叉树
BiTree CreateBiTree(char *nodelist,int position)
{//参数nodelist表示字符数组，参数position表示结点在数组中的位置
    BiTree p;  //定义新结点
    //若结点为空或当前数组位置超出二叉树中结点的数量，则终止程序
    if((nodelist[position]=='0')||(position>N))
    return NULL;
    else
    {
        p=(BiTree)malloc(sizeof(BiTNode));
                     //为新结点分配内存空间
       p->data=nodelist[position];
                     //为新结点添加数据
       p->lchild=CreateBiTree(nodelist,2 * position);
                     //递归创建左子树
       p->rchild=CreateBiTree(nodelist,2 * position+1);
                     //递归创建右子树
       return p;     //返回以二叉链表形式储存的二叉树                                                        
    }
}
//统计叶子结点的数量
int Leaves(BiTree bt)
{
    int lcount,rcount;
    if(bt)            //若二叉树非空
    {
        //若结点的左，右孩子为空，则该结点为叶子结点，程序返回1
        if((bt->lchild==NULL) && (bt->rchild==NULL))
        return 1;
        lcount = Leaves(bt->lchild); //计算左子树中叶子结点的数量
        rcount = Leaves(bt->rchild); //计算右子树中叶子结点的数量
        return lcount+rcount;
    }
    else
    return 0;                  //若二叉树为空，则其叶子结点数量为0
}
int main()
{
    int x;                  //二叉树中叶子结点的数量
    BiTree T=NULL;          //初始化空树 
    char nodelist[11]=
             {' ','A','B','C','D','E','0','F','0','G','H'};
                       //根据二叉树的顺序储存结构定义字符数组
    N=10;                   //将结点数量赋值为10
    T=CreateBiTree(nodelist,1);
                       //创建以二叉链表形式存储的二叉树
    x=Leaves(T);                   //统计叶子结点的数量
    printf("二叉树的叶子结点的数量为%d\n",x);
    return 0;
}