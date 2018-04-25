#ifndef TABLASDATOS_H_
#define TABLASDATOS_H_

#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>
#include <list>
#include "Arbol.h"
#include "Nodo.h"

using namespace std;

class TablasDatos {
public:
	TablasDatos() {}

	bool lecturaDatos(string rutaFicheroAtributos, string rutaFicheroDatos) {
		_datos.clear();
		ifstream lecturaAtributos;
		lecturaAtributos.open(rutaFicheroAtributos);

		if (!lecturaAtributos.is_open())
			return false;

		string linea;
		getline(lecturaAtributos, linea);

		_listaAtributos = split(linea, ',');

		lecturaAtributos.close();

		ifstream lecturaDatos;
		lecturaDatos.open(rutaFicheroDatos);

		if (!lecturaDatos.is_open())
			return false;

		while (!lecturaDatos.eof()) {
			getline(lecturaDatos, linea);
			vector<string> ejemplos = split(linea, ',');
			if (linea != "" && ejemplos.size() != _listaAtributos.size()) {
				lecturaDatos.close();
				return false;
			}
			_listaEjemplos.push_back(ejemplos);
		}

		lecturaDatos.close();

		return true;
	}

	list<string> listaEjemplos(string atributo) {
		list<string> l;
		for (auto cit = _datos[atributo].cbegin(); cit != _datos[atributo].cend(); cit++) {
			l.push_back(cit->first);
		}
		return l;
	}
	
	list<vector<string> > listaEjemplos() {
		return _listaEjemplos;
	}

	vector<string> listaAtributos() {
		return _listaAtributos;
	}

	unordered_map<string, int> datosAtributos() {
		unordered_map<string, int> m;
		size_t i = 0;
		for (auto cit = _listaAtributos.cbegin(); cit != _listaAtributos.cend()-1; cit++) {
			m.insert_or_assign(*cit, i);
			i++;
		}
		return m;
	}

	unordered_map<string, unordered_map<string, Nodo> > getDatos() {
		return _datos;
	}

private:

	vector<string> split(string linea, char pattern) {
		vector<string> v;
		string palabra = "";
		for (size_t i = 0; i < linea.size(); i++) {
			if (linea[i] != pattern)
				palabra.push_back(linea[i]);
			else {
				v.push_back(palabra);
				palabra = "";
			}
		}
		v.push_back(palabra);
		return v;
	}

	list<vector<string> > _listaEjemplos;
	vector<string> _listaAtributos;
	unordered_map<string, unordered_map<string, Nodo> > _datos;
};

#endif // !TABLASDATOS_H_