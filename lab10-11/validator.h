#pragma once
#include "Domain.h"
#include <vector>

using std::vector;
using std::ostream;

class ValidatorException {
private:
	vector<string> mesaje;

public:
	//constructor
	ValidatorException(const vector<string>& erori) : mesaje(erori) {}

	friend ostream& operator<<(ostream& out, const ValidatorException& mesaj);

};

ostream& operator<<(ostream& out, const ValidatorException& mesaj);

class ProdusValidator {
public:
	void validare(const Produs& prod);
};