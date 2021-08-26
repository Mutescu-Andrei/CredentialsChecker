#include "Header.h"

int Persoana::caracterAcceptat(char c) {
	if (c >= 'a' && c <= 'z')return 1;
	if (c >= 'A' && c <= 'Z')return 1;
	if (c == ' ' || c == '-')return 1;
	return 0;
}
int Persoana::testNume(const char* nume) {
	for (int i = 0; i < strlen(nume); i++)
		if (!caracterAcceptat(nume[i]))
			return 0;
	return 1;
}
int Persoana::testCNP(const char* cnp) {
	//S
	if (cnp[0] < '1' || cnp[0]>'8')return 0;
	//AA

	if (cnp[1] < '0' || cnp[1]>'9')return 0;
	if (cnp[2] < '0' || cnp[2]>'9')return 0;
	//LL
	if (cnp[3] < '0' || cnp[3]>'1')return 0;
	if (cnp[4] < '0' || cnp[4]>'9')return 0;
	if (cnp[3] == '1' && cnp[4] > '2')return 0;
	//ZZ

	if (cnp[5] < '0' || cnp[5]>'3')return 0;
	if (cnp[6] < '0' || cnp[6]>'9')return 0;
	if (cnp[5] == '3' && cnp[6] > '1')return 0;
	//JJ
	if (cnp[7] < '0' || cnp[7]>'9')return 0;
	if (cnp[8] < '0' || cnp[8]>'9')return 0;
	int cod = (cnp[7] - '0') * 10 + (cnp[8] - '0');
	if (!((cod >= 1 && cod <= 46) || cod == 51 || cod == 52))return 0;
	//NNN

	if (cnp[9] < '0' || cnp[9]>'9')return 0;
	if (cnp[10] < '0' || cnp[10]>'9')return 0;
	if (cnp[11] < '0' || cnp[11]>'9')return 0;
	if (cnp[9] == '0' && cnp[10] == '0' && cnp[11] == '0')return 0;
	//C

	if (cnp[10] < '0' || cnp[10]>'9')return 0;
	int cod2 = (int(cnp[0]) - '0') * 2 + (int(cnp[1]) - '0') * 7 + (int(cnp[2]) - '0') * 9 + (int(cnp[3]) - '0') * 1 + (int(cnp[4]) - '0') * 4 + (int(cnp[5]) - '0') * 6 + (int(cnp[6]) - '0') * 3 + (int(cnp[7]) - '0') * 5 + (int(cnp[8]) - '0') * 8 + (int(cnp[9]) - '0') * 2 + (int(cnp[10]) - '0') * 7 + (int(cnp[11]) - '0') * 9;
	int rest = cod2 % 11;
	if (rest == 10 && cnp[12] != '1')return 0;

	if (rest < 10 && cnp[12] != char(rest + '0'))return 0;
	return 1;
}
Persoana::Persoana() {
	this->nume = new char[1];
	strcpy(this->nume, "");
	strcpy(this->cnp, "1791010022791");
}
Persoana::Persoana(const char* nume, char* cnp) {
	if (!testNume(nume))
		throw NumeInvalid();
	if (!testCNP(cnp))
		throw CnpInvalid();
	this->nume = new char[strlen(nume) + 1];
	strcpy(this->nume, nume);
	strcpy(this->cnp, cnp);
}
Persoana::Persoana(const Persoana& p) {
	nume = new char[strlen(p.nume) + 1];
	strcpy(nume, p.nume);
	strcpy(cnp, p.cnp);
}
Persoana::~Persoana() {
	if (nume)delete[] nume;
}
Persoana& Persoana::operator=(const Persoana& p) {
	if (this != &p) {
		if (nume)delete[] nume;
		nume = new char[strlen(p.nume) + 1];
		strcpy(nume, p.nume);
		strcpy(cnp, p.cnp);
	}
	return *this;
}
ostream& operator<<(ostream& out, const Persoana& p) {
	out << p.nume << " (" << p.cnp << ")";
	return out;
}
Student::Student() :Persoana() {
	punctaj = 0;
	an = 0;
}
Student::Student(const char* nume, char* cnp, int punctaj, int an) : Persoana(nume, cnp) {
	if (!testAn(an))
		throw AnInvalid();
	if (!testPunctaj(punctaj))
		throw PunctajInvalid();
	this->punctaj = punctaj;
	this->an = an;
}
Student::Student(const Student& s) : Persoana(s) {
	punctaj = s.punctaj;
	an = s.an;
}
Student& Student::operator=(const Student& s) {
	if (this != &s) {
		if (nume)delete[] nume;
		nume = new char[strlen(s.nume) + 1];
		strcpy(nume, s.nume);
		strcpy(cnp, s.cnp);
		punctaj = s.punctaj;
		an = s.an;
	}
	return *this;
}
ostream& operator<<(ostream& out, const Student& s) {
	out << s.nume << " (" << s.cnp << ") :" << endl << "Punctaj: " << s.punctaj << " (an: " << s.an << ")" << endl;
	return out;
}
int Student::testAn(const int an) {
	if (an < 1 || an>3)
		return 0;
	return 1;
}
int Student::testPunctaj(const int punctaj)
{
	if (punctaj < 0 || punctaj>999)
		return 0;
	return 1;


}
istream& operator >> (istream& in, Student& s) {
	char linie[1024];
	in.getline(linie, 1024);
	if (linie != NULL && strlen(linie) >= 0) {
		char* p;
		p = strtok(linie, ",");
		for (int i = 0; i < 4; i++) {
			switch (i) {
			case 0:
				if (p == NULL)
					throw LinieGoala();
				if (s.nume)delete[] s.nume;
				s.nume = new char[strlen(p) + 1];
				if (!s.testNume(p))
					throw NumeInvalid();
				strcpy(s.nume, p);
				break;
			case 1:
				if (!s.testCNP(p))
					throw CnpInvalid();
				strncpy(s.cnp, p, 13);
				break;
			case 2:
				if (p == NULL)
					throw LinieGoala();
				if (!s.testPunctaj(atoi(p)))
					throw PunctajInvalid();
				s.punctaj = atoi(p);

				break;
			case 3:
				if (p == NULL)
					throw LinieGoala();
				if (!s.testAn(atoi(p)))
					throw AnInvalid();
				s.an = atoi(p);
				break;
			}
			p = strtok(NULL, ",");
		}
	}

	return in;
}



