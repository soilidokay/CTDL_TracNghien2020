#ifndef List_H
#include "List.h"
#endif 

#ifndef LIST_CPP
#define LIST_CPP

template<class T>
node<T>* List<T>::createnode(List<T>::dataPtr dat) {
	node<T>* ptrtemp = NULL;
	ptrtemp = new List<T>::nodeOjb;
	if (ptrtemp != NULL) {
		ptrtemp->info = dat;
		ptrtemp->next = NULL;
	}
	return ptrtemp;
}

template<class T>
node<T>* List<T>::insertfirst(dataPtr dat)
{
	if (dat == NULL) return NULL;
	nodePtr ptrtemp = createnode(dat);
	if (ptrtemp == NULL) return NULL;
	else
	{
		++_count;
		ptrtemp->next = _first;
		_first = ptrtemp;
		if (_last == NULL) _last = _first;
	}
	return ptrtemp;
}

template<class T>
node<T>* List<T>::insertlast(dataPtr dat)
{
	if (dat == NULL) return NULL;
	nodePtr ptrtemp = createnode(dat);
	if (ptrtemp == NULL) return NULL;
	else
	{
		++_count;
		if (isempty()) _first = ptrtemp;
		else _last->next = ptrtemp;
		_last = ptrtemp;
	}
	return ptrtemp;
}

template<class T>
node<T>* List<T>::insertCen(T* ptrdatsam, T* ptrDat)
{
	if (ptrdatsam == NULL || ptrDat == NULL) return NULL;
	if (isempty()) return insertfirst(ptrDat);
	if (_last->info == ptrdatsam) return insertlast(ptrDat);
	else
	{
		nodePtr temp = NULL;
		temp = search(ptrdatsam);
		if (temp != NULL) {
			nodePtr tempDat = createnode(ptrDat);
			if (tempDat != NULL) {
				++_count;
				tempDat->next = temp->next;
				temp->next = tempDat;
				return tempDat;
			}
		}
	}
	return NULL;
}

template<class T>
node<T>* List<T>::insertCen(nodePtr ptrN, T* ptrdat)
{
	nodePtr temp;
	temp = createnode(ptrdat);
	if (temp == NULL)return NULL;
	temp->next = ptrN->next;
	ptrN->next = temp;
	if (ptrN == _last) _last = ptrN;
	return temp;
}


template<class T>
void List<T>::RadixSort(const SelectString& select)
{
	if (isempty()) return;

	nodePtr trav = _first;
	//tim chuoi dai nhat
	int maxLen = 0, MaxTemp = 0;
	while (trav != NULL) {
		MaxTemp = select(trav->info).length();
		if (MaxTemp > maxLen) {
			maxLen = MaxTemp;
		}
		trav = trav->next;
	}

	nodePtr** bucket = new nodePtr * [257];
	for (int i = 0; i < 257; i++)
	{
		bucket[i] = new nodePtr[2];
		bucket[i][0] = NULL;
		bucket[i][1] = NULL;
	}

	//sap xep
	for (int i = maxLen - 1; i > 0; i--)
	{
		BucketListString(select, bucket, i);
		MergeBucket(bucket);
	}
	for (int i = 0; i < 257; i++)
	{
		delete[] bucket[i];
	}
	delete[] bucket;
}
template<class T>
void List<T>::BucketListString(const SelectString& select, nodePtr**& bucket, int offset)
{

	nodePtr trav = _first, travNext;
	int pos = 0;
	std::string buffstr = "";
	while (trav != NULL) {

		buffstr = select(trav->info);

		if (offset < buffstr.length()) {
			pos = buffstr[offset];
			if (bucket[pos + 1][0] == NULL) {
				bucket[pos + 1][0] = trav;
				bucket[pos + 1][1] = trav;
			}
			else {
				bucket[pos + 1][1]->next = trav;
				bucket[pos + 1][1] = trav;
			}
		}
		else {
			if (bucket[0][0] == NULL) {
				bucket[0][0] = trav;
				bucket[0][1] = trav;
			}
			else {
				bucket[0][1]->next = trav;
				bucket[0][1] = trav;
			}
		}

		trav = trav->next;
	}
}
template<class T>
void List<T>::MergeBucket(nodePtr**& LstBucket)
{
	nodePtr* temp = LstBucket[0];
	int index = 1;
	while (temp[0] == NULL) temp = LstBucket[index++];

	_first = temp[0];
	temp[0] = NULL;

	for (; index < 257; index++)
	{
		if (LstBucket[index][0] != NULL) {
			temp[1]->next = LstBucket[index][0];
			temp = LstBucket[index];
			temp[0] = NULL;
		}
	}
	_last = temp[1];
	_last->next = NULL;
}
template<class T>
node<T>* List<T>::insertConst(T* ptrDat)
{
	if (ptrDat == NULL)return NULL;
	if (isempty() || _ptr(_first->info) > _ptr(ptrDat)) return insertfirst(ptrDat);
	nodePtr temp = createnode(ptrDat);
	_last->next = temp;
	temp->next = _first;
	nodePtr trav = _first;
	while (_ptr(trav->next->info) < _ptr(ptrDat)) trav = trav->next;
	if (trav == _last) {
		_last = temp;
		++_count;
		_last->next = NULL;
		return temp;
	}
	temp->next = trav->next;
	trav->next = temp;
	_last->next = NULL;
	++_count;
	return temp;
}

