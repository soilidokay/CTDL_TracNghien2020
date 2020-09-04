#ifndef APPDBCONTEXT_H
#define APPDBCONTEXT_H

#include"DBSet.h"
#include "Database.h"
class AppDbContext
{
public:
	AppDbContext();
	DBSet<std::string, char, Len_IdMonHoc, EntityMonHoc, Monhoc>* MonHocs;
	DBSet<std::string, char, Len_IdSV, EntiySinhvien, Sinhvien>* SinhViens;
	DBSet<long long int, long long int, 1, EntityQuestion, Question>* Questions;
	DBSet<std::string, char, Len_IdLop, EntityLopHoc, LopHoc>* LopHocs;
	DBSet<std::string, char, Len_IdMonHoc + Len_IdSV, EntityDiem, Diem>* Diems;
	DBSet<std::string, char, 31, EntityDetailAnswer, ModelDetailQuestion>* BangDiems;
	static AppDbContext* getInstance();
private:
	static AppDbContext* Instance;

};


#endif // !APPDBCONTEXT_H
