
#ifndef ARRAYLIST_H
#include "ArrayList.h"
#endif // !ARRAYLIST_H



#ifndef ARRAYLIST_CPP
#define ARRAYLIST_CPP

template<typename T>
inline ArrayList<T>::ArrayList(int size)
{
	_size = size;
	_data = new T * [_size];
	_amount = 0;
}

template<typename T>
ArrayList<T>::~ArrayList()
{
	delete[] _data;
}

template<typename T>
bool ArrayList<T>::Insert(int index, T* data)
{
	if (index < 0 || index >= _size || _amount >= _size) return false;

	for (int i = _amount; i > index; i++)
	{
		_data[i] = _data[i - 1];
	}
	++_amount;
	_data[index] = data;
	return true;
}

template<typename T>
bool ArrayList<T>::Insert(T* data)
{
	if (_amount >= _size) return false;
	_data[_amount++] = data;
	return true;
}

template<typename T>
int ArrayList<T>::InsertConst(T* data)
{
	if (_amount >= _size) return false;

	_data[_amount] = data;

	int index = 0;
	for (; *data > * _data[index]; index++);


	if (index < _amount) {

		for (int i = _amount; i > index; i--)
		{
			_data[i] = _data[i - 1];
		}
		_data[index] = data;
	}

	++_amount;

	return index;

}

template<typename T>
bool ArrayList<T>::Delete(int index, int amount = 1)
{
	if (!isCheckIndex(index) || _amount == 0) return false;

	int amountDelete = _amount - index;

	amountDelete = (amount > amountDelete ? amountDelete : amount) + index;
	int indexDelete = index;
	for (; indexDelete < amountDelete; indexDelete++)
	{
		delete _data[indexDelete];
	}


	amountDelete = _amount - 1;

	for (; indexDelete <= amountDelete; index++, indexDelete++)
	{
		_data[index] = _data[indexDelete];
	}

	_amount -= amount;

	return true;
}

template<typename T>
bool ArrayList<T>::Delete(int index)
{
	return Delete(index, 1);
}

template<typename T>
bool ArrayList<T>::isCheckIndex(int index)
{
	return !(index < 0 || index >= _amount);
}

template<typename T>
bool ArrayList<T>::Update(int index, T* data)
{
	if (!isCheckIndex(index) || _amount == 0) return false;

	delete _data[index];
	_data[index] = data;

	return true;
}

template<typename T>
void ArrayList<T>::RadixSort(const SelectString& select)
{
}

template<typename T>
int ArrayList<T>::Search(T* data)
{
	for (int i = 0; i < _amount; i++)
	{
		if (*_data[i] == *data) return i;
	}
	return -1;
}

template<typename T>
int ArrayList<T>::Size()
{
	return _amount;
}

template<typename T>
bool ArrayList<T>::isempty()
{
	return _amount == 0;
}

template<typename T>
void ArrayList<T>::forEach(const IList<T>::ACTION& action, int indexStart, int indexEnd)
{
	if (indexStart < 0) return;

	int indexEndTemp = _amount;
	if (indexEnd > -1) {
		indexEndTemp = indexEnd >= _amount ? _amount : indexEnd + 1;
	}
	for (; indexStart < indexEndTemp; indexStart++)
	{
		if (!action(_data[indexStart], indexStart)) return;
	}
	for (indexStart; indexStart <= indexEnd; indexStart++)
	{
		if (!action(NULL, indexStart)) return;
	}
}

template<typename T>
IList<T>* ArrayList<T>::filter(const IList<T>::ACTION& action)
{
	IList<T>* temps = new  ArrayList<T>(_size);
	for (int i = 0; i < getSize(); i++)
	{
		if (action(_data[i], i)) {
			temps->InsertConst(_data[i]);
		}
	}
	return temps;
}

template<typename T>
T* ArrayList<T>::GetData(int index)
{
	if (!isCheckIndex(index) || _amount == 0) return NULL;
	return _data[index];
}

template<typename T>
int ArrayList<T>::getSize()
{
	return Size();
}

template<typename T>
void ArrayList<T>::Clear(bool isDeleteData = false)
{
	for (int i = 0; i < _amount; i++)
	{
		delete _data[i];
	}
}


#endif // !ARRAYLIST_CPP


