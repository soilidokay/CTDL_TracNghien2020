#include "AppDbContext.h"

AppDbContext::AppDbContext()
{
	MonHocs = new DBSet<std::string, char, Len_IdMonHoc, EntityMonHoc, Monhoc>("MonHoc.txt");
	SinhViens = new DBSet<std::string, char, Len_IdSV, EntiySinhvien, Sinhvien>("SinhVien.txt");
	Questions = new DBSet<long long int, long long int, 1, EntityQuestion, Question>("Question.txt");
	LopHocs = new DBSet<std::string, char, Len_IdLop, EntityLopHoc, LopHoc>("LopHoc.txt");
	Diems = new DBSet <std::string, char, Len_IdMonHoc + Len_IdSV, EntityDiem, Diem>("Diem.txt");
	BangDiems = new  DBSet<std::string, char, 31, EntityDetailAnswer, ModelDetailQuestion>("ChiTietBangDiem.txt");
}

AppDbContext* AppDbContext::getInstance()
{
	if (Instance == NULL) {
		Instance = new AppDbContext();
	}
	return Instance;
}

AppDbContext* AppDbContext::Instance = NULL;
