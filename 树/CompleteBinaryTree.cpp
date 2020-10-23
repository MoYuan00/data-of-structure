#include<stdio.h>
#include<stdlib.h>
/*
    完全二叉树的顺序存储方式
    实现操作
    1. 插入结点到末尾
    2. 顺序显示结点
*/
typedef struct BinaryTree{
    int maxSize;    // 记录二叉树最多能容纳多少个结点
    int size;// 当前容纳了多少个结点
    int* nodes;   // 二叉树的数组
}BTree;

void init(BTree& bTree, int maxSize){// 初始化二叉树
    bTree.maxSize = maxSize;
    bTree.size = 0;
    bTree.nodes = new int[maxSize];
}
bool isEmpty(const BTree tree){// 二叉树是否为空
    return tree.size != 0;
}
void expand(BTree& tree){// 扩张容纳结点数
    if(isEmpty(tree)) return;
    BTree newTree;
    init(newTree, tree.maxSize * 2 + 1);
    for(int i = 0; i < tree.maxSize; i++){
        newTree.nodes[newTree.size] = tree.nodes[i];
        newTree.size++;   
    }
    delete (tree.nodes);
    tree = newTree;
}
/**
 * 插入新结点node到二叉树的末尾（最后一个叶子结点后）
 */
bool insert(BTree& tree, int data){
    if(tree.maxSize == tree.size)// 扩张容量
        expand(tree);
    tree.nodes[tree.size++] = data;
}

bool showNodes(BTree tree){// 显示树的结点
    for(int i = 0; i < tree.size; i++){
        printf("%d, ", tree.nodes[i]);
    }
    printf("\n");
}
int main(){
    BTree tree;
    init(tree, 5);
    for(int i = 1; i <= 90;i++){
        insert(tree, (i * 17) % 31);
    }
    showNodes(tree);
    showNodes(tree);
    return 0;
}