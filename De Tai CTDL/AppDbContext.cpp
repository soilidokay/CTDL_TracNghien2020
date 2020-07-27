#include "AppDbContext.h"

AppDbContext::AppDbContext()
{
	MonHocs = new DBSet<std::string, char, 10, EntityMonHoc, Monhoc>("MonHoc.txt");
	SinhViens = new DBSet<std::string, char, 20, EntiySinhvien, Sinhvien>("SinhVien.txt");
	Questions = new DBSet<long long int, long long int, 1, EntityQuestion, Question>("Question.txt");
	LopHocs = new DBSet<std::string, char, 10, EntityLopHoc, LopHoc>("LopHoc.txt");
	Diems = new DBSet <std::string, char, 10, EntityDiem, Diem>("Diem.txt");
	BangDiems = new  DBSet<std::string, char, 50, EntityDetailAnswer, ModelDetailQuestion>("ChiTietBangDiem.txt");
}

AppDbContext* AppDbContext::getInstance()
{
	if (Instance == NULL) {
		Instance = new AppDbContext();
	}
	return Instance;
}

AppDbContext* AppDbContext::Instance = NULL;
