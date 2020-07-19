#ifndef APPDBCONTEXT_H
#define APPDBCONTEXT_H

#include"DBSet.h"
#include "Database.h"
class AppDbContext
{
public:
	AppDbContext();
	DBSet<std::string, char, 10, EntityMonHoc, Monhoc>* MonHocs;
	DBSet<std::string, char, 20, EntiySinhvien, Sinhvien>* SinhViens;
	DBSet<long long int, long long int, 1, EntityQuestion, Question>* Questions;
	DBSet<std::string, char, 10, EntityLopHoc, LopHoc>* LopHocs;
	static AppDbContext* getInstance();
private:
	static AppDbContext* Instance;

};


#endif // !APPDBCONTEXT_H
