#include "CompareData.h"

void _strcopy(char* charstr, int nchar, std::string valuestr)
{
	int len = valuestr.length();
	len = (len < nchar) ? len : nchar;
	valuestr.copy(charstr, len);
	charstr[len] = 0;
}
void _PassValue(int* a, int* b) {
	a[0] = *b;
}