#ifndef List_H
#define List_H

#include "IList.h"
#include <memory> 

#define _ptr(_var) *##_var

template<class _T>
struct node
{
	_T* info;
	node<_T>* next;
};

template<class T>
class List : public IList<T>
{
public:
	typedef  node<T> nodeOjb;
	typedef  node<T>* nodePtr;
	typedef  T dataOjb;
	typedef  T* dataPtr;
	//three functions are buond together
	//------------------------------
	nodePtr createnode(dataPtr dat);
	nodePtr insertfirst(dataPtr dat);
	nodePtr insertlast(dataPtr dat);
	nodePtr insertCen(T* ptrdatsam, T* ptrDat);
	nodePtr insertCen(nodePtr ptrN, T* ptrdat);
	void RadixSort(const SelectString& select) override;
	void BucketListString(const SelectString& select, nodePtr**& bucket, int offset);
	void MergeBucket(nodePtr**& LstBucket);
	nodePtr insertConst(T* ptrDat);
	int Search(T* data) override;
	int InsertConst(T* data) override;
	bool Delete(int index)override;
	void forEach(const IList<T>::ACTION& action, int indexStart = 0, int indexEnd = -1) override;
	IList<T>* filter(const IList<T>::ACTION& action) override;
	T* GetData(int index) override;
	//
	bool Addlast(nodePtr value);
	bool AddFirt(nodePtr Value);
	void Clear(bool isDeleteData = false) override;
	//
	bool Delfirst();
	/*bool Dellast() {
		if (isempty()) return 0;
		if (_first == _last) {
			delete _last;
			_first = nullptr;
			_count = 0;
		}
		else
		{

		}
	}*/
	bool DelCen(T* ptrDat);

	bool DelCen(T* ptrDat, int& index);

	bool DelLast();

	bool DelNode(nodePtr Nde);

	virtual bool AddList(List<T>& list);
	//----------------------
	bool isempty() override;
	//-------------
	nodePtr search(dataPtr dat);
	int searchIndex(dataPtr dat);
	nodePtr getfirst();
	nodePtr getLast();
	int getSize() override;
	void Sort();
	~List();
	List();
protected:
	nodePtr _first = nullptr, _last = nullptr, _Current = nullptr;
	int _count = 0;
};

#ifndef LIST_CPP
#include "List.cpp"
#endif

#endif // !list_h

