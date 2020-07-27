#ifndef DBSET_H
#define DBSET_H

#include"List.h"
#include <windows.h>
#include <string>
#include <fstream>
#include "CompareData.h"	
#include <type_traits>
#include "ArrayList.h"
#include "TreeAVL.h"

template<typename T, int amount>
struct EntityDataIndex {
	T Id[amount];
	int sizeOffset = -1;
};
template<typename _TIdCompare, typename T, int amount>
struct DataIndex :public EntityDataIndex<T, amount>, public CompareData<_TIdCompare> {

	void setId(_TIdCompare u) {
		if (typeid(_TIdCompare) == typeid(std::string)) {
			_strcopy((char*)Id, amount, *((std::string*) & u));
		}
		else {
			((_TIdCompare*)Id)[0] = *((_TIdCompare*)&u);
		}
	}

	_TIdCompare getId()override {
		if (typeid(_TIdCompare) == typeid(std::string)) {
			std::string temp = (char*)Id;
			return *((_TIdCompare*)&temp);
		}
		else {
			return *((_TIdCompare*)&Id[0]);
		}
	}
};


template<typename _TIdCompare, typename _TId, int amount, typename _TEntity, class T = CompareData<_TIdCompare>>
class DBSet
{
public:
	DBSet(std::string pathdata);
	DBSet(std::string pathdata, int SizeData);
	~DBSet();
	void Add(T* data);
	void Delete(T* data, bool deleteData = false);
	void Update(T* data);
	bool isExit(_TIdCompare id);
	T* Seach(T *data);
	List<T>* ToList();
	T* ToArray();
	T** ToArrayPtr();
	ArrayList<T>* ToArrayList(int size);
	TreeAVL<T>* ToTree();
	int size();
private:
	void CheckAndCreateFile(std::string path);
	void Initial(std::string pathdata);
	void DeleteIndex(DataIndex<_TIdCompare, _TId, amount>* data);
	void AddIdex(DataIndex<_TIdCompare, _TId, amount>* data);
	DataIndex<_TIdCompare, _TId, amount>* GetDataIndex(T* data, int offsetData);
	void WriteIndex();
	void ReadDataIndex();
	void WriteIndexRemove();
	void ReadDataIndexRemove();
	T* ReadData();
	ArrayList<T>* ReadDataArrayList(int size);
	TreeAVL<T>* ReadDataTree();
	T** ReadDataPtr();
	List<DataIndex<_TIdCompare, _TId, amount>>* _dataId;
	List<int>* _dataOffsetRemove;
	int _SizeData;
	int _SizeDataIndex;
	std::string _PathIndex;
	std::string _PathIndexRemove;
	std::fstream* _fData;
	std::fstream* _fDataIndex;
	std::fstream* _fDataIndexRemove;
	CompareData<_TIdCompare>* comparetor = NULL;
};


#ifndef DBSET_CPP
#include "DBSet.cpp"
#endif

#endif // !DBSET_H

