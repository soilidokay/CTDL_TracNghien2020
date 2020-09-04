//----------------
#pragma warning(disable:4996)

#ifndef DataBase_H
#define DataBase_H


#include <iostream>
#include <iomanip>
#include <string>
#include "List.h"
#include "TreeAVL.h"
#include "CompareData.h"
const char lim = 179;

#define Len_IdMonHoc 11
#define Len_Answer 101

class EntityQuestion {
protected:
	long long int _idquest = '-1';
	char _IdObject[Len_IdMonHoc] = "";
	char _Quest[Len_Answer] = "";
	char _answerA[Len_Answer] = "";
	char _answerB[Len_Answer] = "";
	char _answerC[Len_Answer] = "";
	char _answerD[Len_Answer] = "";
	char _answer = '\0';
};
static std::string CutStr(std::string str, int amount) {
	if (str.length() > amount) {
		return str.substr(0, amount - 3) + "...";
	}
	else {
		return str;
	}
}
class Question : public EntityQuestion, public CompareData<long long int>
{
public:
	Question() {}
	Question(long long int idquest, std::string Quest, std::string answerA, std::string answerB,
		std::string answerC, std::string answerD, char answer)
	{
		_idquest = idquest;
		_strcopy(_Quest, Len_Answer, Quest);
		_strcopy(_answerA, Len_Answer, answerA);
		_strcopy(_answerB, Len_Answer, answerB);
		_strcopy(_answerC, Len_Answer, answerC);
		_strcopy(_answerD, Len_Answer, answerD);
		_answer = answer;
	};
	void setId(long long int idquest) { _idquest = idquest; }
	void setQuest(std::string Quest) { _strcopy(_Quest, Len_Answer, Quest); }
	void setIdObject(std::string IdObject) { _strcopy(_IdObject, Len_Answer, IdObject); }
	void setanswerA(std::string answerA) { _strcopy(_answerA, Len_Answer, answerA); }
	void setanswerB(std::string answerB) { _strcopy(_answerB, Len_Answer, answerB); }
	void setanswerC(std::string answerC) { _strcopy(_answerC, Len_Answer, answerC); }
	void setanswerD(std::string answerD) { _strcopy(_answerD, Len_Answer, answerD); }
	void setanswer(char answer) { _answer = answer; }
	friend std::ostream& operator<<(std::ostream& output, Question* Obj) {
		//char lim = 179;
		output << std::left << std::setfill(' ');
		if (Obj != NULL) {
			output << std::setw(12) << CutStr(Obj->_Quest, 12) << lim
				<< std::setw(12) << CutStr(Obj->_answerA, 12) << lim
				<< std::setw(12) << CutStr(Obj->_answerB, 12) << lim
				<< std::setw(12) << CutStr(Obj->_answerC, 12) << lim
				<< std::setw(12) << CutStr(Obj->_answerD, 12) << lim
				<< std::setw(12) << Obj->_answer << lim;
		}
		else
		{
			output << std::setw(12) << " " << lim
				<< std::setw(12) << " " << lim
				<< std::setw(12) << " " << lim
				<< std::setw(12) << " " << lim
				<< std::setw(12) << " " << lim
				<< std::setw(12) << " " << lim;
		}
		return output;
	}
	static void settitle() {
		std::cout << std::left << std::setfill(' ');
		std::cout << std::setw(3) << ' ' << lim
			<< std::setw(12) << "  Cau Hoi" << lim
			<< std::setw(12) << "    A" << lim
			<< std::setw(12) << "    B" << lim
			<< std::setw(12) << "    C" << lim
			<< std::setw(12) << "    D" << lim
			<< std::setw(12) << "Dap An" << lim;
	}
	static int getSizeTitle() { return 75; }
	long long int getId()override { return _idquest; }
	std::string getQuest() { return _Quest; }
	std::string getIdObject() { return _IdObject; }
	std::string getanswerA() { return _answerA; }
	std::string getanswerB() { return _answerB; }
	std::string getanswerC() { return _answerC; }
	std::string getanswerD() { return _answerD; }
	 char getAnserw() { return _answer; }
	~Question() {};
};

