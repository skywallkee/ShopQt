#pragma once
#include "repository.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
	Produs produsAdaugat;
	//ProdusRepository& repo;
	RepositoryAbstract& repository;
public:
	UndoAdauga(RepositoryAbstract& repo, const Produs& p) :repository(repo), produsAdaugat(p) {};
	void doUndo() override {
		repository.sterge(produsAdaugat);
	}
};

class UndoSterge : public ActiuneUndo {
private:
	Produs produsSters;
	//ProdusRepository& repo;
	RepositoryAbstract& repository;
public:
	UndoSterge(RepositoryAbstract& repo, const Produs& p) :repository(repo), produsSters(p) {};
	void doUndo() override {
		repository.adauga(produsSters); //sterge(produsSters)
	}
};

class UndoModifica :public ActiuneUndo {
private:
	Produs produsModificat;
	//ProdusRepository& repo;
	RepositoryAbstract& repository;
public:
	UndoModifica(RepositoryAbstract& repo, const Produs& produsModificat) : repository(repo), produsModificat(produsModificat) {};
	void doUndo() override {
		Produs p = repository.cauta(produsModificat.getId());
		repository.modifica(p, produsModificat.getNume(), produsModificat.getTip(), produsModificat.getPret(), produsModificat.getProducator());
	}
};