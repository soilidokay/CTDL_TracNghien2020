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
	void SetCurrFirst() { _Current = _first; }
	nodePtr getNode() {
		nodePtr temp = nullptr;
		if (!isempty()) temp = _Current;
		if (_Current != nullptr) _Current = _Current->next;
		return temp;
	}
	bool isLast() { return _Current == nullptr; }
	//------------------------------
	nodePtr creatnode(dataPtr dat) {
		nodePtr ptrtemp = nullptr;
		ptrtemp = new nodeOjb;
		if (ptrtemp != nullptr) {
			ptrtemp->info = dat;
			ptrtemp->next = nullptr;
		}
		return ptrtemp;
	}
	nodePtr insertfirst(dataPtr dat) {
		if (dat == nullptr) return nullptr;
		nodePtr ptrtemp = creatnode(dat);
		if (ptrtemp == nullptr) return nullptr;
		else
		{
			++_count;
			ptrtemp->next = _first;
			_first = ptrtemp;
			if (_last == nullptr) _last = _first;
		}
		return ptrtemp;
	}
	nodePtr insertlast(dataPtr dat) {
		if (dat == nullptr) return nullptr;
		nodePtr ptrtemp = creatnode(dat);
		if (ptrtemp == nullptr) return nullptr;
		else
		{
			++_count;
			if (isempty()) _first = ptrtemp;
			else _last->next = ptrtemp;
			_last = ptrtemp;
		}
		return ptrtemp;
	}
	nodePtr insertCen(T* ptrdatsam, T* ptrDat) {
		if (ptrdatsam == nullptr || ptrDat == nullptr) return nullptr;
		if (isempty()) return insertfirst(ptrDat);
		if (_last->info == ptrdatsam) return insertlast(ptrDat);
		else
		{
			nodePtr temp = nullptr;
			temp = search(ptrdatsam);
			if (temp != nullptr) {
				nodePtr tempDat = creatnode(ptrDat);
				if (tempDat != nullptr) {
					++_count;
					tempDat->next = temp->next;
					temp->next = tempDat;
					return tempDat;
				}
			}
		}
		return nullptr;
	}
	nodePtr insertCen(nodePtr ptrN, T* ptrdat) {
		nodePtr temp;
		temp = creatnode(ptrdat);
		if (temp == nullptr)return nullptr;
		temp->next = ptrN->next;
		ptrN->next = temp;
		if (ptrN == _last) _last = ptrN;
		return temp;
	}

	nodePtr insertConst(T* ptrDat) {
		if (ptrDat == nullptr)return nullptr;
		if (isempty() || _ptr(_first->info) > _ptr(ptrDat)) return insertfirst(ptrDat);
		nodePtr temp = creatnode(ptrDat);
		_last->next = temp;
		temp->next = _first;
		nodePtr trav = _first;
		while (_ptr(trav->next->info) < _ptr(ptrDat)) trav = trav->next;
		if (trav == _last) {
			_last = temp;
			++_count;
			_last->next = nullptr;
			return temp;
		}
		temp->next = trav->next;
		trav->next = temp;
		_last->next = nullptr;
		++_count;
		return temp;
	}

	//
	bool Addlast(nodePtr value) {
		if (value == nullptr) return 0;
		else
		{
			++_count;
			if (isempty()) _first = value;
			else _last->next = value;
			_last = value;
		}
		return 1;
	}
	bool AddFirt(nodePtr Value) {
		if (Value == nullptr) return 0;
		else
		{
			++_count;
			Value->next = _first;
			_first = Value;
			if (_last == nullptr) _last = _first;
		}
		return 1;
	}
	void clear() {
		while (!isempty())
		{
			delete getfirst()->info;
			Delfirst();
		}
	}
	//
	bool Delfirst() {
		if (isempty()) return 0;
		nodePtr temp = _first->next;
		if (_first == _last) _last = nullptr;
		delete _first;
		_first = temp;
		--_count;
		return 1;
	}
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

	bool DelCen(T* ptrDat, int& index) {
		index = -1;
		if (isempty() || ptrDat == nullptr) return -1;
		if (_ptr(ptrDat) == _ptr(_first->info)) {
			index = 0;
			return Delfirst();
		}
		nodePtr temp = _first;
		index = 0;
		while (temp->next != nullptr && _ptr(ptrDat) != _ptr(temp->next->info)) {
			temp = temp->next;
			index++;
		}
		if (temp->next == nullptr) return -1;
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
		return true;
	}

	bool DelLast() {
		if (_last == _first) return Delfirst();
		nodePtr temp = _first;
		while (temp->next != nullptr) temp = temp->next;
		if (temp->next == _last) return 0;
		if (temp->next == _last) {
			delete _last;
			_last = temp;
			temp->next = nullptr;
			--_count;
		}
		return 1;
	}
	bool DelNode(nodePtr Nde) {
		if (Nde == _first) return Delfirst();
		if (Nde == _last) return DelLast();
		return DelCen(Nde->info);
	}
	//The temp parameter contains the address,
	//it belongs to the class being added
	//-------Two functions are bound together
	void reset(nodePtr temp) {
		if (temp == _first) { _first = nullptr; _count = 0; }
	}
	virtual bool AddList(List<T>& list) {
		if (list.isempty()) return 0;
		if (!isempty()) _ptr(this) = list;
		else {
			_last->next = list.getfirst();
			_last = list.getLast();
			_count += list._count;
		}
		return 1;
	}
	//----------------------
	bool isempty() { return _first == nullptr; }
	//-------------
	void setfirst(nodePtr first) { _first = first; }
	void setlast(nodePtr last) { _last = last; }
	//-----------------------
	nodePtr search(dataPtr dat) {
		if (isempty()) return nullptr;
		nodePtr _Cur = _first;
		nodePtr tempdat = creatnode(dat);
		_last->next = tempdat;

		while (_ptr(_Cur->info) != _ptr(dat)) _Cur = _Cur->next;

		if (_Cur == tempdat) _Cur = nullptr;
		delete tempdat;
		_last->next = nullptr;
		return _Cur;
	}
	int searchIndex(dataPtr dat) {
		if (isempty()) return -1;
		nodePtr _Cur = _first;
		nodePtr tempdat = creatnode(dat);
		_last->next = tempdat;
		int index = 0;
		while (_ptr(_Cur->info) != _ptr(dat)) {
			index++;
			_Cur = _Cur->next;
		}

		if (_Cur == tempdat) {
			index = -1;
			_Cur = nullptr;
		}
		delete tempdat;
		_last->next = nullptr;
		return index;
	}
	nodePtr getfirst() { return _first; }
	nodePtr getLast() { return _last; }
	int getSize() { return _count; }
	void Sort() {
		if (isempty() || _count < 2) return;
		nodePtr num1 = _first;
		nodePtr num2;
		for (; num1->next != nullptr; num1 = num1->next)
			for (num2 = num1->next; num2 != nullptr; num2 = num2->next) {
				if (_ptr(num1->info) > _ptr(num2->info)) {
					swap(num1->info, num2->info);
				}
			}
	}
	~List() {
		while (!isempty())
		{
			Delfirst();
		}
	}
	List() {

	}
protected:
	nodePtr _first = nullptr, _last = nullptr, _Current = nullptr;
	int _count = 0;
};

template <class T>
class Queue : public List<T>
{
public:
	//--------------------
	T* GetValue() {
		T* temp = nullptr;
		if (!isempty()) {
			--_count;
			temp = _first->info;
			nodePtr tempPtr = _first;
			_first = _first->next;
			delete tempPtr;
		}
		return temp;
	}
};
template<class T>
class Stack : public List<T>
{
public:
	bool AddList(List<T>& list) override {
		if (list.isempty()) return 0;
		if (!isempty()) _ptr(this) = list;
		else {
			list.getLast()->next = _first;
			_first = list.getfirst();
			_count += list._count;
		}
		return 1;
	}
	T* getValue() {
		T* temp = nullptr;
		if (!isempty()) {
			--_count;
			temp = _first->info;
			nodePtr tempPtr = _first;
			_first = _first->next;
			delete tempPtr;
		}
		return temp;
	}
};
#endif // !list_h