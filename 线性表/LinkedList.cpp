#include<stdio.h>
#include<stdlib.h>
/**
 * 无头结点的单链表的实现 
 * 
 */
typedef struct Node{
    int data;
    struct Node* next;// 指针
    
}Node, *LinkedList;
// 初始化
void Init(LinkedList &list){
    list = NULL;
}
// 尾插法，插入操作
bool Insert(LinkedList& list, int data){
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;
    if(!list){// 如果 头为 NULL，就把数据给头
        list = temp;
    }else{// 头不为NUll，就链接到尾节点
        Node* p = list;
        while(p->next){// 找到尾节点
            p = p->next;
        }
        p->next = temp;// 链接到尾节点
    }   
    return true;
}
// 头插法，插入操作
bool HeadInsert(LinkedList& list, int data){
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    // 将节点链接到头前面，如果头为NULL操作也不会出错
    temp->next = list;
    list = temp;
    return true;
}
// 找到第i个节点
Node* GetElem(LinkedList& list, int index){
    if(index < 1) return NULL;// index无效
    Node* p = list;
    for(int i = 1; i < index && p; i++){// 找到第index个节点，直到p为NULL
        p = p->next;
    }
    return p;// 返回第index个节点，如果index > len返回尾NULL
}
// 删除一个节点
bool Delete(LinkedList& list, int index, int& data){
    if(index <= 0 || !list) return false;
    if(index == 1){// 如果要删除头节点，需要后移头结点然后删除
        Node* del = list;
        list = list->next;// 将头节点后移
        data = del->data;// 记录要删除的值
        free(del);
        return true;
    }
    Node* p = GetElem(list, index - 1);// 获取到要删除的元素
    if(p){// 如果不是NULL
        Node* del = p->next;
        p->next = del->next;
        data = del->data;// 记录要删除的值
        free(del);
        return true;
    }
    return false;
}
// 获取链表长度
int GetLen(LinkedList list){
    int i = 0;
    while(list){
        i++;
        list = list->next;
    }
    return i;
}
// 从头到尾输出链表数据
void Show(LinkedList list){
    printf("长度(%d):  ", GetLen(list));
    while(list){
        printf("%d,", list->data);
        list = list->next;
    }
    printf("\n");
}


int main(){

    
    LinkedList head = (LinkedList)malloc(sizeof(Node));// 创建链表的头结点（也就是创建链表了）
    Init(head);
    Insert(head, 3);
    Insert(head, 4);
    Show(head);
    int x;
    if(Delete(head, 1, x)){
        printf("删除成功!");
    }else{
        printf("删除失败!");
    }
    Show(head);

    Insert(head, 5);
    Insert(head, 6);
    HeadInsert(head, 7);
    Show(head);
    if(Delete(head, 3, x)){
        printf("删除成功!");
    }else{
        printf("删除失败!");
    }
    Show(head);

    system("pause");
    return 0;
}
