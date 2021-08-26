#pragma once
#pragma warning(disable:4996)
#include<iostream>
#include<fstream>
using namespace std;

class Persoana {
protected:
	char* nume;
	char cnp[13];

public:
	Persoana();
	Persoana(const char*, char*);
	Persoana(const Persoana&);
	~Persoana();
	Persoana& operator=(const Persoana&);
	friend ostream& operator<<(ostream&, const Persoana&);
	static int testNume(const char* nume);
	static int testCNP(const char* cnp);
	static int caracterAcceptat(char);
};
class Student : public Persoana {
	int punctaj, an;
public:
	Student();
	Student(const char*, char*, int, int);
	Student(const Student&);
	Student& operator=(const Student&);
	friend ostream& operator<<(ostream&, const Student&);
	friend istream& operator>>(istream&, Student&);
	static int testAn(const int an);
	static int testPunctaj(const int punctaj);
};

template <class Element, int MAX_STIVA>
class Stiva {
private:
	Element tab[MAX_STIVA];
	int index_virf;
public:
	Stiva();
	~Stiva();
	void push(Element);
	void pop();
	Element top();
	Element bot(int);
	bool is_empty();
	void afis();
	friend istream& operator >> <Element, MAX_STIVA> (istream&, Stiva<Element, MAX_STIVA>&);
};

class Exceptie {
	char* mesaj;
	int cod;
public:
	Exceptie(const char* mesaj = "", int cod = 0);
	Exceptie(const Exceptie&);
	~Exceptie();
	Exceptie& operator=(const Exceptie&);
	void afisare();
	friend ostream& operator<<(ostream&, const Exceptie&);
};


class LinieGoala :public Exceptie {
public:
	LinieGoala() :Exceptie("Linie goala!", 1) {}
};
class NumarParametriIncorect :public Exceptie {
public:
	NumarParametriIncorect() :Exceptie("Prea putini parametri!", 2) {}
};
class NumeInvalid :public Exceptie {
public:
	NumeInvalid() :Exceptie("Nume invalid!", 3) {}
};
class CnpInvalid :public Exceptie {
public:
	CnpInvalid() :Exceptie("CNP invalid!", 4) {}
};
class PunctajInvalid :public Exceptie {
public:
	PunctajInvalid() :Exceptie("Punctaj invalid!", 5) {}
};
class AnInvalid :public Exceptie {
public:
	AnInvalid() :Exceptie("An invalid!", 6) {}
};