#define Len_Answers 21
class ModelQuestion :public Question {
private:
	char _answers[Len_Answers];
public:
	void setAnswers(std::string answers) { _strcopy(_answers, Len_Answers, answers); }
	std::string getAnswers() { return _answers; }
	friend std::ostream& operator<<(std::ostream& output, ModelQuestion* Obj) {
		//char lim = 179;
		output << std::left << std::setfill(' ');
		if (Obj != NULL) {
			output << std::setw(12) << CutStr(Obj->_Quest, 12) << lim
				<< std::setw(12) << CutStr(Obj->_answerA, 12) << lim
				<< std::setw(12) << CutStr(Obj->_answerB, 12) << lim
				<< std::setw(12) << CutStr(Obj->_answerC, 12) << lim
				<< std::setw(12) << CutStr(Obj->_answerD, 12) << lim
				<< std::setw(20) << Obj->_answers << lim;
		}
		else
		{
			output << std::setw(12) << " " << lim
				<< std::setw(12) << " " << lim
				<< std::setw(12) << " " << lim
				<< std::setw(12) << " " << lim
				<< std::setw(12) << " " << lim
				<< std::setw(20) << " " << lim;
		}
		return output;
	}
	static void settitle() {
		std::cout << std::left << std::setfill(' ');
		std::cout << std::setw(3) << ' ' << lim
			<< std::setw(12) << "  Cau Hoi" << lim
			<< std::setw(12) << "    A" << lim
			<< std::setw(12) << "    B" << lim
			<< std::setw(12) << "    C" << lim
			<< std::setw(12) << "    D" << lim
			<< std::setw(20) << "Dap An" << lim;
	}
	static int getSizeTitle() { return 83; }
};

#define Len_TenMonHoc 31
class EntityMonHoc {
protected:
	char _idObject[Len_IdMonHoc] = "";
	char _nameobj[Len_TenMonHoc] = "";
};

class Monhoc : public EntityMonHoc, public CompareData<std::string>
{
public:
	Monhoc() {
	}
	Monhoc(std::string idobject, std::string nameObj) {
		_strcopy(_idObject, Len_IdMonHoc, idobject);
		_strcopy(_nameobj, Len_TenMonHoc, nameObj);
	}

	void setidobject(std::string idobject) { _strcopy(_idObject, Len_IdMonHoc, idobject); }
	void setname(std::string nameobj) { _strcopy(_nameobj, Len_TenMonHoc, nameobj); }
	void setLstQuestion(IList<Question>* lstQuestion) { LstQuest = lstQuestion; }

	std::string getId()override { return _idObject; }
	std::string getName() { return _nameobj; }
	IList<Question>* GetLstQuetion() { return LstQuest; }
	~Monhoc() {}
	friend std::ostream& operator<<(std::ostream& output, Monhoc* Obj) {
		//char lim = 179;
		output << std::left << std::setfill(' ');
		if (Obj != NULL) {
			output << std::setw(20)
				<< Obj->getId()
				<< lim
				<< std::setw(20)
				<< Obj->getName() << lim;
		}
		else
		{
			output << std::setw(20) << ' ' << lim
				<< std::setw(20) << ' ' << lim;
		}
		return output;
	}
	static void settitle() {
		std::cout << std::left << std::setfill(' ');
		std::cout << std::setw(3) << ' ' << lim
			<< std::setw(20) << "       ID" << lim
			<< std::setw(20) << "             Mon hoc" << lim;
	}
	static int getSizeTitle() { return 43; }
private:
	IList<Question>* LstQuest = NULL;
};
#define Len_IdSV 21
class EntityDiem {
protected:
	char _MaMH[Len_IdMonHoc];
	double _Scores;
	char _MaSV[Len_IdSV];
};


