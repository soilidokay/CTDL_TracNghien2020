#ifndef TREEAVL_CPP
#define TREEAVL_CPP

#ifndef TREEAVL_H
#include"TreeAVL.h"
#endif // !TREEAVL_H

template<class _T>
NodeAVl<_T>::NodeAVl()
{
	key = NULL;
	bal = 0;
	left = NULL;
	right = NULL;
}

template<class _T>
TreeAVL<_T>::TreeAVL()
{
	Tree = NULL; count = 0;
}

template<class _T>
NodeAVl<_T>* TreeAVL<_T>::CreatNode(_T* data)
{
	ptrNodeAVl _node = new NodeAVl<_T>;
	if (_node != NULL) {
		_node->key = data;
		_node->bal = 0;
	}
	return _node;
}

template<class _T>
int TreeAVL<_T>::InsertNodeAVl(_T* data)
{
	int err = InsertNodeAVL(Tree, data);
	if (err != NONE) ++count;
	return err;
}

template<class _T>
int TreeAVL<_T>::DeleteNodeAVl(_T* data)
{
	int err = DeleteNodeAVl(Tree, data);
	if (err == OK)--count;
	return err;
}

template<class _T>
_T* TreeAVL<_T>::getValue()
{
	return Tree->key;
}

template<class _T>
_T* TreeAVL<_T>::GetData(int index)
{
	if (index < 0 || index >= getSize()) return NULL;

	int size = getSize() + 1;
	int indexHead = 0, indexLast = 1;
	std::unique_ptr<NodeAVl<_T>* []> queue{ new NodeAVl<_T> * [size] {} };
	NodeAVl<_T>* trav = NULL;

	queue[indexHead] = Tree;

	while (indexHead < index) {
		trav = queue[indexHead++];
		if (trav->left != NULL) {
			queue[indexLast++] = trav->left;
		}
		if (trav->right != NULL) {
			queue[indexLast++] = trav->right;
		}
	}


	return queue[indexHead]->key;
}

template<class _T>
int TreeAVL<_T>::InsertConst(_T* data)
{
	int err = InsertNodeAVl(data);
	if (err != NONE) {
		return Search(data);
	}
	return -1;
}

template<class _T>
bool TreeAVL<_T>::Delete(int index)
{
	_T* data = GetData(index);
	if (data == NULL) return false;
	delete data;
	return DeleteNodeAVl(data);
}

template<class _T>
void TreeAVL<_T>::forEach(const ACTION& action, int indexStart, int indexEnd)
{
	if (indexStart < 0) return;
	if (indexStart >= getSize()) indexStart = 0;

	int indexEndTemp = getSize();
	if (indexEnd > -1) {
		indexEndTemp = indexEnd >= getSize() ? getSize() : indexEnd + 1;
	}
	int indexHead = 0, indexLast = 1;
	int size = getSize() + 1;
	std::unique_ptr<NodeAVl<_T>* []> queue{ new NodeAVl<_T> * [size] {} };
	NodeAVl<_T>* trav = NULL;

	if (!isempty())queue[indexHead] = Tree;

	while (indexHead < indexStart) {
		trav = queue[indexHead];
		if (trav->left != NULL) {
			queue[indexLast] = trav->left;
			++indexLast;
		}
		if (trav->right != NULL) {
			queue[indexLast] = trav->right;
			++indexLast;
		}
		++indexHead;
	}

	for (; indexHead < indexEndTemp; indexHead++)
	{
		trav = queue[indexHead];

		if (!action(trav->key, indexHead)) return;

		if (trav->left != NULL) {
			queue[indexLast] = trav->left;
			++indexLast;
		}
		if (trav->right != NULL) {
			queue[indexLast] = trav->right;
			++indexLast;
		}
	}

	while (indexHead <= indexEnd) if (!action(NULL, indexHead++)) return;
}

template<class _T>
bool TreeAVL<_T>::isempty()
{
	return Tree == NULL;
}

template<class _T>
int TreeAVL<_T>::Search(_T* data)
{
	if (data == NULL) return -1;
	int indexHead = 0, indexLast = 1;
	int size = getSize() + 1;

	std::unique_ptr<NodeAVl<_T>* []> queue{ new NodeAVl<_T> * [size] {} };

	NodeAVl<_T>* trav = NULL;

	if (!isempty())queue[indexHead] = Tree;

	while (indexHead < getSize()) {
		trav = queue[indexHead];
		if (*data == *trav->key) return indexHead;
		if (trav->left != NULL) {
			queue[indexLast++] = trav->left;
		}
		if (trav->right != NULL) {
			queue[indexLast++] = trav->right;
		}
		++indexHead;
	}
	return -1;
}

template<class _T>
int TreeAVL<_T>::getSize()
{
	return getCount();
}

template<class _T>
void TreeAVL<_T>::RadixSort(const SelectString& select)
{
}

