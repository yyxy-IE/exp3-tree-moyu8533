#include <stdio.h>
#include <stdlib.h>

//定义二叉链表的结点结构BiTNode和指向二叉链表的头指针BiTree
typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
} BiTNode, *BiTree;

int N; // 声明全局变量N，用于存放表达式字符串长度

// 创建以二叉链表形式存储的二叉树
BiTree CreateBiTree(int *nodelist, int position) {
    //参数nodelist表示存储表达式的数组
    //参数position表示结点在数组中的位置
    BiTree p;   //定义新结点
    //若结点为空或当前数组位置超出表达式字符串的长度，则终止程序
    if (position > N || nodelist[position] == 0)  
    return NULL;
    else
    p = (BiTree)malloc(sizeof(BiTNode));          //为新结点分配空间
    p->data = nodelist[position];                 //为新结点添加数据
    p->lchild = CreateBiTree(nodelist, 2 * position);     //递归创建左子树
    p->rchild = CreateBiTree(nodelist, 2 * position + 1);   //递归创建右子树
    return p;                                           //返回以二叉链表形式存储的二叉树
}

// 计算单个表达式的值
int Get_Value(int oper, int oper1, int oper2) { //参数oper表示运算符，参数oper1和oper2分别表示两个操作数
    switch ((char)oper) {                        //根据不同的运算符进行不同的操作
        case '*': return oper1 * oper2;
        case '/': return oper1 / oper2;
        case '+': return oper1 + oper2;
        case '-': return oper1 - oper2;
        default: return 0;
    }
}

// 递归计算表达式的值
int Calculate_PreOrder(BiTree T) {
    int oper1=0;   //表示定义第一操作数的量
    int oper2=0;   //表示定义第二操作数的量
    //若表达式只有数值，则将操作数由字符转换为数字，并作为结果返回
    if (T->lchild == NULL && T->rchild == NULL) {
        return T->data - '0';
    }
    else
    // 计算左子树表达式的值，存入第一操作数变量
     oper1 = Calculate_PreOrder(T->lchild);

    // 计算右子树表达式的值，存入第二操作数变量
     oper2 = Calculate_PreOrder(T->rchild);

    return Get_Value(T->data, oper1, oper2);  //计算单个表达式值
}

// 5. 主函数
int main() {
    BiTree T = NULL;
     int cal_result;
    int nodelist[8] = {0, '*', '+', '-', '1', '2', '6', '3'};
                             //根据二叉树的顺序存储结构定义表达式对应的数组
    N = 7;                   //将表达式的长度赋值为7

    T = CreateBiTree(nodelist, 1);
                              //创建以二叉链表形式存储的二叉树
    cal_result = Calculate_PreOrder(T);  //计算表达式的值

    printf("Using PreOrder logic, Calculate result is [ %d ]\n", cal_result);

    return 0;
}
