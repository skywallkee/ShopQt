#include "service.h"
#include <algorithm>
#include <random>

using std::copy_if;
using std::sort;
using std::for_each;

/*
	adauga produs in lista de produse
	input: id, pret - int; nume, tip, producator - string
	output: -
	functie void, nu returneaza nimic
*/
void ProdusService::adaugaProdus(int id, const string& nume, const string& tip, int pret, const string& producator)
{
	Produs p{ id,nume,tip,pret,producator };
	validator.validare(p);
	repo.adauga(p);
	undoActiuni.push_back(std::make_unique<UndoAdauga>(repo, p));
}

/*
	sterge produs din lista de produse in functie de id
	input : id - int
	output: -
*/
void ProdusService::stergeProdus(int id)
{
	const Produs& p = cautaProdus(id);
	undoActiuni.push_back(std::make_unique<UndoSterge>(repo, p));
	repo.sterge(p);
}

/*
	modifica un produs din lista de produse in functie de id
	input: id, pretNou - int; numeNou, tipNou, producatorNou - string
	output: -
*/
void ProdusService::modificaProdus(int id, const string & numeNou, const string & tipNou, int pretNou, const string & producatorNou)
{
	const Produs& p = cautaProdus(id);
	undoActiuni.push_back(std::make_unique<UndoModifica>(repo, p));
	repo.modifica(p, numeNou, tipNou, pretNou, producatorNou);
}

/*
	cauta produs in lista de produse in functie de id
	input: id - int
	output: produs - Produs
*/
const Produs& ProdusService::cautaProdus(int id) const
{
	return repo.cauta(id);
}

/*
	returneaza lista de produse
*/
const vector<Produs> ProdusService::getAll() const
{
	return repo.getAll();
}

/*
	filtreaza produsele dupa tip
	input: tip - string
	output: vector
	returneaza produsele care au ca tip sting-ul dat
*/
vector<Produs> ProdusService::filtrareTip(const string& tip) const
{
	vector<Produs> listaProduse = repo.getAll();
	vector<Produs> rez;
	copy_if(listaProduse.begin(), listaProduse.end(), back_inserter(rez), [tip](const Produs& prod) {return prod.getTip() == tip; });
	return rez;
}

/*
	filtreaza produsele dupa pret
	input: pretMax - int
	output: vector
	returneaza produsele care au un pret mai mic decat int-ul dat
*/
vector<Produs> ProdusService::filtrarePretMaiMic(int pretMax) const
{
	vector<Produs> listaProduse = repo.getAll();
	vector<Produs> rez;
	copy_if(listaProduse.begin(), listaProduse.end(), back_inserter(rez), [pretMax](const Produs& prod) noexcept {return prod.getPret() < pretMax; });
	return rez;
}

/*
	filtreaza produsele dupa pret
	input: pretMin - int
	output: vector
	returneaza produsele care au un pret mai mare decat int-ul dat
*/
vector<Produs> ProdusService::filtrarePretMaiMare(int pretMin) const
{
	vector<Produs> listaProduse = repo.getAll();
	vector<Produs> rez;
	copy_if(listaProduse.begin(), listaProduse.end(), back_inserter(rez), [pretMin](const Produs& prod) noexcept {return prod.getPret() > pretMin; });
	return rez;
}

/*
	filtreaza produsele dupa pret
	input: pretMin, pretMax - int
	output: vector
	returneaza produsele care au un pret mai mic decat pretMax si mai mare decat pretMin
*/
vector<Produs> ProdusService::filtrarePret(int pretMin, int pretMax) const
{
	vector<Produs> listaProduse = repo.getAll();
	vector<Produs> rez;
	copy_if(listaProduse.begin(), listaProduse.end(), back_inserter(rez), [=](const Produs& prod) noexcept {return prod.getPret() >= pretMin && prod.getPret() <= pretMax; });
	return rez;
}

/*
	sorteaza dupa nume
	input: -
	output: vector
	returneaza lista de produse sortata alfabetic dupa nume
*/
vector<Produs> ProdusService::sortareNume() const
{
	vector<Produs> listaProduse = repo.getAll();
	sort(listaProduse.begin(), listaProduse.end(), [](const Produs& p1, const Produs& p2) {return p1.getNume() < p2.getNume(); });
	return listaProduse;
}

/*
	sorteaza dupa producator
	input: -
	output: vector
	returneaza lista de produse sortata alfabetic dupa producator
*/
vector<Produs> ProdusService::sortareProducator() const
{
	vector<Produs> listaProduse = repo.getAll();
	sort(listaProduse.begin(), listaProduse.end(), [](const Produs& p1, const Produs& p2) {return p1.getProducator() < p2.getProducator(); });
	return listaProduse;
}

/*
	sorteaza dupa tip si pret
	input: -
	output: vector
	returneaza lista de produse sortata dupa tip si pret
*/
vector<Produs> ProdusService::sortareTipPret() const
{
	vector<Produs> listaProduse = repo.getAll();
	sort(listaProduse.begin(), listaProduse.end(), [](const Produs& p1, const Produs& p2) {
		if (p1.getTip() == p2.getTip())
		{
			return p1.getPret() > p2.getPret(); //
		}
		return p1.getTip() < p2.getTip();
	});
	return listaProduse;
}

vector<ProdusTipDTO> ProdusService::raportTip()
{
	map<string, int> raport;
	vector<Produs> listaProduse = getAll();
	for_each(listaProduse.begin(), listaProduse.end(), [&](const auto& p) {
		string tipStocare = p.getTip();
		if (raport.find(tipStocare) == raport.end()) {
			raport[tipStocare] = 1;
		}
		else
			raport[tipStocare] += 1;

	});
	vector<ProdusTipDTO> rez;
	for_each(raport.begin(), raport.end(), [&](const auto& p) {
		ProdusTipDTO stocare{ p.first,p.second };
		rez.push_back(stocare);
	});
	return rez;
}

void ProdusService::golesteCos()
{
	cos.golesteCos();
}

void ProdusService::adaugaInCos(const Produs & p)
{
	cos.adaugaCos(p);
}

void ProdusService::saveToCVS(const string & numeFisier)
{
	cos.saveToCVS(numeFisier);
}

void ProdusService::genereazaCos(int numar)
{
	vector<Produs> listaProduse = getAll();
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> const dist(0, listaProduse.size() - 1);
	for (int i = 0; i < numar; i++)
	{
		int const pozitie = dist(mt);
		cos.adaugaCos(listaProduse.at(pozitie));
	}
}



int ProdusService::getSizeCos() noexcept
{
	return cos.getSizeCos();
}

const vector<Produs>& ProdusService::getAllCos() const noexcept
{
	return cos.getCos();
}

void ProdusService::undo()
{
	if (undoActiuni.empty())
		throw ProdusRepositoryException("UNDO nu se mai poate efectua!");
	undoActiuni.back()->doUndo();
	undoActiuni.pop_back();
}

