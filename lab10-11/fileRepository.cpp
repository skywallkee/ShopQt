#include "fileRepository.h"
#include "service.h"

/*
	citeste dintr-un fisier de tip CSV
*/
void ProdusFileRepository::loadFromFile()
{
	std::ifstream in;
	in.open(numeFisier);
	if (!in.is_open()) throw ProdusRepositoryException("Nu s-a putut deschide fisierul: " + numeFisier);
	string nume, tip, producator;
	int id, pret;
	while (in >> id >> nume >> tip >> pret >> producator) {
		Produs p{ id,nume,tip,pret,producator };
		adauga(p);
	}
	in.close();
}

/*
	scrie intr-un fisier de tip CSV
*/
void ProdusFileRepository::writeToFile()
{
	std::ofstream out(numeFisier, std::ios::trunc);
	for (const auto& produs : getAll()) {
		out << produs.getId() << " ";
		out << produs.getNume() << " ";
		out << produs.getTip() << " ";
		out << produs.getPret() << " ";
		out << produs.getProducator() << std::endl;
	}
	out.close();
}


