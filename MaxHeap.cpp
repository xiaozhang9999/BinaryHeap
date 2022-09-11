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

template<typename T>
void MaxHeap<T>::replace(T e)
{
	if (empty())
		throw "the data is empty!";
	//将最大元素替换为新元素
	data[0] = e;
	SiftDown(0);
}


template<typename T>
string MaxHeap<T>::to_string()
{
	string s;
	s = "the data is:";
	if (data.empty())
		s = s + " NULL";
	else {
		for (T e : data) {
			s = s + " " + std::to_string(e);
		}
	}
	return s;
}
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
//用heapify实现堆排序
template<typename T>
void HeapSort2(T data[], int length)
{
	MaxHeap<T> heap(data,length);

	for (int i = length - 1; i >= 0; i--)
		data[i] = heap.extractMax();
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
		swap(data[k], data[j]);
		k = j;
	}
}
//交换
template<typename T>
void swap(T data[], int i, int j) {
	T t = data[i];
	data[i] = data[j];
	data[j] = t;
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
int main()
{
	MaxHeap<int> heap ;
	int a[] = { 6,4,7,3,8,2,5 };
	for (int i = 0; i < 7; i++) {
		heap.add(a[i]);
	}
	cout << heap.to_string() << endl;
	while (!heap.empty()) {
		cout<<heap.extractMax()<<endl;
		cout << heap.to_string() << endl;
	}
	HeapSort3(a,7);
	for (int e : a)
		cout << e << " ";
	
	cout << endl;
}