class Diem :public EntityDiem, public CompareData<std::string> {
public:
	Diem() {}
	Diem(std::string MaMH, std::string MaSV, double Mark) {
		_strcopy(_MaMH, Len_IdMonHoc, MaMH);
		_strcopy(_MaSV, Len_IdSV, MaSV);
		_Scores = Mark;
	}
	void setObjectId(std::string ObjectId) { _strcopy(_MaMH, Len_IdMonHoc, ObjectId); }
	std::string getObjectId() { return _MaMH; }
	void setStudentId(std::string studentid) { _strcopy(_MaSV, Len_IdSV, studentid); }
	std::string getStudentId() { return _MaSV; }
	void setScores(double Scores) { _Scores = Scores; }
	double getScores() { return _Scores; }
	std::string getId()override { return getObjectId() + getStudentId(); }
};

#define Len_LastName 31
#define Len_FirstName 11
#define Len_Pass 16
#define Len_IdLop 11
class EntiySinhvien {
protected:
	char _idStudent[Len_IdSV] = "";
	char _lastname[Len_LastName] = "";
	char _firstname[Len_FirstName] = "";
	bool _sex = false;
	char _passWord[Len_Pass] = "";
	char _MaLop[Len_IdLop] = "";
};
class Sinhvien : public EntiySinhvien, public CompareData<std::string>
{
public:
	friend std::ostream& operator<<(std::ostream& output, Sinhvien* Obj) {
		//char lim = 179;
		output << std::left << std::setfill(' ');
		if (Obj != NULL) {
			output << std::setw(15) << Obj->_idStudent << lim
				<< std::setw(20) << Obj->_lastname << lim
				<< std::setw(10) << Obj->_firstname << lim;
			if (Obj->_sex) output << std::setw(10) << "Nam" << lim;
			else output << std::setw(10) << "Nu" << lim;
			output << std::setw(15) << Obj->_passWord << lim;
		}
		else
		{
			output << std::setw(15) << " " << lim
				<< std::setw(20) << " " << lim
				<< std::setw(10) << " " << lim
				<< std::setw(10) << " " << lim
				<< std::setw(15) << " " << lim;
		}
		return output;
	}
	static  void settitle() {
		std::cout << std::left << std::setfill(' ');
		std::cout << std::setw(3) << ' ' << lim
			<< std::setw(15) << "     ID" << lim
			<< std::setw(20) << "        HO" << lim
			<< std::setw(10) << " Ten" << lim
			<< std::setw(10) << "Gioi Tinh" << lim
			<< std::setw(15) << "    PassWord" << lim;
	}
	static  int getSizeTitle() { return 73; }
	enum SEX
	{
		nam = 1, nu = 0
	};
	Sinhvien() {}
	Sinhvien(std::string idstudent, std::string lastname, std::string firstname, bool sex, std::string pass) {
		_strcopy(_idStudent, Len_IdSV, idstudent);
		_strcopy(_lastname, Len_LastName, lastname);
		_strcopy(_firstname, Len_FirstName, firstname);
		_strcopy(_passWord, Len_Pass, pass);
		_sex = sex;
		_LstDiem = new List<Diem>;
	}
	void setidstudent(std::string idstudent) { _strcopy(_idStudent, Len_IdSV, idstudent); }
	void setlastname(std::string lastname) { _strcopy(_lastname, Len_LastName, lastname); }
	void setfirstname(std::string firstname) { _strcopy(_firstname, Len_FirstName, firstname); }
	void setsex(bool sex) { _sex = sex; }
	void setLstDiem(List<Diem>* lstDiem) { _LstDiem = lstDiem; }
	void SetPass(std::string pass) { _strcopy(_passWord, Len_Pass, pass); }
	void SetMaLop(std::string malop) { _strcopy(_MaLop, Len_IdLop, malop); }
	std::string getId() { return _idStudent; }
	std::string getlastname() { return _lastname; }
	std::string getfirstname() { return _firstname; }
	bool getsex() { return _sex; }
	std::string getPass() { return _passWord; }
	std::string getMaLop() { return _MaLop; }

