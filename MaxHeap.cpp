#include<iostream>
using namespace std;
#include<vector>
#include<string>
template<typename T>
class MaxHeap
{
public:
	MaxHeap() {};
	MaxHeap(T arr[],int length);//heapify����������ɶѵ���״
	~MaxHeap() {};
	int size() { return data.size(); }//����Ԫ�ظ���
	bool empty() { return data.empty(); };//���Ƿ�Ϊ��
	int parent(int index);//���ؽڵ�ĸ�������
	int leftChild(int index);//���ؽڵ����������
	int rightChild(int index);//���ؽڵ���Һ�������
	void add(T e);//���һ����Ԫ��
	void SiftUp(int k);//������Ϊk��Ԫ���ϵ�������λ��
	T extractMax();//ȡ������Ԫ�ز�����
	void SiftDown(int k);//���������ڵ��Ԫ���³�������λ��
	void replace(T e);//ȡ�����Ԫ�أ�����һ����Ԫ��
	string to_string();//�ַ������
private:
	vector<T> data;
};

template<typename T>
MaxHeap<T>::MaxHeap(T arr[],int length)
{
	//heapify
	//������arr[]����data
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
	data.push_back(e);//��data��ĩβ���Ԫ��e
	SiftUp(data.size() - 1);//��Ԫ�ص���������λ��
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
		throw "the data is empty!";//����Ϊ��ʱ�޷�ȡ��Ԫ��
	T ret = data.front();//data�е�һ��Ԫ�أ�Ҳ������Ԫ��
	//�������һ�������һ��Ԫ�ؽ���
	swap(data.front(), data.back());
	//ɾ������Ԫ�أ���ʱ��������ĩβ
	data.pop_back();
	//������
	SiftDown(0);
	return ret;
}

template<typename T>
void MaxHeap<T>::SiftDown(int k)
{
	while (leftChild(k) < data.size()) {
		int j = leftChild(k);
		if (j + 1 < data.size() && data[j] < data[j + 1]) {//��k���Һ��Ӳ����Һ���ֵ��������
			j = j + 1;//����j�����Һ��ӵ�����
		}
		//����jΪ���Һ�����ֵ����Ԫ���е�����
		if (data[k] >= data[j])
			break;//��ʱ�ѵ�����λ�ã�ѭ����ֹ
		//����k��j
		swap(data[k], data[j]);
		k = j;
	}
}

template<typename T>
void MaxHeap<T>::replace(T e)
{
	if (empty())
		throw "the data is empty!";
	//�����Ԫ���滻Ϊ��Ԫ��
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
//���öѸ���������
template<typename T>
void HeapSort(T data[],int length)
{
	MaxHeap<T> heap;
	for (int j=0;j<length;j++) 
		heap.add(data[j]);

	for (int i = length - 1; i >= 0; i--) 
		data[i] = heap.extractMax();
}
//��heapifyʵ�ֶ�����
template<typename T>
void HeapSort2(T data[], int length)
{
	MaxHeap<T> heap(data,length);

	for (int i = length - 1; i >= 0; i--)
		data[i] = heap.extractMax();
}
//��data[0,n)�γɵ������У�����k��Ԫ�أ�ִ��SiftDown
template<typename T>
void SiftDown(T data[],int k,int n)
{
	while (2 * k + 1 < n) {
		int j = 2*k+1;
		if (j + 1 < n && data[j] < data[j + 1]) {//��k���Һ��Ӳ����Һ���ֵ��������
			j = j + 1;//����j�����Һ��ӵ�����
		}
		//����jΪ���Һ�����ֵ����Ԫ���е�����
		if (data[k] >= data[j])
			break;//��ʱ�ѵ�����λ�ã�ѭ����ֹ
		//����k��j
		swap(data[k], data[j]);
		k = j;
	}
}
//����
template<typename T>
void swap(T data[], int i, int j) {
	T t = data[i];
	data[i] = data[j];
	data[j] = t;
}
//ԭ������
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
