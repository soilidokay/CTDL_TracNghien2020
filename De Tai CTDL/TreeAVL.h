#ifndef TreeAVL_H
#define TreeAVL_H
template<class _T>

struct NodeAVl {
	_T* key;
	int bal;
	NodeAVl* left, *right;
	NodeAVl() {
		key = NULL;
		bal = 0;
		left = NULL;
		right = NULL;
	}
};

template<class _T>
class TreeAVL
{
public:
	typedef struct NodeAVl<_T>* ptrNodeAVl;
	TreeAVL() {
		Tree = NULL; count = 0;
	}
	enum Error
	{
		OK = 2, // trang thai nat can bang balance
		Fail = 1, // trai thai khong can can bang balance
		NONE = -1 // thuc thi that bai
	};
	ptrNodeAVl CreatNode(_T* data) {
		ptrNodeAVl _node = new NodeAVl<_T>;
		if (_node != NULL) {
			_node->key = data;
			_node->bal = 0;
		}
		return _node;
	}
	//
	//them mot nut
	//
	int InsertNodeAVl(_T* data) {
		int err = InsertNodeAVL(Tree, data);
		if (err == OK) ++count;
		return err;
	}
	//xoa mot nut
	//
	// nếu hàm trả về none : khong tim thay nut can xoa
	//
	int DeleteNodeAVl(_T* data) {
		int err DeleteNodeAVl(Tree, data);
		if (err == OK)--count;
		return err;
	}
	ptrNodeAVl getValue() { return Tree; }
	_T* getvalue() { return Tree->key; }
	bool isempty() { return Tree == NULL; }
	ptrNodeAVl searchNode(_T* data) {
		ptrNodeAVl temp = Tree;
		if (Tree == NULL)return NULL;
		while (temp != NULL)
		{
			if (*temp->key > *data) temp = temp->right;
			if (*temp->key < *data) temp = temp->left;
			else return temp;
		}
	}
	_T* searchValue(_T* data) {
		return searchNode(data)->key;
	}
	int getCount() { return count; }
	~TreeAVL() {};
private:
	enum Balance
	{
		DeviationLeft = 1, // balance lech trai
		DeviationRight = -1, // balance lech phai
		DeviationCenter = 0 // balance can bang
	};
	int InsertNodeAVL(ptrNodeAVl &pNode, _T* data) {
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
			if (*pNode->key > *data) {
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

	int DeleteNodeAVl(ptrNodeAVl &pNode, _T* data) {
		int res = NONE;
		if (pNode != NULL) {
			if (*pNode->key > *data) {
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
				if (pNode->right != NULL&&pNode->left != NULL) {
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

	//ham xoay trai
	void LeftRotate(ptrNodeAVl &pNode) {
		ptrNodeAVl tempNode = pNode;
		pNode = pNode->right;
		tempNode->right = pNode->left;
		pNode->left = tempNode;
	}
	//ham xoay phai
	void RightRotate(ptrNodeAVl &pNode) {
		ptrNodeAVl tempNode = pNode;
		pNode = pNode->left;
		tempNode->left = pNode->right;
		pNode->right = tempNode;
	}
	//
	//hieu chinh nhanh trai bi lech
	//
	void LeftBalance(ptrNodeAVl &NodeYa) {
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
	//
	//hieu chinh nhanh phai bi lech
	//
	void RightBalance(ptrNodeAVl &NodeYa) {
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
	//
	//can bang khi nut nhanh trai bi xoa
	//
	int EqualBalanceLeft(ptrNodeAVl &pNode) {
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
	//
	//can bang neu nut nhanh trai bi xoa
	//
	int EqualBalanceRight(ptrNodeAVl &pNode) {
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
	//
	//do tim nut ben nhanh trai de thay the nut can xoa
	//
	ptrNodeAVl DelAndSwap_Left(ptrNodeAVl &Node, int &res) {
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
	//
	//do tim nut nhanh phai de thay the
	//
	ptrNodeAVl DelAndSwap_Right(ptrNodeAVl &Node, int &res) {
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
	//
private:
	ptrNodeAVl Tree;
	int count;
};

#endif // !TreeAVL_H
