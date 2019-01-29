#include "validator.h"

ostream& operator<<(ostream& out, const ValidatorException& mesaj)
{
	for (const auto& msg : mesaj.mesaje) {
		out << msg << " ";
	}
	return out;
}

void ProdusValidator::validare(const Produs& prod)
{
	vector<string> erori;
	if (prod.getId() < 0) erori.push_back("Id negativ!\n");
	if (prod.getNume().size() == 0) erori.push_back("Denumire vida!\n");
	if (prod.getPret() < 0) erori.push_back("Pret negativ!\n");
	if (prod.getProducator().size() == 0) erori.push_back("Producator vid!\n");
	if (prod.getTip().size() == 0) erori.push_back("Tip vid!\n");

	if (erori.size() > 0)
		throw ValidatorException(erori);
}