	List<Diem>* getLstDiem() { return _LstDiem; }
	~Sinhvien() {}
private:
	List<Diem>* _LstDiem = NULL;
};
#define Len_Mark 11
class ModelMarkSinhvien : public Sinhvien
{
public:
	friend std::ostream& operator<<(std::ostream& output, ModelMarkSinhvien* Obj) {
		//char lim = 179;
		output << std::left << std::setfill(' ');
		if (Obj != NULL) {
			output << std::setw(15) << Obj->_idStudent << lim
				<< std::setw(20) << Obj->_lastname << lim
				<< std::setw(10) << Obj->_firstname << lim
				<< std::setw(15) << std::string(Obj->_Mark).substr(0, 4) << lim;
		}
		else
		{
			output << std::setw(15) << " " << lim
				<< std::setw(20) << " " << lim
				<< std::setw(10) << " " << lim
				<< std::setw(15) << " " << lim;
		}
		return output;
	}
	static void settitle() {
		std::cout << std::left << std::setfill(' ');
		std::cout << std::setw(3) << ' ' << lim
			<< std::setw(15) << "     ID" << lim
			<< std::setw(20) << "        HO" << lim
			<< std::setw(10) << " Ten" << lim
			<< std::setw(15) << "    Diem" << lim;
	}
	static int getSizeTitle() { return 63; }
	void setMark(std::string mark) { _strcopy(_Mark, Len_Mark, mark); }
	std::string getMark() { return _Mark; }
private:
	char _Mark[Len_Mark];
};

#define Len_TenLop 11
#define Len_NienKhoa 11
class EntityLopHoc {
protected:
	char _idclass[Len_IdLop] = "";
	char _NameClass[Len_TenLop] = "";
	char _SchoolYear[Len_NienKhoa] = "";
};
class LopHoc :public EntityLopHoc, public CompareData<std::string>
{
public:
	friend std::ostream& operator<<(std::ostream& output, LopHoc* Obj) {
		//char lim = 179;
		output << std::left << std::setfill(' ');
		if (Obj != NULL) {
			output << std::setw(20) << Obj->getId() << lim
				<< std::setw(20) << Obj->getName() << lim
				<< std::setw(20) << Obj->getSchoolYear() << lim;
		}
		else
		{
			output << std::setw(20) << ' ' << lim
				<< std::setw(20) << ' ' << lim
				<< std::setw(20) << ' ' << lim;
		}
		return output;
	}
	static void settitle() {
		std::cout << std::left << std::setfill(' ')
			<< std::setw(3) << ' ' << lim
			<< std::setw(20) << "         ID" << lim
			<< std::setw(20) << "         Lop hoc" << lim
			<< std::setw(20) << "  Nien khoa" << lim;

	}
	static int getSizeTitle() { return 63; }
	LopHoc() {}
	LopHoc(std::string idclass, std::string nameclass, std::string schoolyear) {
		_strcopy(_idclass, 10, idclass);
		_strcopy(_NameClass, 10, nameclass);
		_strcopy(_SchoolYear, 10, schoolyear);
		_LSinhvien = new  List<Sinhvien>;
	}
	void setid(std::string idclass) { _strcopy(_idclass, 11, idclass); }
	void setnameclass(std::string nameclass) { _strcopy(_NameClass, 11, nameclass); }
	void setschoolyear(std::string schoolyear) { _strcopy(_SchoolYear, 11, schoolyear); }
	void setLSinhvien(List<Sinhvien>* LSinhvien) { _LSinhvien = LSinhvien; }

	std::string getId() { return _idclass; }
	std::string getName() { return _NameClass; }
	std::string getSchoolYear() { return _SchoolYear; }
	List<Sinhvien>* getLSinhvien() { return _LSinhvien; }

