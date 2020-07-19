#ifndef DBSET_H
#include "DBSet.h"
#endif

#ifndef DBSET_CPP
#define DBSET_CPP

template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
DBSet<_TIdCompare, _TId, amount, _TEntity, T>::DBSet(std::string pathdata)
{
	this->Initial(pathdata);
}

template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
DBSet<_TIdCompare, _TId, amount, _TEntity, T>::DBSet(std::string pathdata, int SizeData)
{
	_SizeData = SizeData;
	this->Initial(pathdata);

}

template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
DBSet<_TIdCompare, _TId, amount, _TEntity, T>::~DBSet()
{
	_fData->close();
	delete _fData;
	_dataId->Clear();
	delete _dataId;
}

template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
void DBSet<_TIdCompare, _TId, amount, _TEntity, T>::Add(T* data)
{
	int offsetData = _dataId->getSize() * _SizeData;

	if (!_dataOffsetRemove->isempty()) {
		int* temp = _dataOffsetRemove->getfirst()->info;
		offsetData = *temp;
		delete temp;
		_dataOffsetRemove->Delfirst();
		WriteIndexRemove();
	}

	DataIndex<_TIdCompare, _TId, amount>* dataIndex = GetDataIndex(data, offsetData);

	int index = _dataId->searchIndex(dataIndex);

	if (index > -1) return;

	AddIdex(dataIndex);

	_TEntity* temp = data;
	_fData->seekp(offsetData);
	_fData->write(reinterpret_cast<const char*>(temp), _SizeData);
}


template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
void DBSet<_TIdCompare, _TId, amount, _TEntity, T>::Delete(T* data, bool deleteData)
{

	DataIndex<_TIdCompare, _TId, amount>* dataIndex = GetDataIndex(data, 0);
	node<DataIndex<_TIdCompare, _TId, amount>>* tempindex = _dataId->search(dataIndex);
	if (tempindex == NULL) return;

	_fData->seekp(tempindex->info->sizeOffset);
	int* dataremove = new int(tempindex->info->sizeOffset);
	_dataOffsetRemove->insertlast(dataremove);

	_TEntity dataTemp;
	_fData->write(reinterpret_cast<const char*>(&dataTemp), _SizeData);

	DeleteIndex(dataIndex);
	WriteIndexRemove();
	if (deleteData) {
		delete data;
	}
	delete dataIndex;
}
template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
void DBSet<_TIdCompare, _TId, amount, _TEntity, T>::Update(T* data)
{
	DataIndex<_TIdCompare, _TId, amount>* dataIndex = GetDataIndex(data, 0);
	node<DataIndex<_TIdCompare, _TId, amount>>* tempindex = _dataId->search(dataIndex);
	if (tempindex == NULL) return;
	_TEntity* temp = data;
	_fData->seekp(tempindex->info->sizeOffset);
	_fData->write(reinterpret_cast<const char*>(temp), _SizeData);
	delete dataIndex;
}
template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
List<T>* DBSet<_TIdCompare, _TId, amount, _TEntity, T>::ToList()
{
	List<T>* data = new List<T>;
	if (_dataId->isempty()) return data;

	T** dataptr = ReadDataPtr();

	for (int i = 0; i < _dataId->getSize(); i++)
	{
		data->insertlast(dataptr[i]);
	}

	return data;
}
template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
T* DBSet<_TIdCompare, _TId, amount, _TEntity, T>::ToArray()
{
	return ReadData();
}
template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
T** DBSet<_TIdCompare, _TId, amount, _TEntity, T>::ToArrayPtr()
{
	return ReadDataPtr();
}

template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
ArrayList<T>* DBSet<_TIdCompare, _TId, amount, _TEntity, T>::ToArrayList(int size)
{
	return ReadDataArrayList(size);
}

template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
TreeAVL<T>* DBSet<_TIdCompare, _TId, amount, _TEntity, T>::ToTree()
{
	return ReadDataTree();
}