template<class _T>
void TreeAVL<_T>::Clear(bool isDeleteData)
{
	if (isempty()) return;
	int indexHead = 0, indexLast = 1;
	NodeAVl<_T>** queue = new NodeAVl<_T> * [getSize()];
	NodeAVl<_T>* trav = NULL;

	queue[indexHead] = Tree;

	while (indexHead < getSize()) {
		trav = queue[indexHead++];
		if (trav->left != NULL) {
			queue[indexLast++] = trav->left;
		}
		if (trav->right != NULL) {
			queue[indexLast++] = trav->right;
		}
		if (isDeleteData) {
			delete trav->key;
		}
		delete trav;
	}
}

template<class _T>
IList<_T>* TreeAVL<_T>::filter(const ACTION& action)
{
	IList<_T>* temp = new List<_T>();

	int indexHead = 0, indexLast = 1;
	int size = getSize() + 1;
	std::unique_ptr<NodeAVl<_T>* []> queue{ new NodeAVl<_T> * [size] {} };

	NodeAVl<_T>* trav = NULL;

	if (!isempty())queue[indexHead] = Tree;

	while (indexHead < getSize()) {
		trav = queue[indexHead];
		if (action(trav->key, indexHead)) {
			temp->InsertConst(trav->key);
		}
		if (trav->left != NULL) {
			queue[indexLast++] = trav->left;
		}
		if (trav->right != NULL) {
			queue[indexLast++] = trav->right;
		}
		++indexHead;
	}
	//forEach([&](_T* item, int index) {
	//	if (action(item, index)) {
	//		temp->InsertNodeAVl(item);
	//	}
	//	return true;
	//	}
	//);
	return temp;
}


template<class _T>
NodeAVl<_T>* TreeAVL<_T>::searchNode(_T* data)
{
	ptrNodeAVl temp = Tree;
	if (Tree == NULL)return NULL;
	while (temp != NULL)
	{
		if (*data > * temp->key) temp = temp->right;
		else if (*data < *temp->key) temp = temp->left;
		else return temp;
	}
	return NULL;
}

template<class _T>
_T* TreeAVL<_T>::searchValue(_T* data)
{
	auto temp = searchNode(data);
	if (temp == NULL) return NULL;
	return temp->key;
}

template<class _T>
int TreeAVL<_T>::getCount()
{
	return count;
}

