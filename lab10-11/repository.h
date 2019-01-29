#pragma once
#include "domain.h"
#include <map>
#include <vector>

using std::vector;
using std::ostream;

class RepositoryAbstract {
public:
	RepositoryAbstract() = default;
	virtual void adauga(const Produs& prod) = 0;
	virtual void sterge(const Produs& prod) = 0;
	virtual void modifica(const Produs& prod, const string& numeNou, const string& tipNou, int pretNou, const string& producatorNou) = 0;
	virtual const Produs& cauta(int id) const = 0;
	virtual const vector<Produs> getAll() = 0;
	virtual ~RepositoryAbstract() {}
};

class ProdusRepository : public RepositoryAbstract {
private:
	vector<Produs> listaProduse;

public:
	ProdusRepository() noexcept : RepositoryAbstract() {};

	//nu permite copierea de obiecte ProdusRepository
	ProdusRepository(const ProdusRepository& ot) = delete;
	void salveaza();
	~ProdusRepository() {};

	/*
	adaugam produsul in lista de produse
	input: prod - Produs
	output: exceptie - ProdusRepositoryException
	arunca exceptie daca mai exista un produs identic in lista
	*/
	virtual void adauga(const Produs& prod) override;

	/*
	stergem un produs din lista de produse
	input: prod - Produs
	output: exceptie - ProdusRepositoryException
	arunca exceptie daca produsul nu exista in listaa
	*/
	virtual void sterge(const Produs& prod) override;

	/*
	modifica un anumit produs in lista
	input: prod - Produs; numeNou, tipNou, producatorNou - string; pretNou - int
	output: exceptie - ProdusRepositoryException
	arunca exceptie daca produsul nu exista in lista
	*/
	virtual void modifica(const Produs& prod, const string& numeNou, const string& tipNou, int pretNou, const string& producatorNou) override;

	/*
	cauta un produs in lista
	input: id - int
	output: returneaza produsul cautat de tip Produs
	arunca exceptie daca nu exista produsul cautat in lista

	*/
	virtual const Produs& cauta(int id) const override;

	/*
	returneaza toate produsele din lista
	*/
	//
	virtual const vector<Produs> getAll() override;

};

class RepositoryProbabilitate : public RepositoryAbstract {
private:
	std::map<int, Produs> produse;
	double probabilitate;

public:
	RepositoryProbabilitate(double probabilitate) : RepositoryAbstract(), probabilitate(probabilitate) {};
	RepositoryProbabilitate(const RepositoryProbabilitate& ot) = delete;

	void adauga(const Produs& prod) override;
	void sterge(const Produs& prod) override;
	void modifica(const Produs& prod, const string& numeNou, const string& tipNou, int pretNou, const string& producatorNou) override;
	const Produs& cauta(int id) const override;
	const vector<Produs> getAll() override;

};

class ProdusRepositoryException {
private:
	string mesaj;
public:
	ProdusRepositoryException(string mesaj) : mesaj(mesaj) {};

	friend ostream& operator<<(ostream& out, const ProdusRepositoryException& mesaj);
};

ostream& operator<<(ostream& out, const ProdusRepositoryException& mesaj);