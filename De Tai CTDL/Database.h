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

class EntityQuestion {
protected:
	long long int _idquest = '-1';
	char _IdObject[10] = "";
	char _Quest[100] = "";
	char _answerA[100] = "";
	char _answerB[100] = "";
	char _answerC[100] = "";
	char _answerD[100] = "";
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
		_strcopy(_Quest, 100, Quest);
		_strcopy(_answerA, 100, answerA);
		_strcopy(_answerB, 100, answerB);
		_strcopy(_answerC, 100, answerC);
		_strcopy(_answerD, 100, answerD);
		_answer = answer;
	};
	void setId(long long int idquest) { _idquest = idquest; }
	void setQuest(std::string Quest) { _strcopy(_Quest, 100, Quest); }
	void setIdObject(std::string IdObject) { _strcopy(_IdObject, 100, IdObject); }
	void setanswerA(std::string answerA) { _strcopy(_answerA, 100, answerA); }
	void setanswerB(std::string answerB) { _strcopy(_answerB, 100, answerB); }
	void setanswerC(std::string answerC) { _strcopy(_answerC, 100, answerC); }
	void setanswerD(std::string answerD) { _strcopy(_answerD, 100, answerD); }
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

class EntityMonHoc {
protected:
	char _idObject[10] = "";
	char _nameobj[30] = "";
};

class Monhoc : public EntityMonHoc, public CompareData<std::string>
{
public:
	Monhoc() {
	}
	Monhoc(std::string idobject, std::string nameObj) {
		_strcopy(_idObject, 10, idobject);
		_strcopy(_nameobj, 30, nameObj);
	}

	void setidobject(std::string idobject) { _strcopy(_idObject, 10, idobject); }
	void setname(std::string nameobj) { _strcopy(_nameobj, 30, nameobj); }
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
private:
	IList<Question>* LstQuest = NULL;
};

class EntiySinhvien {
protected:
	char _idStudent[20] = "";
	char _lastname[30] = "";
	char _firstname[10] = "";
	bool _sex = false;
	char _passWord[15] = "";
	char _MaLop[10] = "";
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
	static void settitle() {
		std::cout << std::left << std::setfill(' ');
		std::cout << std::setw(3) << ' ' << lim
			<< std::setw(15) << "     ID" << lim
			<< std::setw(20) << "        HO" << lim
			<< std::setw(10) << " Ten" << lim
			<< std::setw(10) << "Gioi Tinh" << lim
			<< std::setw(15) << "    PassWord" << lim;
	}
	enum SEX
	{
		nam = 1, nu = 0
	};
	Sinhvien() {}
	Sinhvien(std::string idstudent, std::string lastname, std::string firstname, bool sex, std::string pass) {
		_strcopy(_idStudent, 20, idstudent);
		_strcopy(_lastname, 20, lastname);
		_strcopy(_firstname, 10, firstname);
		_strcopy(_passWord, 30, pass);
		_sex = sex;
		_LMonHoc = new List<Monhoc>;
	}
	void setidstudent(std::string idstudent) { _strcopy(_idStudent, 20, idstudent); }
	void setlastname(std::string lastname) { _strcopy(_lastname, 20, lastname); }
	void setfirstname(std::string firstname) { _strcopy(_firstname, 10, firstname); }
	void setsex(bool sex) { _sex = sex; }
	void setLMonhoc(List<Monhoc>* LMonhoc) { _LMonHoc = LMonhoc; }
	void SetPass(std::string pass) { _strcopy(_passWord, 30, pass); }
	void SetMaLop(std::string malop) { _strcopy(_MaLop, 30, malop); }

	std::string getId() { return _idStudent; }
	std::string getlastname() { return _lastname; }
	std::string getfirstname() { return _firstname; }
	bool getsex() { return _sex; }
	std::string getPass() { return _passWord; }
	std::string getMaLop() { return _MaLop; }

	List<Monhoc>* getLMonhoc() { return _LMonHoc; }
	~Sinhvien() {}
private:
	List<Monhoc>* _LMonHoc = NULL;
};
class EntityLopHoc {
protected:
	char _idclass[10] = "";
	char _NameClass[10] = "";
	char _SchoolYear[10] = "";
};
class LopHoc :public EntityLopHoc, public CompareData<std::string>
{
public:
	friend std::ostream& operator<<(std::ostream& output, LopHoc* Obj) {
		//char lim = 179;
		output << std::left << std::setfill(' ');
		if (Obj != NULL) {
			output << std::setw(20) << Obj->getId() << lim
				<< std::setw(30) << Obj->getName() << lim
				<< std::setw(20) << Obj->getSchoolYear() << lim;
		}
		else
		{
			output << std::setw(20) << ' ' << lim
				<< std::setw(30) << ' ' << lim
				<< std::setw(20) << ' ' << lim;
		}
		return output;
	}
	static void settitle() {
		std::cout << std::left << std::setfill(' ')
			<< std::setw(3) << ' ' << lim
			<< std::setw(20) << "         ID" << lim
			<< std::setw(30) << "         Lop hoc" << lim
			<< std::setw(20) << "  Nien khoa" << lim;

	}
	LopHoc() {}
	LopHoc(std::string idclass, std::string nameclass, std::string schoolyear) {
		_strcopy(_idclass, 10, idclass);
		_strcopy(_NameClass, 10, nameclass);
		_strcopy(_SchoolYear, 10, schoolyear);
		_LSinhvien = new  List<Sinhvien>;
	}
	void setid(std::string idclass) { _strcopy(_idclass, 10, idclass); }
	void setnameclass(std::string nameclass) { _strcopy(_NameClass, 10, nameclass); }
	void setschoolyear(std::string schoolyear) { _strcopy(_SchoolYear, 10, schoolyear); }
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
	char _SchoolYear[10] = "";
	int _idSchoolYear = -1;
};
class SchoolYear :public EntitySchoolYear, public CompareData<int> {
public:
	SchoolYear(int idSchoolYear,std::string SchoolYear) {
		_idSchoolYear = idSchoolYear;
		_strcopy(_SchoolYear, 10, SchoolYear);
	}
	void SetSchoolYear(std::string schoolyear) {
		_strcopy(_SchoolYear, 10, schoolyear);
	}
	static void settitle() {
		std::cout << std::left << std::setfill(' ')
			<< std::setw(3) << ' ' << lim
			<< std::setw(20) << "  Nien khoa" << lim;

	}
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


#endif // !DataBase_H