template<class _T>
TreeAVL<_T>::~TreeAVL()
{}
template<class _T>
int TreeAVL<_T>::InsertNodeAVL(ptrNodeAVl& pNode, _T* data)
{
	int res = NONE;
	if (pNode == NULL) {
		pNode = CreatNode(data);
		if (pNode == NULL) {
			return NONE;
		}
		return OK;
	}
	else
	{
		if (*pNode->key > * data) {
			res = InsertNodeAVL(pNode->left, data);
			if (res == OK)
				// hieu chinh balance va xoay 
				switch (pNode->bal) {
				case DeviationCenter:
					pNode->bal = DeviationLeft;
					return OK;
				case DeviationLeft:
					LeftBalance(pNode);
					return Fail;
				case DeviationRight:
					pNode->bal = DeviationCenter;
					return Fail;
				default:
					break;
				}
		}
		else if (*pNode->key < *data) {
			res = InsertNodeAVL(pNode->right, data);
			if (res == OK)
				switch (pNode->bal)
				{
				case DeviationCenter:
					pNode->bal = DeviationRight;
					return OK;
				case DeviationLeft:
					pNode->bal = DeviationCenter;
					return Fail;
				case DeviationRight:
					RightBalance(pNode);
					return Fail;
				default:
					break;
				}
		}
		else return NONE;
	}
	return res;
}
template<class _T>
int TreeAVL<_T>::DeleteNodeAVl(ptrNodeAVl& pNode, _T* data)
{
	int res = NONE;
	if (pNode != NULL) {
		if (*pNode->key > * data) {
			res = DeleteNodeAVl(pNode->left, data);
			if (res == OK) return EqualBalanceLeft(pNode);
		}
		else if (*pNode->key < *data) {
			res = DeleteNodeAVl(pNode->right, data);
			if (res == OK) return EqualBalanceRight(pNode);
		}
		else
		{
			//
			//truong hop nut co du hai nhanh
			//
			if (pNode->right != NULL && pNode->left != NULL) {
				ptrNodeAVl temp = DelAndSwap_Left(pNode->left, res);
				temp->bal = pNode->bal;
				temp->left = pNode->left;
				temp->right = pNode->right;
				delete pNode;
				pNode = temp;
				if (res == OK) return EqualBalanceLeft(pNode);
			}
			else if (pNode->left != NULL) delete DelAndSwap_Left(pNode, res);
			else if (pNode->right != NULL) delete DelAndSwap_Right(pNode, res);
			else {
				ptrNodeAVl temp = pNode;
				pNode = NULL;
				delete temp;
				return OK;
			}
		}
	}
	return res;
}
template<class _T>
void TreeAVL<_T>::LeftRotate(ptrNodeAVl& pNode)
{
	ptrNodeAVl tempNode = pNode;
	pNode = pNode->right;
	tempNode->right = pNode->left;
	pNode->left = tempNode;
}
template<class _T>
void TreeAVL<_T>::RightRotate(ptrNodeAVl& pNode)
{
	ptrNodeAVl tempNode = pNode;
	pNode = pNode->left;
	tempNode->left = pNode->right;
	pNode->right = tempNode;
}
template<class _T>
void TreeAVL<_T>::LeftBalance(ptrNodeAVl& NodeYa)
{
	switch (NodeYa->left->bal)
	{
	case DeviationLeft:
		RightRotate(NodeYa);
		NodeYa->bal = DeviationCenter;
		NodeYa->right->bal = DeviationCenter;
		break;
	case DeviationRight:
		LeftRotate(NodeYa->left);
		RightRotate(NodeYa);
		switch (NodeYa->bal) {
		case DeviationCenter:
			NodeYa->left->bal = DeviationCenter;
			NodeYa->right->bal = DeviationCenter;
			break;
		case DeviationLeft:
			NodeYa->left->bal = DeviationCenter;
			NodeYa->right->bal = DeviationRight;
			break;
		case DeviationRight:
			NodeYa->left->bal = DeviationLeft;
			NodeYa->right->bal = DeviationCenter;
			break;
		default:
			break;
		};
		NodeYa->bal = DeviationCenter;
		break;
	case DeviationCenter:
		RightRotate(NodeYa);
		NodeYa->bal = DeviationRight;
		NodeYa->right->bal = DeviationLeft;
		break;
	default:
		break;
	}
}
template<class _T>
void TreeAVL<_T>::RightBalance(ptrNodeAVl& NodeYa)
{
	switch (NodeYa->right->bal)
	{
	case DeviationRight:
		LeftRotate(NodeYa);
		NodeYa->bal = DeviationCenter;
		NodeYa->left->bal = DeviationCenter;
		break;
	case DeviationLeft:
		RightRotate(NodeYa->right);
		LeftRotate(NodeYa);
		switch (NodeYa->bal) {
		case DeviationCenter:
			NodeYa->left->bal = DeviationCenter;
			NodeYa->right->bal = DeviationCenter;
			break;
		case DeviationLeft:
			NodeYa->left->bal = DeviationLeft;
			NodeYa->right->bal = DeviationCenter;
			break;
		case DeviationRight:
			NodeYa->left->bal = DeviationCenter;
			NodeYa->right->bal = DeviationRight;
			break;
		default:
			break;
		};
		NodeYa->bal = DeviationCenter;
		break;
	case DeviationCenter:
		LeftRotate(NodeYa);
		NodeYa->bal = DeviationLeft;
		NodeYa->left->bal = DeviationRight;
		break;
	default:
		break;
	}
}
template<class _T>
int TreeAVL<_T>::EqualBalanceLeft(ptrNodeAVl& pNode)
{
	switch (pNode->bal)
	{
	case DeviationCenter:pNode->bal = DeviationRight; return Fail;
	case DeviationLeft:pNode->bal = DeviationCenter; goto Break;
	case DeviationRight:RightBalance(pNode); goto Break;
	Break: if (pNode->bal == DeviationCenter) return OK; else return Fail;
	default:
		break;
		return Fail;
	}
	return Fail;
}
template<class _T>
int TreeAVL<_T>::EqualBalanceRight(ptrNodeAVl& pNode)
{
	switch (pNode->bal)
	{
	case DeviationCenter:pNode->bal = DeviationLeft; return Fail;
	case DeviationRight:pNode->bal = DeviationCenter; goto Break;
	case DeviationLeft:LeftBalance(pNode); goto Break;
	Break: if (pNode->bal == DeviationCenter) return OK; else return Fail;
	default:
		break;
		return Fail;
	}
	return Fail;
}
template<class _T>
NodeAVl<_T>* TreeAVL<_T>::DelAndSwap_Left(ptrNodeAVl& Node, int& res)
{
	ptrNodeAVl temp;
	if (Node->right == NULL)
	{
		temp = Node;
		Node = temp->left;
		res = OK;
	}
	else
	{
		temp = DelAndSwap_Left(Node->right, res);
		if (res == OK) 	res = EqualBalanceRight(Node);
	}
	return temp;
}
template<class _T>
NodeAVl<_T>* TreeAVL<_T>::DelAndSwap_Right(ptrNodeAVl& Node, int& res)
{
	ptrNodeAVl temp;
	if (Node->left == NULL) {
		temp = Node;
		Node = temp->right;
		res = OK;
	}
	else
	{
		temp = DelAndSwap_Right(Node->left, res);
		if (res == OK) res = EqualBalanceLeft(Node);
	}
	return temp;
}
#endif // !TREEAVL_CPP