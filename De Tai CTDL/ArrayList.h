#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "IList.h"


template<typename T>
class ArrayList :public IList<T>
{
public:
	ArrayList(int size);
	~ArrayList();
	bool Insert(int index, T* data);
	bool Insert(T* data);
	int InsertConst(T* data) override;
	bool Delete(int index, int amount = 1);
	bool Delete(int index) override;
	bool isCheckIndex(int index);
	bool Update(int index, T* data);
	void RadixSort(const SelectString& select) override;
	int Search(T* data) override;
	int Size();
	bool isempty() override;
	void forEach(const IList<T>::ACTION& action, int indexStart = 0, int indexEnd = -1) override;
	IList<T>* filter(const IList<T>::ACTION& action) override;
	T* GetData(int index) override;
	int getSize() override;
	void Clear(bool isDeleteData = false) override;
private:
	T** _data;
	int _size;
	int _amount;
};

#ifndef ARRAYLIST_CPP
#include "ArrayList.cpp"
#endif // !ARRAYLIST_CPP

#endif // !ARRAYLIST_H
