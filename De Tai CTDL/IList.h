#ifndef ILIST_H
#define ILIST_H
#include<functional>
#include<iostream>

template<typename T>
class IList
{
public:
	typedef std::function<bool(T*, int)> ACTION;
	typedef std::function<std::string(T*)> SelectString;
	virtual T* GetData(int index) = 0;
	virtual int InsertConst(T* data) = 0;
	virtual bool Delete(int index) = 0;
	virtual void forEach(const ACTION& action, int indexStart = 0, int indexEnd = -1) = 0;
	virtual bool isempty() = 0;
	virtual int Search(T* data) = 0;
	virtual	int getSize() = 0;
	virtual void RadixSort(const SelectString& select) = 0;
	virtual void Clear(bool isDeleteData = false) = 0;
	virtual IList<T>* filter(const ACTION& action) = 0;
};

#endif // !ILIST_H
