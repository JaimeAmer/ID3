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

		_listaAtributos = split(linea, ",");

		for (auto it = _listaAtributos.cbegin(); it != _listaAtributos.cend(); it++)
			_datos.insert_or_assign(*it, unordered_map<string, Nodo>());

		lecturaAtributos.close();

		ifstream lecturaDatos;
		lecturaDatos.open(rutaFicheroDatos);

		if (!lecturaDatos.is_open())
			return false;

		while (!lecturaDatos.eof()) {
			getline(lecturaDatos, linea);
			vector<string> ejemplos = split(linea, ",");
			if (ejemplos.size() != _listaAtributos.size()) {
				lecturaDatos.close();
				return false;
			}
			for (unsigned int i = 0; i < ejemplos.size(); i++) {
				//Rellenar la tabla de datos
				Nodo elem = _datos[_listaAtributos[i]][ejemplos[i]];
				if (ejemplos[ejemplos.size() - 1] == "si")
					elem.sumP();
				else elem.sumN();
				_datos[_listaAtributos[i]][ejemplos[i]] = elem;
			}
		}

		lecturaDatos.close();

		return true;
	}

	unordered_map<string, Nodo> *operator[](string key) {
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
		while (linea.size() > 0) {
			size_t posIni = 0;
			size_t posFin = linea.find(pattern);
			string s = linea.substr(posIni, posFin);
			if (!v.empty() && s == v.back()) break;
			v.push_back(s);
			linea.erase(posIni, posFin+1);
		}
		return v;
	}

	vector<string> _listaEjemplos;
	vector<string> _listaAtributos;
	unordered_map<string, unordered_map<string, Nodo> > _datos;
};

#endif // !TABLASDATOS_H_
