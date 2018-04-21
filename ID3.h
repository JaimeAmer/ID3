#ifndef ID3_H_
#define ID3_H_

#include <cmath>
#include <utility>
#include <unordered_map>
#include "TablasDatos.h"
#include "Nodo.h"
#include "Arbol.h"

using namespace std;

class ID3 {
public:

	ID3(list<string> listaAtributos, list<string> listaEjemplos) : _listaAtributos(listaAtributos), _listaEjemplos(listaEjemplos) {
		_raiz = ejecutarID3();
	}

	ID3(TablasDatos datos) : _datos(datos.getDatos()), _listaAtributos(datos.listaAtributos()){
		_raiz = ejecutarID3();
	}

	void mostrarSolucion() {

	}

private:


	Arbol ejecutarID3() {
		/*
		if (_listaEjemplos.empty())
			return Arbol("");

		if (comprobar("+"))
			return Arbol("+");

		if (comprobar("-"))
			return Arbol("-");
			*/
		if (!_listaAtributos.empty()) {
			priority_queue<pair<string, unordered_map<string, Nodo> >, vector<pair<string, unordered_map<string, Nodo> > >, Nodo::Comparador> pq;
			for (auto key = _datos.cbegin(); key != _datos.cend(); key++) {
				pq.push(pair<string, unordered_map<string, Nodo> >(key->first, key->second));
			}
			pair<string, unordered_map<string, Nodo> > r = pq.top();
			
			Arbol elem(r.first);
			for(auto values=r.second.cbegin(); values != r.second.cend(); values++){
				elem.addHijo(values->first, &ejecutarID3());
			}

			//_raiz = a;
			_posActual = &_raiz;




		}
		else throw "error";

	}

	bool comprobar(string s) {
		for (auto cit = _listaEjemplos.cbegin(); cit != _listaEjemplos.cend(); cit++) {
			if (*cit != s) {
				return false;
			}
		}
		return true;
	}
	/*
	float calcularMerito(unordered_map<string, Nodo> key) {
		float merito = 0.0;
		for (auto values = key.cbegin(); values != key.cend(); values++) {
			merito += values->second.r() * values->second.infor();
		}
		return merito;
	}
	*/

	list<string> _listaAtributos;
	list<string> _listaEjemplos;
	Arbol _raiz;
	Arbol* _posActual;

	unordered_map<string, unordered_map<string, Nodo> > _datos;

};

#endif // !ID3_H_
