#include<stdio.h>
#include<stdlib.h>
/*
带头结点的循环双链表
*/

/*定义双链表的结点*/
typedef struct Node
{
    int data;
    struct Node *next, *prior;
}Node, * DLList;
// 创建一个结点
Node* newNode(){
    return (Node*)malloc(sizeof(Node));
}
// 初始化一个带头结点的循环双链表
void init(DLList *pList){
    *pList = newNode();
    (*pList)->next = *pList;
    (*pList)->prior = *pList;
}
// 获取双链表的长度
int getLength(DLList list){
    int count = 0;
    Node* p = list->next;
    while(p != list){
        p = p->next;
        count++;
    }
    return count;
}
// 获取双链表的第k个元素
Node* getElem(DLList list, int k){
    if(k < 0 || k > getLength(list)) {
        // printf("获取元素范围溢出%d, length:%d", index, getLength(list));
        return NULL;// 如果范围溢出了
    }
    Node* p = list->next;
    int i = 1;
    while(p != list && i <= k){
        p = p->next;
        i++;
    }
    printf("getElem(k:%d) p:%d\n", k, p->data);
    return p;
}
// 在某个元素的尾部插入一个元素，尾插法
int insertTailInNode(Node* p, int data){
    if(p){
        Node* s = newNode();
        s->data = data;
        // 链接结点
        s->next = p->next; 
        p->next = s;

        s->prior = p;
        s->next->prior = s; 
        printf("p->pr: %d, p->next: %d\n", p->prior->data, p->next->data);
        printf("s->pr: %d, s->next: %d\n", s->prior->data, s->next->data);
        return 1;
    }
    return 0;
}
// 在某个元素的前面插入一个元素，头插法
int insertHeadInNode(Node* p, int data){
    return insertTailInNode(p->prior, data);
}

// 在k的位置插入一个数据，插入成功返回1，失败返回0
int insert(DLList list, int k, int data){
    Node*p = getElem(list, k - 1);
    return insertTailInNode(p, data);
}
// 在双链表尾部插入一个元素
int insertTail(DLList list, int data){
    return insertHeadInNode(list, data);
}
// 在双链表头部插入一个元素
int insertHead(DLList list, int data){
    return insertTailInNode(list, data);
}
// 删除第k个元素
int delete(DLList list, int k){
    Node*p = getElem(list, k - 1);
    if(p){
        Node*s = p->next;// 记录要删除的结点
        // 链接p和s->next结点
        p->next = s->next;
        s->next->prior = p;
        free(s);
        return 1;
    }
    return 0;
}

// 显示循环双链表
void show(DLList list){
    Node*p = list->next;
    while(p != list){
        printf("%d, ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main(){
    
    DLList list;
    init(&list);
    for(int i = 1; i <= 31; i++){
        insert(list, i, i );
    }
    show(list);
    delete(list, 4);
    show(list);

    return 0;
}