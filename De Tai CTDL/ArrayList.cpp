
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
bool ArrayList<T>::InsertConst(T* data)
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

	return true;

}

template<typename T>
bool ArrayList<T>::Delete(int index, int amount = 1)
{
	if (!isCheckIndex(index) || _amount == 0) return false;

	int amountDelete = _amount - index;

	int indexDelete = (amount > amountDelete ? amountDelete : amount) + index;

	for (int i = index; i < indexDelete; i++)
	{
		delete _data[i];
	}

	amountDelete = indexDelete;

	for (; index < amountDelete; index++)
	{
		_data[index] = _data[indexDelete++];
		--_amount;
	}
	return true;
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
T* ArrayList<T>::Search(T* data)
{
	for (int i = 0; i < _amount; i++)
	{
		if (*_data[i] == *data) return _data[i];
	}
	return NULL;
}

template<typename T>
int ArrayList<T>::Size()
{
	return _amount;
}

template<typename T>
T* ArrayList<T>::GetData(int index)
{
	if (!isCheckIndex(index) || _amount == 0) return NULL;
	return _data[index];
}

template<typename T>
void ArrayList<T>::Clear()
{
	for (int i = 0; i < _amount; i++)
	{
		delete _data[i];
	}
}


#endif // !ARRAYLIST_CPP


