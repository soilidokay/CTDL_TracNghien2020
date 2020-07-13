#include <iostream>
#include <string>

using namespace std;
struct Person {
	string Ten;
	string diachi;
};
struct Node {
	Person *per;
	Node * _next;
};

struct List {
	Node *_pH, *_pT;
};

Node * TaoNode(Person * p) {
	Node * tmp = new Node;
	tmp->per = p;
	tmp->_next = NULL;
	return tmp;
}
void Insert(List &l, Node * node) {
	if (l._pH != NULL) {
		l._pT->_next = node;
		l._pT = node;
	}
	else {
		l._pH = l._pT = node;
	}
}

// Tạo động Person và nhập liệu
// sau đó trả ra ngoài
Person * NhapPerson() {
	
	Person * p = new Person;
	cout << "Nhap ten :";
	getline(cin, p->Ten);
	cout << "Nhap dia chi :";
	getline(cin, p->diachi);
	return p;
}

int main() {
	{
		{
			int a[1000000];
		}
		
	}

	return 0;
}