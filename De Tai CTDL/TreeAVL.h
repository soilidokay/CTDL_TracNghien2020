#ifndef TreeAVL_H
#define TreeAVL_H

#include"IList.h"
#include <memory> 
#include"List.h"

template<class _T>
struct NodeAVl {
	_T* key;
	int bal;
	NodeAVl* left, * right;
	NodeAVl();
};

template<class _T>
class TreeAVL :public IList<_T>
{
public:
	typedef struct NodeAVl<_T>* ptrNodeAVl;
	TreeAVL();
	enum Error
	{
		OK = 2, // trang thai nat can bang balance
		Fail = 1, // trai thai khong can can bang balance
		NONE = -1 // thuc thi that bai
	};
	ptrNodeAVl CreatNode(_T* data);
	//
	//them mot nut
	//
	int InsertNodeAVl(_T* data);
	//xoa mot nut
	//
	// nếu hàm trả về none : khong tim thay nut can xoa
	//
	int DeleteNodeAVl(_T* data);
	_T* getValue();
	ptrNodeAVl searchNode(_T* data);
	_T* searchValue(_T* data);
	int getCount();
	//======================
	_T* GetData(int index) override;
	int InsertConst(_T* data) override;
	bool Delete(int index) override;
	void forEach(const ACTION& action, int indexStart = 0, int indexEnd = -1) override;
	bool isempty() override;
	int Search(_T* data) override;
	int getSize()override;
	void RadixSort(const SelectString& select) override;
	void Clear(bool isDeleteData = false) override;
	IList<_T>* filter(const ACTION& action)override;

	~TreeAVL();
private:
	enum Balance
	{
		DeviationLeft = 1, // balance lech trai
		DeviationRight = -1, // balance lech phai
		DeviationCenter = 0 // balance can bang
	};
	int InsertNodeAVL(ptrNodeAVl& pNode, _T* data);

	int DeleteNodeAVl(ptrNodeAVl& pNode, _T* data);

	//ham xoay trai
	void LeftRotate(ptrNodeAVl& pNode);
	//ham xoay phai
	void RightRotate(ptrNodeAVl& pNode);
	//
	//hieu chinh nhanh trai bi lech
	//
	void LeftBalance(ptrNodeAVl& NodeYa);
	//
	//hieu chinh nhanh phai bi lech
	//
	void RightBalance(ptrNodeAVl& NodeYa);
	//
	//can bang khi nut nhanh trai bi xoa
	//
	int EqualBalanceLeft(ptrNodeAVl& pNode);
	//
	//can bang neu nut nhanh trai bi xoa
	//
	int EqualBalanceRight(ptrNodeAVl& pNode);
	//
	//do tim nut ben nhanh trai de thay the nut can xoa
	//
	ptrNodeAVl DelAndSwap_Left(ptrNodeAVl& Node, int& res);
	//
	//do tim nut nhanh phai de thay the
	//
	ptrNodeAVl DelAndSwap_Right(ptrNodeAVl& Node, int& res);
	//
private:
	ptrNodeAVl Tree;
	int count;
};

#ifndef TREEAVL_CPP
#include "TreeAVL.cpp"
#endif // !TREEAVL_CPP


#endif // !TreeAVL_H


