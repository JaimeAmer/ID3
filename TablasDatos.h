#ifndef TABLASDATOS_H_
#define TABLASDATOS_H_

#include <fstream>
#include <map>
#include <queue>
#include <list>
#include "Arbol.h"

using namespace std;

class TablasDatos {
public:
	class Nodo {
	public:
		int p;
		int n;
		int a;
		float r;
		Nodo(int _p, int _n) : p(_p), n(_n), a(_p + _n), r(a/n*1.0){}
		Nodo() : p(0), n(0), a(0), r(0.0) {}
		float infor() const {
			return -p * log2f(p) - n * log2f(n);
		}

		class Comparador {
		public:
			bool operator()(Nodo a, Nodo b) {
				return a.infor() < b.infor();
			}
		};		
	};

	bool lecturaDatos(string rutaFicheroAtributos, string rutaFicheroDatos) {
		_datos.clear();
		ifstream lecturaAtributos;
		lecturaAtributos.open(rutaFicheroAtributos);

		if (!lecturaAtributos.is_open())
			return false;

		string linea;
		getline(lecturaAtributos, linea);

		auto atributos = split(linea, ",");

		for (auto it = atributos.cbegin(); it != atributos.cend(); it++)
			_datos.insert_or_assign(*it, map<string, Nodo>());

		lecturaAtributos.close();

		ifstream lecturaDatos;
		lecturaDatos.open(rutaFicheroDatos);

		if (!lecturaDatos.is_open())
			return false;

		while (!lecturaDatos.eof()) {
			getline(lecturaDatos, linea);
			auto datos = split(linea, ",");
			if (datos.size() != atributos.size()) {
				lecturaDatos.close();
				return false;
			}
			else for (int i = 0; i < datos.size(); i++) {
				//Rellenar la tabla de datos
				_datos[atributos[i]].insert_or_assign(datos[i], Nodo());
			}
		}

		lecturaDatos.close();

		return true;
	}

	map<string, Nodo> *operator[](string key) {
		return &_datos[key];
	}

	list<string> listaEjemplos(string atributo) {
		list<string> l;
		for (auto cit = _datos[atributo].cbegin(); cit != _datos[atributo].cend(); cit++) {
			l.push_back(cit->first);
		}

		return l;
	}

	list<string> listaAtributos() {
		list<string> l;
		for (auto cit = _datos.cbegin(); cit != _datos.cend(); cit++)
			l.push_back(cit->first);

		return l;
	}



private:




	vector<string> split(string linea, string pattern) {
		vector<string> v;
		int posIni = 0;
		int posFin = linea.length;
		while (linea.length > 0) {
			posFin = linea.find(pattern);
			v.push_back(linea.substr(posIni, posFin));
			linea.erase(posIni, posFin);
			posIni = posFin + 1;
		}
		return v;
	}

	list<string> _listaEjemplos;
	list<string> _listaAtributos;
	map<string, map<string, Nodo> > _datos;
};

#endif // !TABLASDATOS_H_
