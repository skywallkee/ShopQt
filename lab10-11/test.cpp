#include "test.h"
#include <assert.h>

void Test::testDomain()
{
	Produs p{ 1,"paine","secara",5,"Otomani" };
	assert(p.getId() == 1);
	assert(p.getNume() == "paine");
	assert(p.getTip() == "secara");
	assert(p.getPret() == 5);
	assert(p.getProducator() == "Otomani");

	p.setNume("paste");
	p.setTip("fainoase");
	p.setPret(4);
	p.setProducator("Carbonara");

	assert(p.getNume() == "paste");
	assert(p.getTip() == "fainoase");
	assert(p.getPret() == 4);
	assert(p.getProducator() == "Carbonara");

	//test dto
	ProdusTipDTO produs{ "fainoase",1 };
	assert(produs.getNr() == 1);
	assert(produs.getTipDTO() == "fainoase");

}

void Test::testRepository()
{
	ProdusRepository repo;
	//adauga
	assert(repo.getAll().size() == 0);
	repo.adauga(Produs{ 1,"paine","secara",5,"Otomani" });
	repo.adauga(Produs{ 2,"faina","aliment",4,"Farina" });
	repo.adauga(Produs{ 3,"paste","fainoase",7,"Carbonara" });
	assert(repo.getAll().size() == 3);
	try
	{
		repo.adauga(Produs{ 1,"paine","secara",5,"Otomani" });
	}
	catch (ProdusRepositoryException&)
	{
		assert(true);
	}

	//cauta
	Produs p{ 0," "," ",0," " };
	p = repo.cauta(1);

	assert(p.getNume() == "paine");
	assert(p.getTip() == "secara");
	assert(p.getPret() == 5);
	assert(p.getProducator() == "Otomani");

	try
	{
		repo.cauta(4);
	}
	catch (const ProdusRepositoryException& mesaj)
	{
		assert(true);
		cout << mesaj;
	}

	//sterge
	repo.sterge(p);
	assert(repo.getAll().size() == 2);

	Produs p1{ -1,"","",-1,"" };
	try
	{
		repo.sterge(p1);
	}
	catch (const ProdusRepositoryException& mesaj)
	{
		assert(true);
		cout << mesaj;
	}

	//modifica
	p = repo.cauta(2);
	repo.modifica(p, "cola", "zero", 7, "Coca-Cola");
	assert(repo.getAll().size() == 2);

	//getAll
	assert(repo.getAll().size() == 2);

}

void Test::testValidator()
{
	ProdusValidator validator;
	Produs p{ 0,"","",-1,"" };
	try
	{
		validator.validare(p);
	}
	catch (const ValidatorException& mesaj)
	{
		assert(true);
		cout << mesaj;
	}

	Produs p1{ 1,"paine","secara",5,"Otomani" };
	validator.validare(p1);
	assert(true);
}

void Test::testService()
{
	//ProdusRepository repo;
	ProdusFileRepository repo{ "testFileRepository.txt" };
	ProdusValidator validator;
	ProdusService service{ repo,validator };

	//adauga
	service.adaugaProdus(1, "paine", "casa", 5, "Otomani");
	service.adaugaProdus(2, "paste", "fainoase", 7, "Carbonara");
	assert(service.getAll().size() == 2);

	//cauta
	Produs p{ 0," "," ",-1," " };
	p = service.cautaProdus(1);
	assert(p.getNume() == "paine");
	assert(p.getTip() == "casa");
	assert(p.getPret() == 5);
	assert(p.getProducator() == "Otomani");

	//modificare
	service.modificaProdus(1, "pepsi", "suc", 7, "Coca-Cola");
	p = service.cautaProdus(1);
	assert(p.getNume() == "pepsi");
	assert(p.getTip() == "suc");
	assert(p.getPret() == 7);
	assert(p.getProducator() == "Coca-Cola");

	//sterge
	service.stergeProdus(1);
	assert(service.getAll().size() == 1);
	service.stergeProdus(2);
	assert(service.getAll().size() == 0);

	//filtrare
	service.adaugaProdus(1, "paine", "casa", 5, "Otomani");
	service.adaugaProdus(2, "paine", "oras", 4, "Brusturi");
	service.adaugaProdus(3, "salam", "casa", 8, "Fox");
	service.adaugaProdus(4, "cola", "suc", 6, "Coca-Cola");
	service.adaugaProdus(5, "lapte", "lactate", 10, "Zuzu");

	assert(service.getAll().size() == 5);

	assert(service.filtrareTip("casa").size() == 2);
	assert(service.filtrareTip("oras").size() == 1);
	assert(service.filtrareTip("lactate").size() == 1);
	assert(service.filtrareTip("fainoase").size() == 0);

	assert(service.filtrarePretMaiMic(6).size() == 2);
	assert(service.filtrarePretMaiMic(9).size() == 4);
	assert(service.filtrarePretMaiMic(11).size() == 5);
	assert(service.filtrarePretMaiMic(2).size() == 0);

	assert(service.filtrarePretMaiMare(4).size() == 4);
	assert(service.filtrarePretMaiMare(6).size() == 2);
	assert(service.filtrarePretMaiMare(9).size() == 1);
	assert(service.filtrarePretMaiMare(11).size() == 0);

	assert(service.filtrarePret(2, 11).size() == 5);
	assert(service.filtrarePret(3, 9).size() == 4);
	assert(service.filtrarePret(5, 9).size() == 3);
	assert(service.filtrarePret(11, 14).size() == 0);

	//test raport dto dupa tip
	assert(service.raportTip().size() == 4);

	//sortare
	assert(service.sortareNume().size() == 5);
	assert(service.sortareProducator().size() == 5);
	assert(service.sortareTipPret().size() == 5);

	service.stergeProdus(5);
	assert(service.sortareNume().size() == 4);
	assert(service.sortareProducator().size() == 4);
	assert(service.sortareTipPret().size() == 4);

	service.stergeProdus(1);
	service.stergeProdus(3);
	service.stergeProdus(4);
	assert(service.sortareNume().size() == 1);
	assert(service.sortareProducator().size() == 1);
	assert(service.sortareTipPret().size() == 1);

	service.stergeProdus(2);
	assert(service.getAll().size() == 0);
}

