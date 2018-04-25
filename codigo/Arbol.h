#ifndef ARBOL_H_
#define ARBOL_H_

#include <list>
#include <string>
#include <utility>
#include "Nodo.h"
#include "TablasDatos.h"
#include "termcolor.hpp"
using namespace std;


class Arbol {
public:

	Arbol(string desc) : _descripcion(desc) {}
	Arbol() : _descripcion("") {}

	vector<pair<string, Arbol> > adjs() {
		return _adyacentes;
	}

	void setElem(string desc) {
		_descripcion = desc;
	}

	void addHijo(const string &arista, Arbol a) {
		_adyacentes.push_back(pair<string, Arbol>(arista, a));
	}

	bool esHoja() {
		return _adyacentes.empty();
	}

	string getNombre() {
		return _descripcion;
	}

	void mostrarSolucion(string indent, bool last) {
		cout << termcolor::white << indent;
		if (last || esHoja()) {
			cout << termcolor::white << "\\-";
			indent += "  ";
		}
		else {
			cout << termcolor::white << "|-";
			indent += "| ";
		}
		if (this->getNombre() == "si")
			cout << termcolor::green;
		else if (this->getNombre() == "no")
			cout << termcolor::red;
		else cout << termcolor::yellow;
		cout << this->getNombre() << endl;
		auto hijos = this->adjs();
		for (size_t i = 0; i < hijos.size(); i++) {
			cout << termcolor::white << indent << "|-" << termcolor::cyan << "<" << hijos[i].first << ">" << endl;
			indent += "| ";
			hijos[i].second.mostrarSolucion(indent, i == hijos.size() - 1);
			indent.pop_back(); indent.pop_back();
		}
		cout << termcolor::reset;
	}


private:

	vector<pair<string, Arbol> > _adyacentes;

	
	string _descripcion;
};

#endif // !ARBOL_H_
