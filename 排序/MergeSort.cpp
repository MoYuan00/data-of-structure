/*
2路 归并排序
使用了分而治之的思想

将数列分为左右两块，
然后分别对左右两块进行划分，然后归并
重复以上步奏

用树的遍历算法来描述，也就是采用了树的后序遍历（左，右，根）
*/
#include<stdio.h>
#include<stdlib.h>

// 构造一个方便好用的顺序表
class ArrayList{
    private:
    int* array = NULL;
    int maxSize;
    public:
    int length;
    public:
    ArrayList(){
        maxSize = 10;
        length = 0;
        array = new int[maxSize];
    }
    // 调整容量
    void SetCapacity(int capacity){
        int newCapacity = capacity + 1;
        int len = newCapacity > length ? length : newCapacity;// 取容量和长度的最小值，将这个长度的值拷贝过来
        int* newArray = new int[newCapacity];
        // 将旧数组数据拷贝过来
        for(int i = 1; i <= len; i++)
            newArray[i] = array[i];
        free(array);// 释放空间
        array = newArray;// 用新数组取代
        maxSize = newCapacity;
        length = len;// 如果容量比数组小，那么长度会缩短。
    }
    // 在index上插入一个数据，当index不合法或者超过当前数组长度 插入失败，当lenght==maxSize时 数组自动扩容
    bool Insert(int index, int data){
        if(index < 1 || index > length + 1) return false;
        if(length == maxSize){// 需要扩容
            int newSize = maxSize * 2 + 11;// 新数组大小
           SetCapacity(newSize);
        }
        for(int i = length; i >= index; i--){//从后向前 将index及以后的数组内容后移
            array[i + 1] = array[i];
        }
        array[index] = data;// 将数据放到index上
        length++;
        return true;
    }   
    // 获取第index个元素
    int GetElem(int index){
        if(index < 1 || index > length) {
            printf("获取范围溢出%d", index);
            exit(-1);
        }
        return array[index];
    }
    // 修改第index个元素
    void UpdateElem(int index, int data){
        if(index < 1 || index > length) {
            printf("修改范围溢出%d", index);
            exit(-1);
        }
        array[index] = data;
    }
    // 交换下标为a和b的值
    void Swap(int a, int b){
        if(a < 1 || a > length || b < 1 || b > length) return;
        if(a == b) return;// 无需交换
        int temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }
    // 删除index上的一个元素
    bool Delete(int index){
        if(index < 1 || index > length) false;
        for(int i = index; i <= length - 1; i++){// 从前向后 将index以后的数组内容前移
            array[i] = array[i];
        }
        length--;
        return true;
    }
    // 显示当前顺序表的内容
    void Show(){
        for(int i = 1; i <= length; i++){
            printf("%d, ", array[i]);
        }
        printf("\n");
    }
};// 顺序表代码 end

// 将左右两块（已经有序）合并成一个有序序列
// 需要一个辅助数组
// 参数: 原数组，辅助数组，起始下标，和分块下标（两块数组的分割），终止下标
// 左边块为[low,mid],右边块为[mid + 1, hight]
void Merge(ArrayList& list, ArrayList& tempList, int low, int mid, int high){
    // 将数组元素全部拷贝到 辅助数组中
    for(int i = low; i <= high; i++)
        tempList.UpdateElem(i, list.GetElem(i));
    // 记录左边块，右边块 处理到哪了，还有元素组当前填充到哪了
    int i = low, j = mid + 1, k = low;
    while(i <= mid && j <= high){
        // 将小的先放入
        if(tempList.GetElem(i) <= tempList.GetElem(j)){
            list.UpdateElem(k++, tempList.GetElem(i++));
        }else{
            list.UpdateElem(k++, tempList.GetElem(j++));
        }
    }
    // 有可能一边空了，一边还有剩余，处理它
    while(i <= mid)
        list.UpdateElem(k++, tempList.GetElem(i++));
    while(j <= high)
        list.UpdateElem(k++, tempList.GetElem(j++));
    // 合并完成
}
// 归并排序
// 原数组，辅助数组,当前归并段的起始，终止下标
void MergeSort(ArrayList& list, ArrayList& tempList, int low, int high){
    if(low < high){
        // 后序遍历
        int mid = (low + high) / 2;
        MergeSort(list, tempList, low, mid);
        MergeSort(list, tempList, mid + 1, high);
        // 合并当左右两段，由于是后序遍历，那么左右两段一定是各自有序的
        Merge(list, tempList, low, mid, high);
    }
}

int main(){

    ArrayList list;
    ArrayList tempList;
    // 插入一组无序数
    for(int i = 1; i <= 33; i ++){
        list.Insert(i, (i * 17) % 31);
    }
    list.Show();
    // 确保辅助数组能够容纳 下原数组（长度，相同）
    tempList.SetCapacity(list.length);
    tempList.length = list.length;
    MergeSort(list, tempList, 1, list.length);// 排序
    list.Show();

    return 0;
}