void Test::testCos()
{
	//OfertaRepository repo;
	ProdusFileRepository repo{ "testFileRepository.txt" };
	ProdusValidator valid;
	ProdusService serv{ repo, valid };

	serv.adaugaProdus(1, "paine", "casa", 8, "Cohani");
	serv.adaugaProdus(2, "Mirinda", "suc", 9, "Pepsi");
	assert(serv.getAll().size() == 2);

	//test adauga in cos
	Produs p = serv.cautaProdus(1);
	serv.adaugaInCos(p);
	assert(serv.getSizeCos() == 1);
	p = serv.cautaProdus(2);
	serv.adaugaInCos(p);
	assert(serv.getSizeCos() == 2);

	//test save to CVS
	serv.saveToCVS("testCosProdus.txt");

	//test goleste cos
	serv.golesteCos();
	assert(serv.getSizeCos() == 0);

	//test genereaza cos
	serv.genereazaCos(5);
	assert(serv.getAllCos().size() == 5);
	serv.golesteCos();
	assert(serv.getSizeCos() == 0);

	serv.stergeProdus(1);
	serv.stergeProdus(2);
	assert(serv.getAll().size() == 0);
}

void Test::testUndo()
{
	//ProdusRepository repo;
	ProdusFileRepository repo{ "testFileRepository.txt" };
	ProdusValidator valid;
	ProdusService serv{ repo, valid };

	serv.adaugaProdus(1, "paine", "casa", 6, "Cohani");
	serv.adaugaProdus(2, "apa", "plata", 5, "Dorna");
	assert(serv.getAll().size() == 2);

	//Test UNDO adauga
	serv.undo();
	assert(serv.getAll().size() == 1);
	serv.undo();
	assert(serv.getAll().size() == 0);


	try
	{
		serv.undo();
	}
	catch (const ProdusRepositoryException& msg)
	{
		assert(true);
		cout << msg;
	}

	serv.adaugaProdus(1, "paine", "casa", 6, "Cohani");
	serv.adaugaProdus(2, "apa", "plata", 5, "Dorna");
	assert(serv.getAll().size() == 2);

	//Test UNDO sterge
	serv.stergeProdus(1);
	assert(serv.getAll().size() == 1);
	serv.stergeProdus(2);
	assert(serv.getAll().size() == 0);

	serv.undo();
	assert(serv.getAll().size() == 1);
	serv.undo();
	assert(serv.getAll().size() == 2);

	//Test UNDO modifica
	serv.modificaProdus(1, "bere", "neagra", 7, "Silva");
	Produs p = serv.cautaProdus(1);
	assert(p.getNume() == "bere");
	assert(p.getTip() == "neagra");
	assert(p.getPret() == 7);
	assert(p.getProducator() == "Silva");

	serv.undo();
	p = serv.cautaProdus(1);
	assert(p.getNume() == "paine");
	assert(p.getTip() == "casa");
	assert(p.getPret() == 6);
	assert(p.getProducator() == "Cohani");

	serv.stergeProdus(1);
	serv.stergeProdus(2);
	serv.adaugaProdus(10, "lapte", "lactate", 9, "Zuzu");
	assert(serv.getAll().size() == 1);
}

void Test::testFileRepository()
{
	auto p1 = Produs{ 1,"faina","fainoase",6,"Farina" };
	auto p2 = Produs{ 2,"cola","suc",4,"Coca-Cola" };
	auto p3 = Produs{ 3,"salam","casa",7,"Fox" };

	ProdusFileRepository repository{ "testFileRepository.txt" };
	try
	{
		ProdusFileRepository repo{ "gresit2" };
	}
	catch (const ProdusRepositoryException& msg)
	{
		cout << msg;
	}
	repository.adauga(p1);
	repository.adauga(p2);
	repository.adauga(p3);
	auto listaProduse = repository.getAll();
	assert(listaProduse.size() == 4); //aici

	repository.sterge(p3);
	repository.modifica(p1, "lapte", "lactate", 5, "Zuzu");
	repository.sterge(p2);
	repository.sterge(p1);

	auto p4 = repository.cauta(10);
	repository.sterge(p4);
}

void Test::testAll()
{
	testDomain();
	testRepository();
	testValidator();
	testService();
	testCos();
	testUndo();
	testFileRepository();
}
