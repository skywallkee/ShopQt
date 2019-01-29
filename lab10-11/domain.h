#pragma once

#include <iostream>
#include <string>

using std::cout;
using std::string;

class Produs {
private:
	int id;
	std::string nume;
	std::string tip;
	int pret;
	std::string producator;
public:
	//constructor
	Produs(int id, const string nume, const string tip, int pret, const string producator) : id(id), nume(nume), tip(tip), pret(pret), producator(producator) {};

	Produs() = default;

	//copy constructor
	Produs(const Produs& ot) : id(ot.id), nume(ot.nume), tip(ot.tip), pret(ot.pret), producator(ot.producator) {
		//cout << "copy" << endl;
	};

	void operator=(const Produs& ot) {
		id = ot.id;
		nume = ot.nume;
		tip = ot.tip;
		pret = ot.pret;
		producator = ot.producator;
	}

	bool operator==(const Produs& ot) noexcept {
		return this->id == ot.id;
	}

	bool operator!=(const Produs& ot) noexcept {
		return !(*this == ot);
	}

	//gettere
	int getId() const noexcept {
		return id;
	}

	string getNume() const {
		return nume;
	}

	string getTip() const {
		return tip;
	}

	int getPret() const noexcept {
		return pret;
	}

	string getProducator() const {
		return producator;
	}

	//settere
	void setNume(const string& value) {
		nume = value;
	}

	void setTip(const string& value) {
		tip = value;
	}

	void setPret(int value) noexcept {
		pret = value;
	}

	void setProducator(const string& value) {
		producator = value;
	}
};

class ProdusTipDTO {
private:
	string tip;
	int nr;
public:
	ProdusTipDTO(const string& tip, int nr) : tip(tip), nr(nr) {};

	string getTipDTO() const { return tip; }
	int getNr() const noexcept { return nr; }
};