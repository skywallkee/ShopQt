#pragma once
#include "repository.h"
#include "validator.h"
#include "fileRepository.h"
#include "undo.h"
#include "CosProdus.h"
#include <map>

using std::map;
using std::unique_ptr;

class ProdusService {
private:
	//ProdusRepository& repo;
	RepositoryAbstract& repo;
	ProdusValidator& validator;
	CosProdus cos;
	std::vector<unique_ptr<ActiuneUndo>> undoActiuni;

public:
	ProdusService(RepositoryAbstract& repo, ProdusValidator& validator) noexcept : repo(repo), validator(validator) {};

	//nu se permite copierea de obiecte ProdusService
	ProdusService(const ProdusService& ot) = delete;

	//nu se permite copierea la assignment
	void operator=(const ProdusService& ot) = delete;

	/*
	adauga produs in lista de produse
	input: id, pret - int; nume, tip, producator - string
	output: -
	functie void, nu returneaza nimic
	*/
	void adaugaProdus(int id, const string& nume, const string& tip, int pret, const string& producator);

	/*
	sterge produs din lista de produse in functie de id
	input : id - int
	output: -
	*/
	void stergeProdus(int id);

	/*
	modifica un produs din lista de produse in functie de id
	input: id, pretNou - int; numeNou, tipNou, producatorNou - string
	output: -
	*/
	void modificaProdus(int id, const string& numeNou, const string& tipNou, int pretNou, const string& producatorNou);

	/*
	cauta produs in lista de produse in functie de id
	input: id - int
	output: produs - Produs
	*/
	const Produs& cautaProdus(int id) const;

	/*
	returneaza lista de produse
	*/
	const vector<Produs> getAll() const;

	/*
	filtreaza produsele dupa tip
	input: tip - string
	output: vector
	returneaza produsele care au ca tip sting-ul dat
	*/
	vector<Produs> filtrareTip(const string& tip) const;

	/*
	filtreaza produsele dupa pret
	input: pretMax - int
	output: vector
	returneaza produsele care au un pret mai mic decat int-ul dat
	*/
	vector<Produs> filtrarePretMaiMic(int pretMax) const;

	/*
	filtreaza produsele dupa pret
	input: pretMin - int
	output: vector
	returneaza produsele care au un pret mai mare decat int-ul dat
	*/
	vector<Produs> filtrarePretMaiMare(int pretMin) const;

	/*
	filtreaza produsele dupa pret
	input: pretMin, pretMax - int
	output: vector
	returneaza produsele care au un pret mai mic decat pretMax si mai mare decat pretMin
	*/
	vector<Produs> filtrarePret(int pretMin, int pretMax) const;

	/*
	sorteaza dupa nume
	input: -
	output: vector
	returneaza lista de produse sortata alfabetic dupa nume
	*/
	vector<Produs> sortareNume() const;

	/*
	sorteaza dupa producator
	input: -
	output: vector
	returneaza lista de produse sortata alfabetic dupa producator
	*/
	vector<Produs> sortareProducator() const;

	/*
	sorteaza dupa tip si pret
	input: -
	output: vector
	returneaza lista de produse sortata dupa tip si pret
	*/
	vector<Produs> sortareTipPret() const;

	/*
	face un raport dupa tip
	returneaza o lista de elemente de tip ProdusTipDTO
	*/
	vector<ProdusTipDTO> raportTip();

	/*
	functie care goleste cosul
	*/
	void golesteCos();

	/*
	functie care adauga un produs in cos
	input: produs - Produs
	output: -
	*/
	void adaugaInCos(const Produs& p);

	/*
	scrie intr-un fisier CVS
	input: numeFisier - string
	*/
	void saveToCVS(const string& numeFisier);

	/*
	returneaza continutul cosului
	input: -
	output: vector
	returneaza continului cosului in cauza
	*/
	void genereazaCos(int numar);

	/*
	determina marimea cosului
	input: -
	ouput: intreg
	returneaza dimensiunea intregului cos
	*/
	int getSizeCos() noexcept;

	/*
	returneaza tot cosul
	*/
	const vector<Produs>& getAllCos() const noexcept;

	void undo();
};