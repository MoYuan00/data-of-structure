/*
堆排序

堆排序基于 堆结构（根>左右孩子）,是一颗特殊的完全二叉树
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
    // 在index上插入一个数据，当index不合法或者超过当前数组长度 插入失败，当lenght==maxSize时 数组自动扩容
    bool Insert(int index, int data){
        if(index < 1 || index > length + 1) return false;
        if(length == maxSize){// 需要扩容
            int newSize = maxSize * 2 + 11;// 新数组大小
            int* newArray = new int[newSize];
            // 将旧数组数据拷贝过来
            for(int i = 1; i <= length; i++)
                newArray[i] = array[i];
            free(array);// 释放空间
            array = newArray;// 用新数组取代
            maxSize = newSize;
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
        if(index < 1 || index > length) exit(-1);
        return array[index];
    }
    // 修改第index个元素
    void UpdateElem(int index, int data){
        if(index < 1 || index > length) exit(-1);
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
};
// 比较 根和左右孩子，如果根小于左右，则交换。然后从交换的孩子向下构造。（2.）
// k: 当前根的下标
void build(ArrayList list, int k, int len){
    int t = list.GetElem(k);// 记录当前 打乱堆的根的值
    // 从左孩子找
    for(int i = k * 2; i <= len; i *= 2){
        if(i <= len - 1 && list.GetElem(i) < list.GetElem(i + 1))// 取左右孩子最大的一个
            i++;
        if(t >= list.GetElem(i)) break;// 如果 t大于孩子，跳出
        else{
            list.UpdateElem(k, list.GetElem(i));// 将大的孩子放到根上
            k = i;// 然后继续调整孩子，孩子变成根了
        }
    }
    list.UpdateElem(k, t);// 将打乱堆的元素放到 正确的位置
}
// 堆排序
void HeapSort(ArrayList list){
    // 构造大顶堆（由小到大排序）
    //1.  从最后一个非叶子节点向前构造 
    //2. （每次交换元素可能会破坏孩子的大堆顶，交换后需要对 交换对象的孩子从上向下构造）
    for(int i = list.length / 2; i >= 1; i--){
        build(list, i, list.length);
    }
    // 利用大顶堆排序(空出堆顶位置，堆只有一个时，不用排序)
    for(int i = list.length; i >= 1 + 1; i--){
        list.Swap(1, i);// 不断的将堆顶和 当前堆底交换，将当前最大值放到当前堆的最后（每次放完，堆的规模缩小一）
        build(list, 1, i - 1); // 由于堆顶元素乱了 调整 缩小后的堆
    }
    // 最后数组 由大到小有序
}


int main(){
    ArrayList list;
    // 插入一组无序数
    for(int i = 1; i <= 30; i ++){
        list.Insert(i, i * 17 % 33);
    }
    list.Show();
    HeapSort(list);// 排序
    list.Show();


    return 0;
}