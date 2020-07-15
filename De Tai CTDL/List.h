#ifndef List_H
#define List_H

#define _ptr(_var) *##_var

template<class _T>
struct node
{
	_T* info;
	node<_T>* next;
};

template<class T>
class List
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

	nodePtr insertConst(T* ptrDat);

	//
	bool Addlast(nodePtr value);
	bool AddFirt(nodePtr Value);
	void clear();
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
	bool DelCen(T* ptrDat) {
		if (isempty() || ptrDat == nullptr) return 0;
		if (_ptr(ptrDat) == _ptr(_first->info)) return Delfirst();
		nodePtr temp = _first;
		while (temp->next != nullptr && _ptr(ptrDat) != _ptr(temp->next->info)) temp = temp->next;
		if (temp->next == nullptr) return 0;
		if (temp->next == _last) {
			delete _last;
			_last = temp;
			temp->next = nullptr;
		}
		else
		{
			nodePtr bktemp = temp->next->next;
			delete temp->next;
			temp->next = bktemp;
		}
		--_count;
		return 1;
	}

	bool DelCen(T* ptrDat, int& index);

	bool DelLast();

	bool DelNode(nodePtr Nde);

	virtual bool AddList(List<T>& list);
	//----------------------
	bool isempty();
	//-------------
	nodePtr search(dataPtr dat);
	int searchIndex(dataPtr dat);
	nodePtr getfirst();
	nodePtr getLast();
	int getSize();
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