template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
int DBSet<_TIdCompare, _TId, amount, _TEntity, T>::size()
{
	return _dataId->getSize();
}

template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
void DBSet<_TIdCompare, _TId, amount, _TEntity, T>::CheckAndCreateFile(std::string path)
{
	std::fstream* f = new std::fstream(path, std::ios::in);
	if (f->is_open()) {
		f->close();
		delete f;
	}
	else
	{
		f->close();
		delete f;
		f = new  std::fstream(path, std::ios::out);
		f->close();
		delete f;
	}
	_fData = new std::fstream(path, std::ios::binary | std::ios::out | std::ios::in | std::ios::ate);
}

template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
void DBSet<_TIdCompare, _TId, amount, _TEntity, T>::Initial(std::string pathdata)
{
	if (_SizeData < 1) {
		_SizeData = sizeof(_TEntity);
	}
	_SizeDataIndex = sizeof(EntityDataIndex<_TId, amount>);
	_dataId = new List<DataIndex<_TIdCompare, _TId, amount>>();
	_dataOffsetRemove = new List<int>;
	CheckAndCreateFile(pathdata);
	_PathIndex = "Index" + pathdata;
	_PathIndexRemove = "IndexRemove" + pathdata;
	ReadDataIndex();
	ReadDataIndexRemove();
}

template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
void DBSet<_TIdCompare, _TId, amount, _TEntity, T>::DeleteIndex(DataIndex<_TIdCompare, _TId, amount>* data)
{
	auto temp = _dataId->DelCen(data);
	if (temp) {
		WriteIndex();
	}
}
template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
void DBSet<_TIdCompare, _TId, amount, _TEntity, T>::AddIdex(DataIndex<_TIdCompare, _TId, amount>* data)
{
	_dataId->insertConst(data);
	WriteIndex();
}
template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
DataIndex<_TIdCompare, _TId, amount>* DBSet<_TIdCompare, _TId, amount, _TEntity, T>::GetDataIndex(T* data, int offsetData)
{
	comparetor = (CompareData<_TIdCompare>*) data;
	DataIndex<_TIdCompare, _TId, amount>* dataIndex = new DataIndex<_TIdCompare, _TId, amount>();
	dataIndex->setId(comparetor->getId());
	dataIndex->sizeOffset = offsetData;
	return dataIndex;
}
template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
void DBSet<_TIdCompare, _TId, amount, _TEntity, T>::WriteIndex()
{
	try {
		_fDataIndex = new std::fstream(_PathIndex, std::ios::binary | std::ios::out);
	}
	catch (std::exception e1) {
		// catch block
	}
	node<DataIndex<_TIdCompare, _TId, amount>>* trav = _dataId->getfirst();
	EntityDataIndex<_TId, amount>* data = NULL;
	int nSize = _dataId->getSize();
	_fDataIndex->write(reinterpret_cast<const char*>(&nSize), 4);
	while (trav != NULL) {
		data = trav->info;
		_fDataIndex->write(reinterpret_cast<char*>(data), _SizeDataIndex);
		trav = trav->next;
	}
	_fDataIndex->close();
	delete _fDataIndex;
}

template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
T* DBSet<_TIdCompare, _TId, amount, _TEntity, T>::ReadData()
{
	if (_dataId->isempty()) return nullptr;
	T* data = new T[_dataId->getSize()];

	node<DataIndex<_TIdCompare, _TId, amount>>* trav = _dataId->getfirst();
	_TEntity* temp;
	int index = 0;
	while (trav != NULL) {
		temp = &data[index];
		_fData->seekg(trav->info->sizeOffset);
		_fData->read(reinterpret_cast<char*>(temp), _SizeData);
		trav = trav->next;
		index++;
	}
	return data;
}

