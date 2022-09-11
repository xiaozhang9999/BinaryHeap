# BinaryHeap
# 优先队列
优先队列：出队顺序和入队顺序无关，和优先级相关。
几个使用场景：
1.操作系统中的任务调度，资源分配；动态选择优先级最高的任务执行。
2.游戏中的AI，面对不同敌人时优先选择优先级高的攻击，动态处理。
优先队列可以复用队列接口，也可以使用不同的底层实现。
|  | 入队 |出队(取出最大元素)|
|--|--|--|
| 普通线性结构 |  O(1)|O(n)|
|顺序线性结构|O(n)|O(1)|
|堆|O(logn)|O(logn)|

不同结构下，优先队列入队出队的时间复杂度。使用堆结构更加高效。
堆的本质是树，二叉堆是满足特殊性质的二叉树。
## 二叉堆BinaryHeap

 - 是一颗完全二叉树；
 - （最大堆）堆中某节点的值总不大于其父节点的值（节点值总大于其左右孩子树所有节点的值）；
 - （最小堆）堆中某节点的值总不小于其父节点的值（节点值总小于其左右孩子树所有节点的值）；

但层次低的节点值不一定都小于（大于）上层节点的值。
### 用数组存储二叉堆
若实现最大堆，对于节点i可知

> parent(i)=i/2;
> lchild(i)=2*i;
> rchild(i)=2*i+1;

因为数组标号从0开始，所以索引发生偏移。
> parent(i)=(i-1)/2;
> lchild(i)=2*i+1;
> rchild(i)=2*i+2;

