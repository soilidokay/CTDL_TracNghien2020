#ifndef ARRAYLIST_H
#define ARRAYLIST_H
template<typename T>
class ArrayList
{
public:
	ArrayList(int size);
	~ArrayList();
	bool Insert(int index, T* data);
	bool Insert(T* data);
	bool InsertConst(T* data);
	bool Delete(int index, int amount = 1);
	bool isCheckIndex(int index);
	bool Update(int index, T* data);
	T* Search(T* data);
	int Size();
	T* GetData(int index);
	void Clear();
private:
	T** _data;
	int _size;
	int _amount;
};

#ifndef ARRAYLIST_CPP
#include "ArrayList.cpp"
#endif // !ARRAYLIST_CPP

#endif // !ARRAYLIST_H
