/*
动态分配的顺序存储结构的线性表实现
*/
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define ElemType int
using namespace std;

typedef struct List{
    ElemType* data;// 指针，可以指向一片连续的空间
    int mSize;// 最大容量
    int len;// 当前使用容量
}List;
// 初始化一个 动态分配的顺序表, 长度为mSize+1, 0下标不使用
void Init(List& list, int mSize){
    list.data = new ElemType[mSize + 1];
    list.len = 0;
}
// 在index个位置上插入一个元素
bool Insert(List& list, int index, ElemType data){
    if(index < 1 || index > list.len + 1) return false; // 防止溢出
    if(list.len == list.mSize){// 如果已经存满了，则将容器扩大
        int newSize = list.mSize * 2 + 17;
        ElemType* data = new ElemType[newSize];// 创建一个更大的容器
        for(int i = 1; i <= list.len; i++){// 将数据拷贝过去
            data[i] = list.data[i];
        }
        delete list.data;// 释放久容器空间
        list.data = data;// 获得新容器
        list.mSize = newSize;
    }
    for(int i = list.len + 1; i >= index; i--){// 从后向前，将元素后移
        list.data[i + 1] = list.data[i];
    }
    list.data[index] = data;// 赋值
    list.len++;// 长度加1
    return true;
}
// 删除第index个位置上的一个元素
bool Delete(List& list, int index){
    if(index < 1 || index > list.len) return false;// 防止溢出
    for(int i = index; i <= list.len - 1; i++){// 从前向后，将元素前移
        list.data[i] = list.data[i + 1];
    }
    list.len--;// 长度减1
    return true;
}
// 显示链表
void Show(List list){
    for(int i = 1; i <= list.len; i++){
        cout << list.data[i] << ",";
    }
    cout << endl;
}



int main(){

    List list;
    // 初始化一个 顺序表
    Init(list, 60);
    // 插入一些数据
    for(int i = 1; i <= 100; i++){
        Insert(list, i, i);
    }
    Show(list);
    // 删除最前端的一些元素
    for(int i = 1; i <= 20; i++){
        Delete(list, 1);
    }
    Show(list);
    // 删除最后的一些元素
    for(int i = 21; i <= 30; i++){
        Delete(list, list.len);
    }
    Show(list);

    return 0;
}