template<class T>
int List<T>::Search(T* data)
{
	return searchIndex(data);
}

template<class T>
int List<T>::InsertConst(T* data)
{
	node<T>* temp = insertConst(data);
	if (temp == NULL) return -1;
	return searchIndex(data);
}

template<class T>
bool List<T>::Delete(int index) {

	if (index < 0 || index >= getSize()) return false;

	int indexTemp = 0;
	nodePtr trav = _first, prev = NULL;

	while (indexTemp < index) {
		prev = trav;
		trav = trav->next;
		++indexTemp;
	}

	delete trav->info;


	if (prev == NULL) {
		nodePtr temp = _first->next;
		_first = temp;
	}
	else if (trav == _last) {
		_last = prev;
		prev->next = NULL;
	}
	else {
		prev->next = trav->next;
	}

	--_count;
	delete trav;
	return true;
}

template<class T>
void List<T>::forEach(const IList<T>::ACTION& action, int indexStart, int indexEnd)
{
	if (indexStart < 0) return;
	if (indexStart >= getSize()) indexStart = 0;
	int indexEndTemp = getSize();
	if (indexEnd > -1) {
		indexEndTemp = indexEnd >= getSize() ? getSize() : indexEnd + 1;
	}
	int index = 0;
	nodePtr i = _first;

	while (index < indexStart) {
		i = i->next;
		++index;
	}

	for (; index < indexEndTemp; i = i->next)
	{
		if (!action(i->info, index++)) return;
	}

	while (index <= indexEnd) if (!action(NULL, index++)) return;
}

template<class T>
IList<T>* List<T>::filter(const IList<T>::ACTION& action)
{
	IList<T>* temps = new List<T>();

	nodePtr trav = _first;
	int index = 0;
	while (trav != NULL) {
		if (action(trav->info, index++)) {
			temps->InsertConst(trav->info);
		}
		trav = trav->next;
	}
	return temps;
}

template<class T>
T* List<T>::GetData(int index)
{
	if (index < 0 || index > getSize()) return NULL;

	int indexTemp = 0;
	for (nodePtr i = _first; i != NULL; i = i->next)
	{
		if (indexTemp == index) {
			return i->info;
		}
		++indexTemp;
	}
	return NULL;
}

template<class T>
bool List<T>::Addlast(nodePtr value)
{
	if (value == NULL) return 0;
	else
	{
		++_count;
		if (isempty()) _first = value;
		else _last->next = value;
		_last = value;
		_last->next = NULL;
	}
	return 1;
}

template<class T>
bool List<T>::AddFirt(nodePtr Value)
{
	if (Value == NULL) return 0;
	else
	{
		++_count;
		Value->next = _first;
		_first = Value;
		if (_last == NULL) _last = _first;
	}
	return 1;
}

