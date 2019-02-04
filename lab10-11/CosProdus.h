#pragma once
#include "domain.h"
//#include "repository.h"
#include <vector>
#include <fstream>
using std::vector;

class CosProdus {
private:
	vector<Produs> cos;
public:
	CosProdus() = default;
	~CosProdus() = default;

	/*
	adauga produs in cos
	input: produs - Produs
	output: -
	*/
	void adaugaCos(const Produs& p) {
		cos.push_back(p);
	}

	/*
	functie care goleste cosul
	input: -
	output: -
	*/
	void golesteCos() {
		cos.erase(cos.begin(), cos.end());
	}

	/*
	returneaza continutul cosului
	input: -
	output: vector
	returneaza continutului cosului
	*/
	const vector<Produs>& getCos() const noexcept {
		return cos;
	}

	/*
	returneaza marimea cosului
	input:
	output: intreg
	returneaza dimensiunea intregului cos
	*/
	int getSizeCos() noexcept {
		return cos.size();
	}

	/*
	functie care citeste dintr-un fisier de tip CVS
	input: numeFisier - string
	*/
	void readFromCVS(const string& numeFisier) {
		std::ifstream in;
		in.open(numeFisier);
		if (!in.is_open()) {
			throw ProdusRepositoryException("Nu s-a putut deschide fisierul " + numeFisier);
		}
		string nume, tip, producator;
		int id, pret;
		while (in >> id >> nume >> tip >> pret >> producator) {
			Produs p{ id,nume,tip,pret,producator };
			adaugaCos(p);
		}
		in.close();
	}
	/*
	  Functie care scrie intr-un fisier de tip CVS
	  Input: numeFisier - string
	*/
	void saveToCVS(const string& numeFisier)
	{
		std::ofstream out;
		out.open(numeFisier, std::ios::trunc);
		for (const auto& p : cos)
		{
			out << p.getId() << ",";
			out << p.getNume() << ",";
			out << p.getTip() << ",";
			out << p.getPret() << ",";
			out << p.getProducator() << std::endl;
		}
		out.close();
	}

};