template <class Element, int MAX_STIVA>
Stiva<Element, MAX_STIVA>::Stiva() {
	index_virf = -1;
}
template <class Element, int MAX_STIVA>
Stiva<Element, MAX_STIVA>::~Stiva() {}

template <class Element, int MAX_STIVA>
void Stiva<Element, MAX_STIVA>::push(Element e) {
	if (index_virf < MAX_STIVA - 1)
		tab[++index_virf] = e;
}
template <class Element, int MAX_STIVA>
void Stiva<Element, MAX_STIVA>::pop() {
	if (index_virf >= 0)
		index_virf--;
}
template <class Element, int MAX_STIVA>
Element Stiva<Element, MAX_STIVA>::top() {
	if (index_virf < 0)
		return Element();
	return tab[index_virf];
}
template <class Element, int MAX_STIVA>
Element Stiva<Element, MAX_STIVA>::bot(int nr) {
	return tab[nr];
}
template <class Element, int MAX_STIVA>
void Stiva<Element, MAX_STIVA>::afis() {
	int aux = index_virf;
	while (aux >= 0)
	{
		cout << tab[aux] << endl;
		aux--;
	}

}

template <class Element, int MAX_STIVA>
bool Stiva<Element, MAX_STIVA>::is_empty() {
	return index_virf == -1;
}

template <class Element, int MAX_STIVA>
istream& operator >> (istream& in, Stiva<Element, MAX_STIVA>& s) {
	Element el;
	s.index_virf = -1;
	int nr = 1;
	Stiva<Exceptie, 35>E;
	while (!in.eof()) {
		try {
			in >> el;

			E.push("Nici o eroare");
			s.push(el);
		}
		catch (NumeInvalid)
		{
			E.push(NumeInvalid());
			s.push(el);
		}
		catch (CnpInvalid)
		{
			E.push(CnpInvalid());
			s.push(el);
		}
		catch (AnInvalid)
		{
			E.push(AnInvalid());
			s.push(el);
		}
		catch (PunctajInvalid)
		{
			E.push(PunctajInvalid());
			s.push(el);
		}
		catch (LinieGoala)
		{
			E.push(LinieGoala());
			s.push(el);
		}
		nr++;
	}
	int nr2 = nr - 1;
	while (!s.is_empty())
	{
		cout << "Nr-ul Liniei: " << nr2 << " " << endl;
		cout << s.top() << "Eroare: " << E.top();
		s.pop();
		E.pop();
		nr2--;
		cout << endl;
		cout << endl;
	}
	return in;

}
Exceptie::Exceptie(const char* mesaj, int cod) {
	if (!mesaj) {
		this->mesaj = new char[1];
		this->mesaj[0] = '\0';
	}
	this->mesaj = new char[strlen(mesaj) + 1];
	strcpy(this->mesaj, mesaj);
	this->cod = cod;
}
Exceptie::Exceptie(const Exceptie& e) {
	mesaj = new char[strlen(e.mesaj) + 1];
	strcpy(mesaj, e.mesaj);
	cod = e.cod;
}
Exceptie::~Exceptie() {
	if (mesaj)delete mesaj;
}
Exceptie& Exceptie::operator=(const Exceptie& e) {
	if (this != &e) {
		if (mesaj)delete mesaj;
		mesaj = new char[strlen(e.mesaj) + 1];
		strcpy(mesaj, e.mesaj);
		cod = e.cod;
	}
	return *this;
}
void Exceptie::afisare() {
	cout << mesaj << endl;
}
ostream& operator<<(ostream& out, const Exceptie& e) {
	out << e.mesaj << " (cod:" << e.cod << ")";
	return out;
}

void main() {


	Stiva<Student, 5> S;

	ifstream in("student.txt");
	in >> S;

	system("pause");
}