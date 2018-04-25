#ifndef ID3_H_
#define ID3_H_

#include <cmath>
#include <utility>
#include <unordered_map>
#include <map>
#include "TablasDatos.h"
#include "Nodo.h"
#include "Arbol.h"

using namespace std;

class ID3 {
public:

	ID3(TablasDatos datos) : _datos(datos.getDatos()), _listaAtributos(datos.listaAtributos()), _listaEjemplos(datos.listaEjemplos()){
		_listaAtributos.pop_back();
		_raiz = ejecutarID3(_listaAtributos, _listaEjemplos);
	}

	void solucion() {

		_raiz.mostrarSolucion("", true);
	}

private:


	Arbol ejecutarID3(vector<string> listaAtributos, list<vector<string> > listaEjemplos) {
		unordered_map<string, unordered_map<string, Nodo> > datos = generarTablasIteracion(listaAtributos, listaEjemplos);
		unordered_map<string, int> indiceAtributos = calcularIndiceAtributos(listaAtributos);
		
		if (listaEjemplos.empty())
			return Arbol("");

		if (comprobar(listaEjemplos, "si"))
			return Arbol("si");

		if (comprobar(listaEjemplos, "no"))
			return Arbol("no");
		
		if (!listaAtributos.empty()) {

			map<float, pair<string, unordered_map<string, Nodo> > > meritos;
			for (size_t i = 0; i<listaAtributos.size(); i++) {
				meritos.insert_or_assign(calcularMerito(datos[listaAtributos[i]]), pair<string, unordered_map<string, Nodo>>(listaAtributos[i], datos[listaAtributos[i]]));
			}
			
			pair<string, unordered_map<string, Nodo> > r = meritos.begin()->second;
			
			Arbol tree(r.first);
			
			vector<string> nuevaListaAtributos;
			for (size_t i = 0; i < listaAtributos.size(); i++) {
				if (listaAtributos[i] != r.first)
					nuevaListaAtributos.push_back(listaAtributos[i]);
			}

			for(auto values=r.second.cbegin(); values != r.second.cend(); values++){
				list<vector<string> > nuevaListaEjemplos;
				for (auto cit = listaEjemplos.cbegin(); cit != listaEjemplos.cend(); cit++) {
					vector<string> nuevaLinea;
					if ((*cit)[indiceAtributos[r.first]] == values->first) {
						for (size_t i = 0; i < cit->size(); i++) {
							if (i != indiceAtributos[r.first]) {
								nuevaLinea.push_back((*cit)[i]);
							}
						}
						nuevaListaEjemplos.push_back(nuevaLinea);
					}					
				}
				Arbol a = ejecutarID3(nuevaListaAtributos, nuevaListaEjemplos);
				tree.addHijo(values->first, a);
			}
			
			return tree;
		}
		else throw "error";

	}

	unordered_map<string, unordered_map<string, Nodo> > generarTablasIteracion(vector<string> listaAtributos, list<vector<string>> listaEjemplos) {
		unordered_map<string, unordered_map<string, Nodo> > datos;

		for (size_t i = 0; i<listaAtributos.size() - 1; i++)
			datos.insert_or_assign(listaAtributos[i], unordered_map<string, Nodo>());
		for (auto ejemplos = listaEjemplos.begin(); ejemplos != listaEjemplos.end(); ejemplos++) {
			for (unsigned int i = 0; i < ejemplos->size() - 1; i++) {
				if ((*ejemplos)[ejemplos->size() - 1] == "si") {
					datos[listaAtributos[i]][(*ejemplos)[i]].sumP();
				}
				else datos[listaAtributos[i]][(*ejemplos)[i]].sumN();
			}
		}

		return datos;
	}

	bool comprobar(list<vector<string>> l, string s) {
		for (auto cit = l.cbegin(); cit != l.cend(); cit++) {
			if ((*cit)[cit->size() - 1] != s)
				return false;
		}
		return true;
	}

	unordered_map<string, int> calcularIndiceAtributos(vector<string> listaAtributos) {
		unordered_map<string, int> m;
		size_t i = 0;
		for (auto cit = listaAtributos.cbegin(); cit != listaAtributos.cend(); cit++) {
			m.insert_or_assign(*cit, i);
			i++;
		}
		return m;
	}

	float calcularMerito(const unordered_map<string, Nodo> &key) const {
		float merito = 0.0f;
		int N = 0;
		for (unordered_map<string, Nodo>::const_iterator values = key.cbegin(); values != key.cend(); values++) N += values->second.a();
		for (unordered_map<string, Nodo>::const_iterator values = key.cbegin(); values != key.cend(); values++) {
			float op1 = (values->second.a()*1.0f) / N;
			float op2 = values->second.infor();
			if (!isnan(op1) && !isnan(op2))
				merito += (op1 * op2);
		}
		return merito;
	}

	vector<string> _listaAtributos;
	unordered_map<string, int> _indiceAtributos;
	list<vector<string>> _listaEjemplos;
	Arbol _raiz;

	unordered_map<string, unordered_map<string, Nodo> > _datos;

};

#endif // !ID3_H_