这样数组数据满足二叉堆性质。用vector向量动态数组存储数据。
```c++
#include<iostream>
using namespace std;
#include<vector>
#include<string>
template<typename T>
class MaxHeap
{
public:
	MaxHeap() {};
	MaxHeap(T arr[],int length);//heapify将数组整理成堆的形状
	~MaxHeap() {};
	int size() { return data.size(); }//堆中元素个数
	bool empty() { return data.empty(); };//堆是否为空
	int parent(int index);//返回节点的父亲索引
	int leftChild(int index);//返回节点的左孩子索引
	int rightChild(int index);//返回节点的右孩子索引
	void add(T e);//添加一个新元素
	void SiftUp(int k);//将索引为k的元素上调至合适位置
	T extractMax();//取出最大的元素并返回
	void SiftDown(int k);//将换到根节点的元素下沉至合适位置
	void replace(T e);//取出最大元素，放入一个新元素
	string to_string();//字符串输出
private:
	vector<T> data;
};
```
求父节点与左右孩子节点
```c++
template<typename T>
int MaxHeap<T>::parent(int index)
{
	if (index == 0)
		throw "index-0 doesn't have parent.";
	return (index - 1) / 2;
}

template<typename T>
int MaxHeap<T>::leftChild(int index)
{
	return 2 * index + 1;
}

template<typename T>
int MaxHeap<T>::rightChild(int index)
{
	return 2 * index + 2;
}
```
### 向堆中添加元素和SiftUp
添加元素只需要调用函数在数组末尾添加一个新元素，SiftUp是将元素在堆中上调到合适位置满足最大堆性质。
将新添加元素与自身节点的父节点元素比较若前者大则二者交换，直到父节点元素更大或者到达堆的根节点。
```c++
template<typename T>
void MaxHeap<T>::add(T e)
{
	data.push_back(e);//在data中末尾添加元素e
	SiftUp(data.size() - 1);//将元素调整至合适位置
}

template<typename T>
void MaxHeap<T>::SiftUp(int k)
{
	while (k > 0 && data.at(parent(k)) < data.at(k)) {
		swap(data[parent(k)], data[k]);
		k = parent(k);
	}
}
```
### 在堆中取出元素（只能取出最大元素）和SiftDown
最大元素就是堆的根节点元素对应也是数组中索引为0的元素。
将数组中第一个元素与最后一个元素交换，然后取出最后一个元素，此时根节点不符合条件，将根节点下沉到合适位置，找出节点左右孩子中最大的，若节点小于孩子则交换，直到合适位置。
```c++
template<typename T>
T MaxHeap<T>::extractMax()
{
	if (data.empty())
		throw "the data is empty!";//数组为空时无法取出元素
	T ret = data.front();//data中第一个元素，也是最大的元素
	//将数组第一个与最后一个元素交换
	swap(data.front(), data.back());
	//删除最大的元素，此时在数组最末尾
	data.pop_back();
	//调整堆
	SiftDown(0);
	return ret;
}

template<typename T>
void MaxHeap<T>::SiftDown(int k)
{
	while (leftChild(k) < data.size()) {
		int j = leftChild(k);
		if (j + 1 < data.size() && data[j] < data[j + 1]) {//若k有右孩子并且右孩子值大于左孩子
			j = j + 1;//则令j等于右孩子的索引
		}
		//最终j为左右孩子中值最大的元素中的索引
		if (data[k] >= data[j])
			break;//此时已到合适位置，循环终止
		//交换k与j
		swap(data[k], data[j]);
		k = j;
	}
}
```
添加，取出的时间复杂度都为$O(logn)$,最差情况也为$O(logn)$。
## 堆排序
简单实现就是将data[]中数据添加到定义的堆heap中，从heap中依次取出最大值，添加到data[]中，得到的data就是有序的。这种方法用到了多余的空间，与之前的归并，快速排序相比性能差一些。
```c++
//利用堆给数组排序
template<typename T>
void HeapSort(T data[],int length)
{
	MaxHeap<T> heap;
	for (int j=0;j<length;j++) 
		heap.add(data[j]);

	for (int i = length - 1; i >= 0; i--) 
		data[i] = heap.extractMax();
}
```
### replace
取出最大元素后放入一个新元素。
可以先extractMax，再add，相当于两次O(logn);
另一种方法，将最大元素替换为新元素，再SiftDown，只有一次O(logn)。
```c++
template<typename T>
void MaxHeap<T>::replace(T e)
{
	if (empty())
		throw "the data is empty!";
	//将最大元素替换为新元素
	data[0] = e;
	SiftDown(0);
}
```
### heapify
将任意数组整理成堆的形状，从最后一个非叶子节点（最后一个节点的parent节点）开始，依次SiftDown。
将此方法写成以数组为参数的堆的构造函数。
```c++
template<typename T>
MaxHeap<T>::MaxHeap(T arr[],int length)
{
	//heapify
	//将数组arr[]赋给data
	for (int i = 0; i < length; i++)
		data.push_back(arr[i]);
	for (int j = parent(length - 1); j >= 0; j--)
		SiftDown(j);
}
```
时间复杂度为O(n)，而上一种方法将数组添加到新堆中时间复杂度为O(nlogn)，所以用heapify来实现堆排序会快很多。
```c++
//用heapify实现堆排序
template<typename T>
void HeapSort2(T data[], int length)
{
	MaxHeap<T> heap(data,length);

	for (int i = length - 1; i >= 0; i--)
		data[i] = heap.extractMax();
}
```
此排序依然用到了额外的空间。
### 原地堆排序
数组首元素data[0]为最大值，使i从末尾遍历,交换data[0]和data[i]，swap[data,0,i]，然后对data[0.i)形成的最大堆中索引0的元素SiftDown，SiftDown(data,0,i)。
```c++
//交换
template<typename T>
void swap(T data[], int i, int j) {
	T t = data[i];
	data[i] = data[j];
	data[j] = t;
}
//对data[0,n)形成的最大堆中，索引k的元素，执行SiftDown
template<typename T>
void SiftDown(T data[],int k,int n)
{
	while (2 * k + 1 < n) {
		int j = 2*k+1;
		if (j + 1 < n && data[j] < data[j + 1]) {//若k有右孩子并且右孩子值大于左孩子
			j = j + 1;//则令j等于右孩子的索引
		}
		//最终j为左右孩子中值最大的元素中的索引
		if (data[k] >= data[j])
			break;//此时已到合适位置，循环终止
		//交换k与j
		swap(data,k,j);
		k = j;
	}
}

//原地排序
template<typename T>
void HeapSort3(T data[], int length)
{
	if (length <= 1) return;

	for (int i = (length - 2)/2; i >= 0; i--)
		SiftDown(data,i,length);
	for (int j = length-1 ; j >=0; j--) {
		swap(data, 0, j);
		SiftDown(data, 0, j);
	}
}
```
这样堆排序的时间性能依然差强人意，堆主要不是用来排序，最重要的作用是用来组建优先队列。
用堆来实现优先队列只需要在声明的优先队列类中声明一个私有的堆对象，用该对象来调用对应功能的方法。
## 优先队列经典问题 top K
在N个元素中选出最大/小的k个元素。
### 剑指Offer 40 最小的k个数
从元素中选出最小的k个元素，使用基于最大堆的优先队列，维护每个新数据，若比这k个最小元素中最大的还小则替换。
```java
class  Solution {
	public  int[] getLeastNumbers(int[] arr, int  k) {
		PriorityQueue<Integer> pq=new  PriorityQueue<>(Comparator.reverseOrder());
		for(int  i=0;i<k;i++)
			pq.add(arr[i]);
		for(int  j=k;j<arr.length;j++){
			if(!pq.isEmpty()&&arr[j]<pq.peek()){
				pq.remove();
				pq.add(arr[j]);
			}
		}
		int[] res=new  int[k];
		for(int  i=0;i<k;i++){
			res[i]=pq.remove();
		}
		return res;
	}
}
```

### leetcode 215 第k个最大的元素
与上面类似
```java
class  Solution {
	public  int  findKthLargest(int[] nums, int  k) {
	PriorityQueue<Integer> pq=new  PriorityQueue<>();
	for(int  i=0;i<k;i++)
		pq.add(nums[i]);
	for(int  j=k;j<nums.length;j++){
		if(!pq.isEmpty()&&nums[j]>pq.peek()){
			pq.remove();
			pq.add(nums[j]);
			}
	}
	return  pq.peek();
	}
}
```
关于top K select K问题
|  | 时间复杂度 |空间复杂度
|--|--|--|
| 快速排序 | O(n) |O(1)
|优先队列|O(nlogn)|O(k)

快速排序的性能更好，但是优先队列不需要一次性知道所有数据，使用于数据流。
相关拓展：二叉堆->d叉堆；索引堆；二项堆；斐波那契堆；
从广义角度理解优先队列。

