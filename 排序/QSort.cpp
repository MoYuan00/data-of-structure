/*
快速排序
*/
#include<stdio.h>
#include<stdlib.h>
#define ElemType int
#define MAX_SIZE 1000
typedef struct List{
    ElemType data[MAX_SIZE];
    int length;
}ArrayList;

// 划分 - 将区间划分为左右两个部分，左边比右边 （大 or 小）
int _Sort(ArrayList& list, int low, int hight){
    ElemType k = list.data[low]; // 选定low的位置为基准字，也充当了哨兵保存了k的值，也就空出了一个位置用于交换
    while(low < hight){
        // 注意要判断 low < hight
        while(low < hight && list.data[hight] >= k) hight--;
        list.data[low] = list.data[hight];// 将找到小于k的元素放到low 那边
        // （不用担心会覆盖low上的值， 第一次覆盖k（但已经记录为基准字），且覆盖后，hight的位置相当于（空位 保证了low覆盖到hight的成立）
        while(low < hight && list.data[low] <= k) low++;
        list.data[hight] = list.data[low];// 将找到大于k的元素放到hight那边
        // 不用担心覆盖hight的值，hight已经复制到low上（low移动前）
    }
    list.data[low] = k; // 将基准元素放到最终位置上, 此时low == hight
    return low;// 返回基准元素位置，基准元素已经放到最终位置上（有序后的最终位置）
}
// 快速排序
void QuickSort(ArrayList& list, int low, int hight){
    if(low < hight){
        // 划分
        int pivotPos = _Sort(list, low, hight);
        // 对两边进行划分
        QuickSort(list, low, pivotPos - 1);
        QuickSort(list, pivotPos + 1, hight);
    }
}
// 插入到数组尾部
void InsertTail(ArrayList& list, ElemType data){
    if(list.length >= MAX_SIZE) return;
    list.data[++list.length] = data;
}
void Show(ArrayList list){
    for(int i = 1; i <= list.length; i++)
        printf("%d,", list.data[i]);
    printf("\n");
}


int main(){

    ArrayList list;
    list.length = 0;

    // 插入一组无序数列
    for(int i = 1; i <= 33; i++){
        InsertTail(list, i * 17 % 31);
    }
    Show(list);
    QuickSort(list, 1, list.length);
    Show(list);

    return 0;
}