#ifndef COMPAREDATA_H
#define COMPAREDATA_H
#include <iostream>
#include <string>


#define _cmp(_var1,_var2,_var3,signal) \
switch(signal){\
	case 0 : return( _var1##->getId()##_var2##_var3##.getId());\
	default:\
		return 0;\
		break;\
}

void _strcopy(char* charstr, int nchar, std::string valuestr);
void _PassValue(int* a, int* b);
class ITiltle
{
public:
	virtual void settitle() = 0;
};

template<typename _T>
class CompareData 
{
public:
	CompareData() { _signalSort = 0; }
	bool operator<(CompareData& cmp) { _cmp(this, < , cmp, _signalSort); }
	bool operator>(CompareData& cmp) { _cmp(this, > , cmp, _signalSort); }
	bool operator==(CompareData& cmp) { _cmp(this, == , cmp, _signalSort); }
	bool operator!=(CompareData& cmp) { _cmp(this, != , cmp, _signalSort); }
	bool operator<=(CompareData& cmp) { _cmp(this, <= , cmp, _signalSort); }
	bool operator>=(CompareData& cmp) { _cmp(this, >= , cmp, _signalSort); }
	virtual _T getId() = 0;

	void setsignalSort(int signalSort) { _signalSort = signalSort; }
private:
	int _signalSort;
};
#endif // !COMPAREDATA_H