template<class T>
void List<T>::Clear(bool isDeleteData)
{
	while (!isempty())
	{
		if (isDeleteData) {
			delete getfirst()->info;
		}
		Delfirst();
	}
}
template<class T>
bool List<T>::Delfirst()
{
	if (isempty()) return 0;
	nodePtr temp = _first->next;
	if (_first == _last) _last = NULL;
	delete _first;
	_first = temp;
	--_count;
	return 1;
}
template<class T>
bool List<T>::DelCen(T* ptrDat)
{
	if (isempty() || ptrDat == NULL) return 0;
	if (_ptr(ptrDat) == _ptr(_first->info)) return Delfirst();
	nodePtr temp = _first;
	while (temp->next != NULL && _ptr(ptrDat) != _ptr(temp->next->info)) temp = temp->next;
	if (temp->next == NULL) return 0;
	if (temp->next == _last) {
		delete _last;
		_last = temp;
		temp->next = NULL;
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
template<class T>
bool List<T>::DelCen(T* ptrDat, int& index)
{
	index = -1;
	if (isempty() || ptrDat == NULL) return -1;
	if (_ptr(ptrDat) == _ptr(_first->info)) {
		index = 0;
		return Delfirst();
	}
	nodePtr temp = _first;
	index = 0;
	while (temp->next != NULL && _ptr(ptrDat) != _ptr(temp->next->info)) {
		temp = temp->next;
		index++;
	}
	if (temp->next == NULL) return -1;
	if (temp->next == _last) {
		delete _last;
		_last = temp;
		temp->next = NULL;
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
template<class T>
bool List<T>::DelLast()
{
	if (isempty()) return 0;

	if (_last == _first) return Delfirst();

	nodePtr temp = _first;
	while (temp->next != NULL) temp = temp->next;

	delete _last;
	_last = temp;
	temp->next = NULL;
	--_count;

	return 1;
}
template<class T>
bool List<T>::DelNode(nodePtr Nde)
{
	if (Nde == _first) return Delfirst();
	if (Nde == _last) return DelLast();
	return DelCen(Nde->info);
}
template<class T>
bool List<T>::AddList(List<T>& list)
{
	if (list.isempty()) return 0;
	if (!isempty()) _ptr(this) = list;
	else {
		_last->next = list.getfirst();
		_last = list.getLast();
		_count += list._count;
	}
	return 1;
}

template<class T>
bool List<T>::isempty()
{
	return _first == NULL;
}

template<class T>
node<T>* List<T>::search(dataPtr dat)
{
	if (isempty()) return NULL;
	nodePtr _Cur = _first;
	nodePtr tempdat = createnode(dat);
	_last->next = tempdat;

	while (_ptr(_Cur->info) != _ptr(dat)) _Cur = _Cur->next;

	if (_Cur == tempdat) _Cur = NULL;
	delete tempdat;
	_last->next = NULL;
	return _Cur;
}

template<class T>
int List<T>::searchIndex(dataPtr dat)
{
	if (isempty()) return -1;
	nodePtr _Cur = _first;
	nodePtr tempdat = createnode(dat);
	_last->next = tempdat;
	int index = 0;
	while (_ptr(_Cur->info) != _ptr(dat)) {
		index++;
		_Cur = _Cur->next;
	}

	if (_Cur == tempdat) {
		index = -1;
		_Cur = NULL;
	}
	delete tempdat;
	_last->next = NULL;
	return index;
}

template<class T>
node<T>* List<T>::getfirst()
{
	return _first;
}

template<class T>
node<T>* List<T>::getLast()
{
	return _last;
}

template<class T>
int List<T>::getSize()
{
	return _count;
}

template<class T>
void List<T>::Sort()
{
	if (isempty() || _count < 2) return;
	nodePtr num1 = _first;
	nodePtr num2;
	for (; num1->next != NULL; num1 = num1->next)
		for (num2 = num1->next; num2 != NULL; num2 = num2->next) {
			if (_ptr(num1->info) > _ptr(num2->info)) {
				swap(num1->info, num2->info);
			}
		}
}

template<class T>
List<T>::~List()
{
	while (!isempty())
	{
		Delfirst();
	}
}

template<class T>
List<T>::List()
{

}


#endif //!LIST_CPP