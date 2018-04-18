#ifndef ARBOL_H_
#define ARBOL_H_

#include <list>
#include <string>
#include <utility>
#include "TablasDatos.h"
using namespace std;


class Arbol {
public:

	Arbol(string desc) : _elem(&TablasDatos::Nodo(0,0)), _desc(desc) {}
	Arbol(string desc, TablasDatos::Nodo n) : _elem(&n), _desc(desc) {}
	Arbol() : _elem(NULL), _desc("") {}

	list<pair<string, Arbol*> > adjs() {
		return _adyacentes;
	}

	void setElem(string desc, TablasDatos::Nodo *elem) {
		_elem = elem;
		_desc = desc;
	}

	bool operator==(string s) const {
		return _desc == s;
	}

	bool operator!=(string s) const {
		return _desc != s;
	}

	void addHijo(const string &arista, Arbol *a) {
		_adyacentes.push_back(pair<string, Arbol*>(arista, a));
	}

private:

	pair<string, Arbol*> par;

	list<pair<string, Arbol*> > _adyacentes;

	string _desc;
	TablasDatos::Nodo *_elem;
};

#endif // !ARBOL_H_
