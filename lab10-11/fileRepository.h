#pragma once
#include "repository.h"
#include <fstream>

class ProdusFileRepository : public ProdusRepository {
private:
	string numeFisier;

	/*
	citeste dintr-un fisier de tip CVS
	*/
	void loadFromFile();

	/*
	scrie intr-un fisier de tip CVS
	*/
	void writeToFile();

public:
	ProdusFileRepository(string numeFisier) : ProdusRepository(), numeFisier(numeFisier) { loadFromFile(); };

	void adauga(const Produs& prod) override {
		ProdusRepository::adauga(prod);
		writeToFile();
	}

	void sterge(const Produs& prod) override {
		ProdusRepository::sterge(prod);
		writeToFile();
	}

	void modifica(const Produs& prod, const string& numeNou, const string& tipNou, int pretNou, const string& producatorNou) override {
		ProdusRepository::modifica(prod, numeNou, tipNou, pretNou, producatorNou);
		writeToFile();
	}


};