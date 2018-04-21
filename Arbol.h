#ifndef ARBOL_H_
#define ARBOL_H_

#include <list>
#include <string>
#include <utility>
#include "Nodo.h"
#include "TablasDatos.h"
using namespace std;


class Arbol {
public:

	Arbol(string desc) : _elem(&Nodo(0,0)), _descripcion(desc) {}
	Arbol(string desc, Nodo n) : _elem(&n), _descripcion(desc) {}
	Arbol() : _elem(NULL), _descripcion("") {}

	list<pair<string, Arbol*> > adjs() {
		return _adyacentes;
	}

	void setElem(string desc, Nodo *elem) {
		_elem = elem;
		_descripcion = desc;
	}

	bool operator==(string s) const {
		return _descripcion == s;
	}

	bool operator!=(string s) const {
		return _descripcion != s;
	}

	void addHijo(const string &arista, Arbol *a) {
		_adyacentes.push_back(pair<string, Arbol*>(arista, a));
	}

private:

	list<pair<string, Arbol*> > _adyacentes;

	
	string _descripcion;
	Nodo *_elem;
};

#endif // !ARBOL_H_
