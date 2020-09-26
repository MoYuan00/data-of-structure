/*
带头节点的单链表
*/
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#define ElemType int

typedef struct Node{
    ElemType data;
    struct Node *next;
}Node, *LList;
// 初始化一个带头结点的单链表, 需要修改头节点（所以要传入引用）
void Init(LList& listHead){
    listHead = new Node;
    listHead->next = NULL;
}
// 获取第index个节点
Node* GetElem(LList listHead, int index){
    if(index < 0) return NULL;// 防止无效数据, 
    Node* p = listHead;
    // 找到第index个节点（0为头结点，1是开始节点）
    for(int i = 1; i <= index && p; i++){
        p = p->next;
    }
    return p;// 如果没有找到返回NULL
}
// 插入到第index个上
bool Insert(LList listHead, int index, ElemType data){
    Node* p = GetElem(listHead, index - 1);// 找到第index-1个节点
    if(p) {
        Node*t = new Node;// 创建一个节点并赋值
        t->data = data;
        
        t->next = p->next;// 链接到第 index个
        p->next = t;
        return true;
    }
    return false;
}
// 删除第index个
bool Delete(LList listHead, int index){
    Node* p = GetElem(listHead, index - 1);// 获取要删除的前一个元素
    if(p && p->next){// 如果存在，且要删除的不是NULL
        Node* waste = p->next;
        // 前后链接，删除中间元素链表不会断掉
        p->next = waste->next;
        delete waste;
        return true;
    }
    return false;
}
// 输出链表
void Show(LList listHead){
    listHead = listHead->next;
    while(listHead){
        cout << listHead->data << ",";
        listHead = listHead->next;
    }
    cout << endl;
}
int main()
{
    LList lList = NULL;
    Init(lList);
    // 插入元素
    for(int i = 1; i <= 10; i++){
        Insert(lList, i, i);
    }
    for(int i = 5; i <= 30; i++){
        Insert(lList, i, i);
    }
    Show(lList);
    Delete(lList, 1);
    Delete(lList, 35);
    Show(lList);
    // 删除一些
    for(int i = 4; i <= 45; i++){
        Delete(lList, i);
    }
    Show(lList);

    return 0;
}