template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
ArrayList<T>* DBSet<_TIdCompare, _TId, amount, _TEntity, T>::ReadDataArrayList(int size)
{
	ArrayList<T>* data = new ArrayList<T>(size);

	if (_dataId->isempty()) return data;
	node<DataIndex<_TIdCompare, _TId, amount>>* trav = _dataId->getfirst();
	int index = 0;
	_TEntity* temp;
	while (trav != NULL) {
		temp = new T;
		_fData->seekg(trav->info->sizeOffset);
		_fData->read(reinterpret_cast<char*>(temp), _SizeData);
		trav = trav->next;
		data->InsertConst((T*)temp);
	}
	return data;
}

template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
TreeAVL<T>* DBSet<_TIdCompare, _TId, amount, _TEntity, T>::ReadDataTree()
{
	TreeAVL<T>* data = new TreeAVL<T>();
	if (_dataId->isempty()) return data;
	node<DataIndex<_TIdCompare, _TId, amount>>* trav = _dataId->getfirst();
	int index = 0;
	_TEntity* temp;
	while (trav != NULL) {
		temp = new T;
		_fData->seekg(trav->info->sizeOffset);
		_fData->read(reinterpret_cast<char*>(temp), _SizeData);
		trav = trav->next;
		data->InsertConst((T*)temp);
	}
	return data;
}

template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
T** DBSet<_TIdCompare, _TId, amount, _TEntity, T>::ReadDataPtr()
{
	if (_dataId->isempty()) return nullptr;
	T** data = new T * [_dataId->getSize()];
	node<DataIndex<_TIdCompare, _TId, amount>>* trav = _dataId->getfirst();
	int index = 0;
	_TEntity* temp;
	while (trav != NULL) {
		temp = new T;
		_fData->seekg(trav->info->sizeOffset);
		_fData->read(reinterpret_cast<char*>(temp), _SizeData);
		trav = trav->next;
		data[index++] = (T*)temp;
	}
	return data;
}

template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
void DBSet<_TIdCompare, _TId, amount, _TEntity, T>::ReadDataIndex()
{
	_fDataIndex = new std::fstream(_PathIndex, std::ios::binary | std::ios::in);
	if (!_fDataIndex->is_open()) return;
	EntityDataIndex< _TId, amount>* data = NULL;
	int nSize = 0;
	_fDataIndex->read(reinterpret_cast<char*>(&nSize), 4);
	if (nSize < 1) return;
	for (int i = 0; i < nSize; i++)
	{
		data = new DataIndex<_TIdCompare, _TId, amount>;
		_fDataIndex->read((char*)data, _SizeDataIndex);
		_dataId->insertlast((DataIndex<_TIdCompare, _TId, amount>*)data);
	}
	_fDataIndex->close();
	delete _fDataIndex;
}

template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
void DBSet<_TIdCompare, _TId, amount, _TEntity, T>::WriteIndexRemove()
{
	_fDataIndexRemove = new std::fstream(_PathIndexRemove, std::ios::binary | std::ios::out);
	node<int>* trav = _dataOffsetRemove->getfirst();
	int nSize = _dataOffsetRemove->getSize();
	_fDataIndexRemove->write(reinterpret_cast<const char*>(&nSize), 4);
	while (trav != NULL) {
		_fDataIndexRemove->write(reinterpret_cast<char*>(trav->info), 4);
		trav = trav->next;
	}
	_fDataIndexRemove->close();
	delete _fDataIndexRemove;
}

template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T>
void DBSet<_TIdCompare, _TId, amount, _TEntity, T>::ReadDataIndexRemove()
{
	_fDataIndexRemove = new std::fstream(_PathIndexRemove, std::ios::binary | std::ios::in);
	if (!_fDataIndexRemove->is_open()) return;
	int* data = NULL;
	int nSize = 0;
	_fDataIndexRemove->read(reinterpret_cast<char*>(&nSize), 4);
	if (nSize < 1) return;
	for (int i = 0; i < nSize; i++)
	{
		data = new int;
		_fDataIndexRemove->read((char*)data, 4);
		_dataOffsetRemove->insertlast(data);
	}
	_fDataIndex->close();
}

#endif // !DBSET_CPP
