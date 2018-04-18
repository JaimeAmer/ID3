#ifndef ID3_H_
#define ID3_H_

#include <cmath>
#include <utility>
#include "TablasDatos.h"
#include "Arbol.h"

using namespace std;
using Par = pair<string, TablasDatos::Nodo>;

class ID3 {
public:
	class Comparador {
	public:
		bool operator()(map<string, TablasDatos::Nodo> a, map<string, TablasDatos::Nodo> b) {
			return calcularMerito(a) < calcularMerito(b);
		}

	private:
		float calcularMerito(map<string, TablasDatos::Nodo> key) {
			float merito = 0.0;
			for (auto values = key.cbegin(); values != key.cend(); values++) {
				merito += values->second.r * values->second.infor();
			}
			return merito;
		}
	};

	ID3(list<string> listaAtributos, list<string> listaEjemplos) : _listaAtributos(listaAtributos), _listaEjemplos(listaEjemplos) {
		ejecutarID3();
	}

private:

	


	Arbol ejecutarID3() {
		if (_listaEjemplos.empty())
			return Arbol("");

		if (comprobar("+"))
			return Arbol("+");

		if (comprobar("-"))
			return Arbol("-");

		if (!_listaAtributos.empty()) {
			priority_queue<pair<string, TablasDatos::Nodo>, Comparador> pq;
			for (auto key = _datos.begin(); key != _datos.end(); key++) {
				for (auto values = _datos[key->first].begin(); values != _datos[key->first].end(); values++) {

					pq.push(values->second);
				}
			}
			Par r = pq.top();

			Arbol a(r.first, r.second);

			_raiz = a;
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

	float calcularMerito(map<string, TablasDatos::Nodo> key) {
		float merito = 0.0;
		for (auto values = key.cbegin(); values != key.cend(); values++) {
			merito += values->second.r * values->second.infor();
		}
		return merito;
	}

	list<string> _listaAtributos;
	list<string> _listaEjemplos;
	Arbol _raiz;
	Arbol* _posActual;

	map<string, map<string, TablasDatos::Nodo> > _datos;

};

#endif // !ID3_H_
