#include<stdio.h>
#include<stdlib.h>

/**
 *  使用堆实现优先队列
 *      这里使用 优先堆 ，最大堆
 */
class Heap
{
private:
    /* data */
    int maxSize;
    int size;
    int* data;
    void swap(int a, int b){    // 交换下标a和b的元素
        int temp = this->data[a];
        this->data[a] = this->data[b];
        this->data[b] = temp;
    }
    void expand(){              // 扩容
        this->maxSize = (this->maxSize << 1) + 1;
        int* newData = new int[maxSize + 1];
        for(int i = 0; i <= this->size; i++)
            newData[i] = this->data[i];
        delete this->data;// 释放原来的数组空间
        this->data = newData;
    }
    void mend(int index){// 维护某个可能乱序的根元素，“堆化”（将堆调整为根大于孩子）
        if(index < 1) return;
        int k = index << 1;
        if(k <= this->size){
            // 如果有右孩子, 且右孩子大于左孩子
            if(k + 1 <= this->size && this->data[k + 1] > this->data[k])
                k++;
            if(this->data[index] < this->data[k]){// 如果需要交换（根小于其 左右孩子中最大的一个），和其交换
                swap(index, k);
                mend(k);// 交换可能导致 其孩子乱序，堆化孩子
            }
        }
    }
public:
    Heap();
    Heap(int maxSize);
    ~Heap();// 析构函数
    void init(int maxSize);
    bool isEmpty();     // 是否为空
    int getFrist();     // 获取优先级最高的元素
    int pop();          // 获取队顶元素并且删除，并保持优先级有序
    void push(int data); // 添加元素到堆中，并保持优先级有序
};

Heap::Heap()
{
    Heap(10);
}
Heap::Heap(int maxSize)
{
    if(maxSize < 0) throw "you can not init a heap that size below zero";
    init(maxSize);
}
Heap::~Heap()
{
    delete this->data;
}
void Heap::init(int maxSize){
    this->maxSize = maxSize;
    this->size = 0;
    this->data = new int[maxSize + 1];
}
bool Heap::isEmpty(){// 是否为空
    return this->size <= 0;
}     
int Heap::getFrist(){
    if(isEmpty())
        throw "the heap is null, please push some data in it.";
    return this->data[1];
}
int Heap::pop(){
    if(isEmpty())
        throw "the heap is null, please push some data in it.";
    int data = this->getFrist();
    swap(1, this->size);// 取出堆顶与堆底交换，
    this->size--;// 缩小规模
    mend(1);
    return data;
}
void Heap::push(int data){
    if(this->size == this->maxSize)
        this->expand();// 扩容
    this->data[++size] = data;
    int k = this->size;
    // 保证插入后有序
    while(k > 1 && this->data[k] > this->data[k >> 1]){ // 如果结点大于其父结点，那么就交换，直到堆顶
        swap(k, k >> 1);
        k >>= 1;
    }
}

int main(){
    Heap* heap = new Heap(10);
    for(int i = 1; i <= 323; i++)
    {
        heap->push(i * 17 % 331);
    }
    printf("%d \n", heap->getFrist());
    while(!heap->isEmpty()){
        printf("%d,", heap->pop());
    }
    return 0;
}