	~LopHoc() {}
private:
	List<Sinhvien>* _LSinhvien = NULL;
};

class EntitySchoolYear {
protected:
	char _SchoolYear[Len_NienKhoa] = "";
	int _idSchoolYear = -1;
};
class SchoolYear :public EntitySchoolYear, public CompareData<int> {
public:
	SchoolYear(int idSchoolYear, std::string SchoolYear) {
		_idSchoolYear = idSchoolYear;
		_strcopy(_SchoolYear, Len_NienKhoa, SchoolYear);
	}
	void SetSchoolYear(std::string schoolyear) {
		_strcopy(_SchoolYear, Len_NienKhoa, schoolyear);
	}
	static void settitle() {
		std::cout << std::left << std::setfill(' ')
			<< std::setw(3) << ' ' << lim
			<< std::setw(20) << "  Nien khoa" << lim;

	}
	static int getSizeTitle() { return 23; }
	void setId(int idSchoolYear) { _idSchoolYear = idSchoolYear; }
	void setLstLopHop(List<LopHoc>* lstLopHoc) { _lstLopHop = lstLopHoc; }
	int getId()override { return _idSchoolYear; }
	List<LopHoc>* getLstLopHoc() { return _lstLopHop; }
	friend std::ostream& operator<<(std::ostream& output, SchoolYear* Obj) {
		//char lim = 179;
		output << std::left << std::setfill(' ');
		if (Obj != NULL) {
			output << std::setw(20) << Obj->GetSchoolYear() << lim;
		}
		else
		{
			output << std::setw(20) << ' ' << lim;
		}
		return output;
	}
	std::string GetSchoolYear() { return _SchoolYear; }
private:
	List<LopHoc>* _lstLopHop = NULL;
};

class ModelAnswer :public CompareData<int> {
public:
	ModelAnswer(int id, char answer) {
		_Answer = answer;
		_id = id;
	}
	void setAnswer(char answer) { _Answer = answer; };
	char getAnswer() { return _Answer; }
	static void settitle() {
		std::cout << std::left << std::setfill(' ')
			<< std::setw(3) << ' ' << lim
			<< std::setw(10) << "Anwser";
	}
	void setId(int id) { _id = id; }
	int getId()override { return _id; }
	static int getSizeTitle() { return 13; }
	friend std::ostream& operator<<(std::ostream& output, ModelAnswer* Obj) {
		//char lim = 179;
		output << std::left << std::setfill(' ');
		if (Obj != NULL) {
			output << std::setw(20) << Obj->getAnswer();
		}
		else
		{
			output << std::setw(20) << ' ';
		}
		return output;
	}
private:
	char _Answer;
	int _id;
};
#define Len_MHandMSV 31
class EntityDetailAnswer {
protected:
	char _IdMhandSv[Len_MHandMSV];
	long long int _idquest = '-1';
	int _Answer;
};
class  ModelDetailQuestion :public EntityDetailAnswer, public CompareData<std::string> {
public:
	ModelDetailQuestion() {}
	ModelDetailQuestion(std::string IdMhandSv, int answer, long long int idQuestion) {
		_strcopy(_IdMhandSv, Len_MHandMSV, IdMhandSv);
		_Answer = answer;
		_idquest = idQuestion;
	}
	void setMhandSv(std::string IdMhandSv) { _strcopy(_IdMhandSv, Len_MHandMSV, IdMhandSv); }
	std::string getMhAndSv() { return _IdMhandSv; }
	std::string getId() override { return _IdMhandSv + std::to_string(_idquest); }
	void setAnswer(int answer) { _Answer = answer; }
	int getAnswer() { return _Answer; }
	void setIdQuestion(long long int idQuestion) { _idquest = idQuestion; }
	long long int getIdQuestion() { return _idquest; }
private:
};

#endif // !DataBase_H